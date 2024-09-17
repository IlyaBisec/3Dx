#pragma once
#include "3dx_StreamConverter.h"
#include <Windows.h>

// ErrorLogger - the class,which show error message
class ErrorLogger
{
public:
	static void log(const std::string &message);
	static void log(HRESULT hResult, const std::string message);
	static void log(HRESULT hResult, std::wstring message);

private:
};