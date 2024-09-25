#include "../../include/graphics/3dx_Graphics.h"

bool DxGraphics::initialize(HWND hWnd, int width, int height)
{
	if (!initializeDirectX(hWnd, width, height))
		return false;

	if (!initializeShaders())
		return false;

	return true;
}

void DxGraphics::renderFrame()
{
	float backgraundColor[] = { 0.0f, 0.0f, 1.0f, 1.0f };
	this->m_deviceContext->ClearRenderTargetView(this->m_renderTargetView.Get(), backgraundColor);
	this->m_swapChain->Present(1, NULL);
}

bool DxGraphics::initializeDirectX(HWND hWnd, int width, int height)
{
	std::vector<GraphicAdapter> adapters = GraphicAdapterReader::getAdapters();

	if(adapters.size() < 1)
	{
		ErrorLogger::log("No IDXGI adapters found");
		return false;
	}

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 1;
	swapChainDesc.OutputWindow = hWnd;
	swapChainDesc.Windowed = TRUE;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	HRESULT hResult;
	hResult = D3D11CreateDeviceAndSwapChain(	adapters[0].ptr_adapter, // IDXGI Adapter
		D3D_DRIVER_TYPE_UNKNOWN,
		NULL,								 // FOR SOFTWARE DRIVER TYPE
		NULL,								 // FLAGS FOR RUNTIME LAYERS
		NULL,								 // FEATURE LEVELS ARRAY
		0,									 //# OF FEATURE LEVELS IN ARRAY
		D3D11_SDK_VERSION,
		&swapChainDesc,						 // Swapchain description
		this->m_swapChain.GetAddressOf(),	 // Swapchain Address
		this->m_device.GetAddressOf(),		 // Device Address
		NULL,								 // Supported feature level
		this->m_deviceContext.GetAddressOf()); // Device Context Address

	if (FAILED(hResult))
	{
		ErrorLogger::log(hResult, "Failed to create device and swapchain");
		return false;
	}

	MWRL::ComPtr<ID3D11Texture2D> backBuffer;
	hResult = this->m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf()));
	if (FAILED(hResult)) //If error occurred
	{
		ErrorLogger::log(hResult, "GetBuffer Failed.");
		return false;
	}

	hResult = this->m_device->CreateRenderTargetView(backBuffer.Get(), NULL, this->m_renderTargetView.GetAddressOf());
	if (FAILED(hResult)) //If error occurred
	{
		ErrorLogger::log(hResult, "Failed to create render target view.");
		return false;
	}

	this->m_deviceContext->OMSetRenderTargets(1, this->m_renderTargetView.GetAddressOf(), NULL);


	return true;
}

bool DxGraphics::initializeShaders()
{
	std::wstring shaderFolder;

#ifndef _DEBUG // Debug mode
	#ifdef _WIN64 // x64
		shaderFolder = L"..\\x64\\Debug\\shaders\\";
	#else // x86 Win32
		shaderFolder = L"..\\Debug\\shaders\\";
#endif // _WIN64
#else // Release mode
	#ifdef _WIN64 // x64
		shaderFolder = L"..\\x64\\Release\\shaders\\";
	#else // x86 Win32
		shaderFolder = L"..\\Release\\shaders\\";
	#endif
#endif // !_DEBUG // Debug mode


	if(!m_vertexShader.initialize(this->m_device, L"..\\Debug\\shaders\\3dx_VertexShader.cso"))
	{
		return false;
	}


	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{
			"POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT, 0, 0,
			D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0
		},

	};

	UINT numElements = ARRAYSIZE(layout);

	HRESULT hResult =  this->m_device->CreateInputLayout(layout, numElements, 
		this->m_vertexShader.getBuffer()->GetBufferPointer(), this->m_vertexShader.getBuffer()->GetBufferSize(), 
		this->m_inputLayout.GetAddressOf());

	if(FAILED(hResult))
	{
		ErrorLogger::log(hResult, "Failed to create input layout");
		return false;
	}

	return true;
}
