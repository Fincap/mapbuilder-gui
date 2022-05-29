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
  inline bool loadHeightmapTexture(mbc::Heightmap& map, ID3D11ShaderResourceView** outSrv)
  {
    // Exit early if g_pd3dDevice not yet initialized.
    if (g_pd3dDevice == NULL || map.points == NULL)
      return false;

    // Load heightmap data into raw RGBA buffer
    int imageWidth = map.width;
    int imageHeight = map.height;

    unsigned char* imageData = new unsigned char[(imageWidth * imageHeight) * 4];

    int index = 0;
    for (int i = 0; i < imageWidth * imageHeight; i++)
    {
      auto height = map.points[i];
      imageData[index + 0] = height;
      imageData[index + 1] = height;
      imageData[index + 2] = height;
      imageData[index + 3] = 255;
      index += 4;
    }

    // Create texture
    D3D11_TEXTURE2D_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Width = imageWidth;
    desc.Height = imageHeight;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    desc.CPUAccessFlags = 0;

    ID3D11Texture2D* pTexture = NULL;
    D3D11_SUBRESOURCE_DATA subResource;
    subResource.pSysMem = imageData;
    subResource.SysMemPitch = desc.Width * 4;
    subResource.SysMemSlicePitch = 0;
    g_pd3dDevice->CreateTexture2D(&desc, &subResource, &pTexture);

    // Create texture view
    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    ZeroMemory(&srvDesc, sizeof(srvDesc));
    srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = desc.MipLevels;
    srvDesc.Texture2D.MostDetailedMip = 0;
    g_pd3dDevice->CreateShaderResourceView(pTexture, &srvDesc, outSrv);
    pTexture->Release();

    delete[] imageData;

    return true;

  }
}