#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <Windows.h>

inline void AnsiToUnicode(const std::string & in, std::wstring * const out) {
    out->assign(in.begin(), in.end()); 
}

inline void UnicodeToAnsi(const std::wstring & in, std::string * const out) {
    out->assign(in.begin(), in.end());
}

inline void FatalErrorMessageBox(const std::wstring & message) {
    MessageBoxW(NULL, message.c_str(), L"Fatal Error", MB_ICONERROR | MB_OK);
}

#define DLLAPI extern "C" __declspec(dllexport)

#endif