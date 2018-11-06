#include "StringTools.h"
#include <algorithm>

std::string StringTools::ReplaceString(std::string subject, const std::string& search,
									   const std::string& replace) {
	size_t pos = 0;
	while((pos = subject.find(search, pos)) != std::string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	return subject;
}

void StringTools::ReplaceStringInPlace(std::string& subject, const std::string& search,
									   const std::string& replace) {
	size_t pos = 0;
	while((pos = subject.find(search, pos)) != std::string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
}

std::wstring StringTools::ReplaceWString(std::wstring subject, const std::wstring& search,
									   const std::wstring& replace) {
	size_t pos = 0;
	while((pos = subject.find(search, pos)) != std::wstring::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	return subject;
}

void StringTools::ReplaceWStringInPlace(std::wstring& subject, const std::wstring& search,
									   const std::wstring& replace) {
	size_t pos = 0;
	while((pos = subject.find(search, pos)) != std::wstring::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
}

std::wstring StringTools::test(std::wstring s, std::wstring delimiter) {
	size_t pos = 0;
	std::wstring token;

	while((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, pos);
		//std::cout << token << std::endl;
		s.erase(0, pos + delimiter.length());
	}

	return s;
}

std::wstring StringTools::toLower(std::wstring wStr) {
	std::transform(
		wStr.begin(), wStr.end(),
		wStr.begin(),
		towlower);
	return wStr;
}

bool StringTools::isOnlyNumeric(const std::wstring &str) {
	return std::all_of(str.begin(), str.end(), ::isdigit); // C++11
}

/*
Splitting: /usr/bin/man
 path: /usr/bin
 file: man
*/
std::string StringTools::SplitFilename(const std::string& str) {
	std::size_t found = str.find_last_of("/\\");
	return str.substr(0, found);
	//std::cout << " file: " << str.substr(found + 1) << '\n';
}

