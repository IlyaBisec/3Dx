#pragma once
#include <string>

// StringConverter - the class which convert std::string to wide string
class StringConverter
{
public:
	static std::wstring stringToWide(const std::string &str);

private:
};