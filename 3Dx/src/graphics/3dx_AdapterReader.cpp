#include "../../include/graphics/3dx_AdapterReader.h"

std::vector<GraphicAdapter> GraphicAdapterReader::m_adapters;


std::vector<GraphicAdapter> GraphicAdapterReader::getAdapters()
{
	// If already initialized
	if (m_adapters.size() > 0)
		return m_adapters;

	Microsoft::WRL::ComPtr<IDXGIFactory> ptr_factory;

	// Create a DGXIFactory obj
	HRESULT hResult = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void **>(ptr_factory.GetAddressOf()));

	if(FAILED(hResult))
	{
		ErrorLogger::log(hResult, "Failed to create DXGIFactory for enumerating adapters");
		exit(-1);
	}

	IDXGIAdapter *ptr_adapter;
	UINT index = 0;

	while (SUCCEEDED(ptr_factory->EnumAdapters(index, &ptr_adapter)))
	{
		m_adapters.push_back(GraphicAdapter(ptr_adapter));
		index += 1;
	}
	return m_adapters;
}


GraphicAdapter::GraphicAdapter(IDXGIAdapter *ptr_adatpter)
{
	this->ptr_adapter = ptr_adatpter;
	HRESULT hResult = ptr_adapter->GetDesc(&this->description);
	if(FAILED(hResult))
	{
		ErrorLogger::log(hResult, "Failed to get description for IDXGIAdapter");
	}

}