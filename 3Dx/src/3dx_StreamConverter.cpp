#include "../include/3dx_StreamConverter.h"

std::wstring StringConverter::stringToWide(const std::string &str)
{
	std::wstring wide_string(str.begin(), str.end());
	return wide_string;
}
