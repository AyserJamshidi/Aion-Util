#pragma once

#include <windows.h>
#include <string>

class StringTools {

public:
	std::string ReplaceString(std::string subject, const std::string & search, const std::string & replace);
	void ReplaceStringInPlace(std::string & subject, const std::string & search, const std::string & replace);

	std::wstring ReplaceWString(std::wstring subject, const std::wstring & search, const std::wstring & replace);
	void ReplaceWStringInPlace(std::wstring & subject, const std::wstring & search, const std::wstring & replace);

	std::wstring test(std::wstring s, std::wstring delimiter);
	std::wstring toLower(std::wstring str);

	bool isOnlyNumeric(const std::wstring & str);
	std::string SplitFilename(const std::string & str);
};