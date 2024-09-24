#include "../../include/graphics/3dx_Shaders.h"

bool VertexShader::initialize(MWRL::ComPtr<ID3D11Device> &device, std::wstring shaderPath)
{
	HRESULT hResult = D3DReadFileToBlob(shaderPath.c_str(), this->m_shaderBuffer.GetAddressOf());
	
	if (FAILED(hResult))
	{
		std::wstring errorMsg = L"Failed to load shader: ";
		errorMsg += shaderPath;
		ErrorLogger::log(hResult, errorMsg);
		return false;
	}

	hResult = device->CreateVertexShader(this->m_shaderBuffer->GetBufferPointer(), this->m_shaderBuffer->GetBufferSize(), 
		NULL, this->m_shader.GetAddressOf());
	if (FAILED(hResult))
	{
		std::wstring errorMsg = L"Failed to create vertex shader: ";
		errorMsg += shaderPath;
		ErrorLogger::log(hResult, errorMsg);
		return false;
	}

	return true;
}

ID3D11VertexShader *VertexShader::getShader()
{
	return this->m_shader.Get();
}

ID3D10Blob *VertexShader::getBuffer()
{
	return this->m_shaderBuffer.Get();
}
