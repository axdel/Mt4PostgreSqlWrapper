//
// Logger.h
//
#ifndef LOGGER_H
#define LOGGER_H

#include <iomanip>
#include <iostream>
#include <sstream>

#include "Common.h"

class Logger
{
private:
    const std::string log_file = "";
    const std::string log_prefix = "";

    HANDLE log_file_handle = NULL;

    bool log_to_stdout = false;
    void SetLogToStdout(const bool log_to_stdout);

public:
    Logger(const std::string log_file, const std::string log_prefix = "");
    ~Logger();
    
    const int GetLogger();
    void WriteLog(std::wstringstream & log_message);
};

namespace {
    inline Logger * const GetLogger(const int logger) {
        return reinterpret_cast<Logger * const>(logger);
    }
}

//
// DLLAPI
//
DLLAPI void DllLoggerDestroy(const int logger);
DLLAPI const int DllLoggerInit(const wchar_t * const log_file, const wchar_t * const log_prefix);
DLLAPI const int DllLoggerGetLogger(const int logger);
DLLAPI void DllLoggerWriteLog(const int logger, const wchar_t * const log_message);

#endif