#ifndef COMMON_H
#define COMMON_H

#include <crtdefs.h>
#include <iostream>
#include <regex>
#include <Windows.h>

#define DLLAPI extern "C" __declspec(dllexport)

#define WRAPPER_VERSION L"2016.10.14"

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

//
// log postion
//
inline std::wstring __FILENAME__(std::wstring file_path) {
    std::wstring filename = L"unknown";
    std::wsmatch match;
    std::wregex regex(L"^.*?\\\\(\\w+\\.\\w+)$");
    if (std::regex_search(file_path, match, regex)) { filename = match[1].str(); }
    return filename;
}
//#define LOG(log_message) log_message
#define LOG(log_message) dynamic_cast<std::wstringstream &>(log_message << " [" << __FILENAME__(_STR2WSTR(__FILE__)) << "|" << __FUNCTIONW__ << "|" << __LINE__ << "]")

#endif