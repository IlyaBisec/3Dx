#pragma once
#ifndef _3DX_SHADERS_H_
#define _3DX_SHADERS_H_

#include "../3dx_ErrLogger.h"

#pragma comment(lib, "D3DCompiler.lib")

#include <d3d11.h>
#include <wrl/client.h>
#include <d3dcompiler.h>

namespace MWRL = Microsoft::WRL;

class VertexShader
{
public:
	bool initialize(MWRL::ComPtr<ID3D11Device> &device, std::wstring shaderPath);
	ID3D11VertexShader *getShader();
	ID3D10Blob *getBuffer();

private:
	MWRL::ComPtr<ID3D11VertexShader> m_shader;
	MWRL::ComPtr<ID3D10Blob> m_shaderBuffer;
};


#endif // !_3DX_SHADERS_H_
