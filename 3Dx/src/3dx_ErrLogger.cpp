#include "..\include\3dx_ErrLogger.h"
#include <comdef.h>

void ErrorLogger::log(const std::string &message)
{
	std::string error_message = "Error: " + message;
	MessageBoxA(NULL, error_message.c_str(), "Error", MB_ICONERROR);
}

void ErrorLogger::log(HRESULT hResult, const std::string message)
{
	_com_error error(hResult);
	std::wstring error_message = L"Error" + StringConverter::stringToWide(message) +
		L"\n" + error.ErrorMessage();
	MessageBoxW(NULL, error_message.c_str(), L"Error", MB_ICONERROR);
}
