#pragma once
#ifndef _3DX_ADAPTER_READER_H_
#define _3DX_ADAPTER_READER_H_

#include "../3dx_ErrLogger.h"
// include the Direct3D Library file
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "DirectXTK.lib")
#pragma comment(lib, "DXGI.lib")

#include <wrl/client.h>
#include <vector>


class GraphicAdapter
{
public:
	GraphicAdapter(IDXGIAdapter *ptr_adatpter);
	IDXGIAdapter *ptr_adapter = nullptr;
	DXGI_ADAPTER_DESC description;
};

class GraphicAdapterReader
{
public:
	static std::vector<GraphicAdapter> getAdapters();
private:
	static std::vector<GraphicAdapter> m_adapters;
};

#endif // !_3DX_ADAPTER_READER_H_
