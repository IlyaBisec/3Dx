#pragma once
#include "3dx_StreamConverter.h"
#include <Windows.h>


class ErrorLogger
{
public:
	static void log(const std::string &message);
	// Wstring error log
	static void log(HRESULT hResult, const std::string message);

private:
};