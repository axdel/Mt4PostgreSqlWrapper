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
    std::string log_file = "";
    std::string log_prefix = "";

    HANDLE log_file_handle = NULL;
    
    bool log_debug = false;
    bool log_to_stdout = false;

    void WriteLog(std::wstringstream & log_message, const std::wstring log_level);

public:
    Logger();
    ~Logger();
    
    const bool Create(const std::string log_file, const std::string log_prefix = "");
    const int GetLogger();
    void LogDebug(const bool log_debug);
    void LogToStdout(const bool log_to_stdout);

    void Debug(std::wstringstream & log_message);
    void Info(std::wstringstream & log_message);
    void Warning(std::wstringstream & log_message);
    void Error(std::wstringstream & log_message);
    void Critical(std::wstringstream & log_message);
};

namespace {
    inline Logger * const GetLogger(const int logger) {
        return reinterpret_cast<Logger * const>(logger);
    }
}

//
// DLLAPI
//
DLLAPI const bool DllLoggerCreate(const int logger, const wchar_t * const log_file, const wchar_t * const log_prefix);
DLLAPI void DllLoggerDestroy(const int logger);
DLLAPI const int DllLoggerInit();
DLLAPI const int DllLoggerGetLogger(const int logger);
DLLAPI void DllLoggerLogDebug(const int logger, const bool log_debug);
DLLAPI void DllLoggerLogToStdout(const int logger, const bool log_to_stdout);
DLLAPI void DllLoggerDebug(const int logger, const wchar_t * const log_message);
DLLAPI void DllLoggerInfo(const int logger, const wchar_t * const log_message);
DLLAPI void DllLoggerWarning(const int logger, const wchar_t * const log_message);
DLLAPI void DllLoggerError(const int logger, const wchar_t * const log_message);
DLLAPI void DllLoggerCritical(const int logger, const wchar_t * const log_message);

#endif