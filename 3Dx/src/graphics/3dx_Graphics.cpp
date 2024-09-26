#include "../../include/graphics/3dx_Graphics.h"

bool DxGraphics::initialize(HWND hWnd, int width, int height)
{
	if (!initializeDirectX(hWnd, width, height))
		return false;

	if (!initializeShaders())
		return false;

	if (!initializeScene())
		return false;

	return true;
}

void DxGraphics::renderFrame()
{
	float backgraundColor[] = { 0.0f, 0.0f, 0.0f, 1.0f }; // Black
	this->m_deviceContext->ClearRenderTargetView(this->m_renderTargetView.Get(), backgraundColor);
	this->m_deviceContext->ClearDepthStencilView(this->m_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);


	this->m_deviceContext->IASetInputLayout(this->m_vertexShader.getInputLayout());
	this->m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	this->m_deviceContext->RSSetState(this->m_rasterizerState.Get());
	this->m_deviceContext->OMSetDepthStencilState(this->m_depthStencilState.Get(), 0);

	this->m_deviceContext->VSSetShader(m_vertexShader.getShader(), NULL, 0);
	this->m_deviceContext->PSSetShader(m_pixelShader.getShader(), NULL, 0);

	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	// Red trinagle
	this->m_deviceContext->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride, &offset);
	this->m_deviceContext->Draw(3, 0);

	// Green triangle
	this->m_deviceContext->IASetVertexBuffers(0, 1, m_vertexBuffer2.GetAddressOf(), &stride, &offset);
	this->m_deviceContext->Draw(3, 0);

	// Draw text
	/*m_spriteBatch->Begin();
	m_spriteFont->DrawString(m_spriteBatch.get(), L"HEY", DirectX::XMFLOAT2(0, 0), DirectX::Colors::White, 0.0f,
		DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f));
	m_spriteBatch->End();*/


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
		ErrorLogger::log(hResult, "Failed to create render target view");
		return false;
	}

	// Describe our depth/Stencil buffer
	D3D11_TEXTURE2D_DESC depthStencilDesc;
	depthStencilDesc.Width = width;
	depthStencilDesc.Height = height;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;


	hResult = this->m_device->CreateTexture2D(&depthStencilDesc, NULL, this->m_depthStencilBuffer.GetAddressOf());
	if (FAILED(hResult)) //If error occurred
	{
		ErrorLogger::log(hResult, "Failed to create depth stencil buffer");
		return false;
	}

	hResult = this->m_device->CreateDepthStencilView(this->m_depthStencilBuffer.Get(), NULL, this->m_depthStencilView.GetAddressOf());
	if (FAILED(hResult)) //If error occurred
	{
		ErrorLogger::log(hResult, "Failed to create depth stencil view");
		return false;
	}

	this->m_deviceContext->OMSetRenderTargets(1, this->m_renderTargetView.GetAddressOf(), this->m_depthStencilView.Get());

	// Create depth stencil state
	D3D11_DEPTH_STENCIL_DESC _depthstencildesc;
	ZeroMemory(&_depthstencildesc, sizeof(D3D11_DEPTH_STENCIL_DESC));

	_depthstencildesc.DepthEnable = true;
	_depthstencildesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
	_depthstencildesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;

	hResult = this->m_device->CreateDepthStencilState(&_depthstencildesc, this->m_depthStencilState.GetAddressOf());
	if (FAILED(hResult)) //If error occurred
	{
		ErrorLogger::log(hResult, "Failed to create depth stencil state");
		return false;
	}

	// Create the viewport
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = width;
	viewport.Height = height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;


	// Set the viewport
	this->m_deviceContext->RSSetViewports(1, &viewport);

	// Create Rasterizer state(viewport window)
	D3D11_RASTERIZER_DESC rasterizerDesc;
	ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));

	rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID; // Wireframe or solid viewport here
	rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;  // Back facing
	hResult = this->m_device->CreateRasterizerState(&rasterizerDesc, this->m_rasterizerState.GetAddressOf());
	if (FAILED(hResult))
	{
		ErrorLogger::log(hResult, "Failed to create rasterizer state");
		return false;
	}

	/*m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(this->m_deviceContext.Get());
	m_spriteFont = std::make_unique<DirectX::SpriteFont>(this->m_device.Get(), L"data\\fonts\\comic_sans_ms_16.spritefont");*/


	return true;
}

bool DxGraphics::initializeShaders()
{
	std::wstring shaderFolder = L"";

#pragma region DetermineShaderPath
	if (IsDebuggerPresent() == TRUE)
	{
#ifdef _DEBUG //Debug Mode
#ifdef _WIN64 //x64
		shaderFolder = L"..\\x64\\Debug\\";
#else  //x86 (Win32)
		shaderFolder = L"..\\Debug\\";
#endif
#else //Release Mode
#ifdef _WIN64 //x64
		shaderFolder = L"..\\x64\\Release\\";
#else  //x86 (Win32)
		shaderFolder = L"..\\Release\\";
#endif
#endif
	}

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA,0},
	};

	UINT numElements = ARRAYSIZE(layout);

	if(!m_vertexShader.initialize(this->m_device, shaderFolder + L"shaders\\3dx_VertexShader.cso", layout, numElements))
	{
		return false;
	}

	if(!m_pixelShader.initialize(this->m_device, shaderFolder + L"shaders\\3dx_PixelShader.cso"))
	{
		return false;
	}

	return true;
}

bool DxGraphics::initializeScene()
{
	// Red trinagle
	Vertex vertex[] =
	{
		Vertex(-0.5f,  -0.5f, 1.0f, 1.0f, 0.0f, 0.0f), // Bottom Left 
		Vertex( 0.0f,   0.5f, 1.0f, 1.0f, 0.0f, 0.0f), // Top Middle
		Vertex( 0.5f,  -0.5f, 1.0f, 1.0f, 0.0f, 0.0f), // Bottom Right 
	};

	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * ARRAYSIZE(vertex);
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData;
	ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
	vertexBufferData.pSysMem = vertex;

	HRESULT hResult = this->m_device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, this->m_vertexBuffer.GetAddressOf());
	if(FAILED(hResult))
	{
		ErrorLogger::log(hResult, "Failed to create vertex buffer");
		return false;
	}

	// Green trinagle
	Vertex vertex_g[] =
	{
		Vertex(-0.25f, -0.25f, 0.0f, 0.0f, 1.0f, 0.0f), // Bottom Left 
		Vertex( 0.00f,  0.25f, 0.0f, 0.0f, 1.0f, 0.0f), // Top Middle
		Vertex( 0.25f, -0.25f, 0.0f, 0.0f, 1.0f, 0.0f), // Bottom Right 
	};

	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * ARRAYSIZE(vertex_g);
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
	vertexBufferData.pSysMem = vertex_g;

	hResult = this->m_device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, this->m_vertexBuffer2.GetAddressOf());
	if (FAILED(hResult))
	{
		ErrorLogger::log(hResult, "Failed to create vertex buffer");
		return false;
	}


	return true;
}
