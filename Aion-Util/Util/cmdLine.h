#pragma once

#include <Windows.h>

class cmdLine {
public:
	cmdLine();
	~cmdLine();
	std::vector<std::wstring> GetCommandLines();
	bool cleanUp();
};