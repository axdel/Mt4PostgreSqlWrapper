#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <Windows.h>

const wchar_t WRAPPER_VERSION[] = L"2015.12.21";

namespace {
    inline void AnsiToUnicode(const std::string & in, std::wstring * const out) {
        out->assign(in.begin(), in.end()); 
    }

    inline void UnicodeToAnsi(const std::wstring & in, std::string * const out) {
        out->assign(in.begin(), in.end());
    }

	inline void WindowsMessageBox(const std::wstring & message, const std::wstring & title, const UINT type) {
		MessageBoxW(NULL, message.c_str(), title.c_str(), type);
	}

    inline void FatalErrorMessageBox(const std::wstring & message) {
		WindowsMessageBox(message.c_str(), L"Fatal Error", MB_ICONERROR | MB_OK);
    }
}

#define DLLAPI extern "C" __declspec(dllexport)

#endif