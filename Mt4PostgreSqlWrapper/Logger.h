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
    
    bool log_debug = false;
    bool log_to_stdout = false;

    void WriteLog(std::wstringstream & log_message, const std::wstring log_level, const bool message_box = false);

public:
    Logger(const std::string log_file, const std::string log_prefix = "");
    ~Logger();
    
    const int GetLogger();
    void LogDebug(const bool log_debug);
    void LogToStdout(const bool log_to_stdout);

    void Debug(std::wstringstream & log_message, const bool message_box = false);
    void Info(std::wstringstream & log_message, const bool message_box = false);
    void Warning(std::wstringstream & log_message, const bool message_box = false);
    void Error(std::wstringstream & log_message, const bool message_box = false);
    void Critical(std::wstringstream & log_message, const bool message_box = false);
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
DLLAPI void DllLoggerLogDebug(const int logger, const bool log_debug);
DLLAPI void DllLoggerLogToStdout(const int logger, const bool log_to_stdout);
DLLAPI void DllLoggerDebug(const int logger, const wchar_t * const log_message, const bool message_box = false);
DLLAPI void DllLoggerInfo(const int logger, const wchar_t * const log_message, const bool message_box = false);
DLLAPI void DllLoggerWarning(const int logger, const wchar_t * const log_message, const bool message_box = false);
DLLAPI void DllLoggerError(const int logger, const wchar_t * const log_message, const bool message_box = false);
DLLAPI void DllLoggerCritical(const int logger, const wchar_t * const log_message, const bool message_box = false);

#endif