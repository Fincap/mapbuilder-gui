#pragma once
#include <memory>

#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <d3d11.h>
#include <MapBuilderCore\Payload.h>
#include <MapBuilderCore\payloads\Heightmap.h>
#include <MapBuilderCore\payloads\ColouredHeightmap.h>

#include "util\D3DGlobals.h"

namespace util
{
  struct SrvProps
  {
    ID3D11ShaderResourceView* srv;
    ID3D11Texture2D* texture;
    D3D11_TEXTURE2D_DESC descTexture;
    D3D11_SHADER_RESOURCE_VIEW_DESC descSrv;
    int prevW;
    int prevH;

    SrvProps()
    {
      newTexture(64, 64);
      bindToSrv();
    }

    void newTexture(int width, int height)
    {
      if (texture != NULL)
        texture->Release();

      prevW = width;
      prevH = height;

      // Create dynamic texture description
      ZeroMemory(&descTexture, sizeof(descTexture));
      descTexture.Width = width;
      descTexture.Height = height;
      descTexture.MipLevels = 1;
      descTexture.ArraySize = 1;
      descTexture.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
      descTexture.SampleDesc.Count = 1;
      descTexture.Usage = D3D11_USAGE_DYNAMIC;
      descTexture.BindFlags = D3D11_BIND_SHADER_RESOURCE;
      descTexture.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

      texture = NULL;
      g_pd3dDevice->CreateTexture2D(&descTexture, NULL, &texture);

      bindToSrv();
    }

    void bindToSrv()
    {
      if (srv != NULL)
        srv->Release();

      // Create shader resource view
      ZeroMemory(&descSrv, sizeof(descSrv));
      descSrv.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
      descSrv.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
      descSrv.Texture2D.MipLevels = descTexture.MipLevels;
      descSrv.Texture2D.MostDetailedMip = 0;
      g_pd3dDevice->CreateShaderResourceView(texture, &descSrv, &srv);
    }

    void mapNewTexture(int width, int height, void* imageData)
    {
      if (width != prevW || height != prevH)
        newTexture(width, height);

      // Create mapped subresource
      D3D11_MAPPED_SUBRESOURCE sub{};
      ZeroMemory(&sub, sizeof(sub));

      // Disable GPU access to the texture data.
      g_pd3dDeviceContext->Map(texture, 0, D3D11_MAP_WRITE_DISCARD, 0, &sub);

      // Map to subresource data
      /* You can only memcpy the entire block in one operation if pitch is equal to width * number
      of bytes in the format. Otherwise you must memcpy one row at a time.
      Credit: https://gamedev.stackexchange.com/a/187646 */
      unsigned* src = (unsigned*)imageData;   // Iterable pointer to image data
      unsigned* dst = (unsigned*)sub.pData;   // Iterable pointer to subresource data.

      for (int i = 0; i < height; i++)   // Copy row-by-row
      {
        memcpy(dst, src, static_cast<size_t>(width) * 4);
        dst += sub.RowPitch >> 2;   // RowPitch is in bytes so for 32-bit data we divide by 4.
        src += width;               // Assume pitch of source data is equal to width * 4.
      }

      // Re-enable GPU access to texture data.
      g_pd3dDeviceContext->Unmap(texture, 0);
    }

  };

  inline bool loadHeightmapTexture(mbc::Heightmap& map, SrvProps& props)
  {
    // Exit early if g_pd3dDevice not yet initialized.
    if (g_pd3dDevice == NULL || map.points == NULL)
      return false;

    // Load heightmap data into raw RGBA buffer
    int imageWidth = map.width;
    int imageHeight = map.height;
    int dataSize = imageWidth * imageHeight * 4;

    unsigned char* imageData = new unsigned char[dataSize] {0};

    int index = 0;
    for (int i = 0; i < dataSize; i++)
    {
      auto point = map.points[index];

      if (i % 4 == 3)
      {
        imageData[i] = 255;
        index++;
      }
      else
      {
        imageData[i] = point;
      }

    }

    // Map heightmap data to texture
    props.mapNewTexture(imageWidth, imageHeight, imageData);

    delete[] imageData;

    return true;

  }


  inline bool loadColouredHeightmapTexture(mbc::ColouredHeightmap& map, SrvProps& props)
  {
    // Exit early if g_pd3dDevice not yet initialized.
    if (g_pd3dDevice == NULL || map.colouredPoints == NULL)
      return false;

    // Load heightmap data into raw RGBA buffer
    int imageWidth = map.width;
    int imageHeight = map.height;
    int dataSize = imageWidth * imageHeight;

    uint32_t* imageData = new uint32_t[dataSize] {0};

    for (int i = 0; i < dataSize; i++)
    {
      // Move alpha channel to leftmost byte.
      imageData[i] = map.colouredPoints[i] + (0xff << 24);
    }

    // Map heightmap data to texture
    props.mapNewTexture(imageWidth, imageHeight, imageData);

    delete[] imageData;

    return true;

  }
}
