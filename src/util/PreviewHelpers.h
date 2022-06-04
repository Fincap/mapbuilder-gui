#pragma once
#include <memory>

#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <d3d11.h>
#include <MapBuilderCore\Payload.h>
#include <MapBuilderCore\payloads\Heightmap.h>

#include "util\D3DGlobals.h"

namespace util
{
  struct SrvProps
  {
    ID3D11ShaderResourceView* outSrv;
    ID3D11Texture2D* pTexture;
    D3D11_TEXTURE2D_DESC desc;
    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    int prevW;
    int prevH;

    SrvProps()
    {
      newTexture(64, 64);
      bindToSrv();
    }

    void newTexture(int width, int height)
    {
      if (pTexture != NULL)
        pTexture->Release();

      prevW = width;
      prevH = height;

      // Create dynamic texture description
      ZeroMemory(&desc, sizeof(desc));
      desc.Width = width;
      desc.Height = height;
      desc.MipLevels = 1;
      desc.ArraySize = 1;
      desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
      desc.SampleDesc.Count = 1;
      desc.Usage = D3D11_USAGE_DYNAMIC;
      desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
      desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

      pTexture = NULL;
      g_pd3dDevice->CreateTexture2D(&desc, NULL, &pTexture);

      bindToSrv();
    }

    void bindToSrv()
    {
      if (outSrv != NULL)
        outSrv->Release();

      // Create shader resource view
      ZeroMemory(&srvDesc, sizeof(srvDesc));
      srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
      srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
      srvDesc.Texture2D.MipLevels = desc.MipLevels;
      srvDesc.Texture2D.MostDetailedMip = 0;
      g_pd3dDevice->CreateShaderResourceView(pTexture, &srvDesc, &outSrv);
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

    if (imageWidth != props.prevW || imageHeight != props.prevH)
      props.newTexture(imageWidth, imageHeight);

    // Create mapped subresource
    D3D11_MAPPED_SUBRESOURCE sub{};
    ZeroMemory(&sub, sizeof(sub));

    // Disable GPU access to the texture data.
    g_pd3dDeviceContext->Map(props.pTexture, 0, D3D11_MAP_WRITE_DISCARD, 0, &sub);

    // Map to subresource data
    /* You can only memcpy the entire block in one operation if pitch is equal to width * number 
    of bytes in the format. Otherwise you must memcpy one row at a time.
    Credit: https://gamedev.stackexchange.com/a/187646 */
    unsigned* src = (unsigned*)imageData;   // Iterable pointer to image data
    unsigned* dst = (unsigned*)sub.pData;   // Iterable pointer to subresource data.

    for (int i = 0; i < imageHeight; i++)   // Copy row-by-row
    {
      memcpy(dst, src, static_cast<size_t>(imageWidth) * 4);
      dst += sub.RowPitch >> 2;   // RowPitch is in bytes so for 32-bit data we divide by 4.
      src += imageWidth;          // Assume pitch of source data is equal to width * 4.
    }

    // Re-enable GPU access to texture data.
    g_pd3dDeviceContext->Unmap(props.pTexture, 0);

    delete[] imageData;

    return true;

  }
}
