#pragma once
#ifndef _3DX_GRAPHICS_H_
#define _3DX_GRAPHICS_H_

#include "3dx_AdapterReader.h"
#include "3dx_Shaders.h"
#include "3dx_Vertex.h"

#include <SpriteBatch.h>
#include <SpriteFont.h>

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
	bool initializeScene();

	MWRL::ComPtr<ID3D11Device> m_device;
	MWRL::ComPtr<ID3D11DeviceContext> m_deviceContext;
	MWRL::ComPtr<IDXGISwapChain> m_swapChain;
	MWRL::ComPtr<ID3D11RenderTargetView> m_renderTargetView;

	MWRL::ComPtr<ID3D11Buffer> m_vertexBuffer;
	MWRL::ComPtr<ID3D11Buffer> m_vertexBuffer2;

	VertexShader m_vertexShader;
	PixelShader  m_pixelShader;

	MWRL::ComPtr<ID3D11DepthStencilView> m_depthStencilView;
	MWRL::ComPtr<ID3D11Texture2D> m_depthStencilBuffer;
	MWRL::ComPtr<ID3D11DepthStencilState> m_depthStencilState;

	MWRL::ComPtr<ID3D11RasterizerState> m_rasterizerState;

	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	std::unique_ptr<DirectX::SpriteFont> m_spriteFont;
};

#endif // !_3DX_GRAPHICS_H_