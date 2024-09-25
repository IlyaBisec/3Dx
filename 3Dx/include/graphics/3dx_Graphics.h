#pragma once
#ifndef _3DX_GRAPHICS_H_
#define _3DX_GRAPHICS_H_

#include "3dx_AdapterReader.h"
#include "3dx_Shaders.h"

namespace MWRL =  Microsoft::WRL;

// DxGraphics - class which initialize 3dx graphics
class DxGraphics
{
public:
	bool initialize(HWND hWnd, int width, int height);
	void renderFrame();

private:
	bool initializeDirectX(HWND hWnd, int width, int height);
	bool initializeShaders();

	MWRL::ComPtr<ID3D11Device> m_device;
	MWRL::ComPtr<ID3D11DeviceContext> m_deviceContext;
	MWRL::ComPtr<IDXGISwapChain> m_swapChain;
	MWRL::ComPtr<ID3D11RenderTargetView> m_renderTargetView;

	MWRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	VertexShader m_vertexShader;
	PixelShader  m_pixelShader;
};

#endif // !_3DX_GRAPHICS_H_