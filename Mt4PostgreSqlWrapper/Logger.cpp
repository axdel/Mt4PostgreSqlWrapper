//
// Logger.cpp
//
#include "Common.h"
#include "Logger.h"

//
// LoggerInit
//
Logger::Logger(const std::string log_file, const std::string log_prefix) : log_file(log_file), log_prefix(log_prefix)
{
    std::wstringstream error_message;

    this->log_file_handle = CreateFileA(
        this->log_file.c_str(), FILE_APPEND_DATA, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL
    );
    if (this->log_file_handle == INVALID_HANDLE_VALUE) {
        this->log_file_handle = NULL;
        error_message << "Cannot create file: " << this->log_file.c_str() << " (Error: " << GetLastError() << ")";
        FatalErrorMessageBox(error_message.str());
    }
}

DLLAPI const int DllLoggerInit(const wchar_t * const log_file, const wchar_t * const log_prefix)
{
    std::string _log_file, _log_prefix;
    UnicodeToAnsi(log_file, &_log_file);
    UnicodeToAnsi(log_prefix, &_log_prefix);
    return reinterpret_cast<const int>(new Logger(_log_file, _log_prefix));
}

//
// LoggerDestroy
//
Logger::~Logger() {}

DLLAPI void DllLoggerDestroy(const int logger)
{
    try {
        Logger * const _logger = GetLogger(logger);
        delete _logger;
    } catch (...) {
        FatalErrorMessageBox(L"DllLoggerDestroy - called on already destroyed logger.");
    }
}

//
// GetLogger
//
const int Logger::GetLogger()
{
    return reinterpret_cast<const int>(this);
}

DLLAPI const int DllLoggerGetLogger(const int logger)
{
    try {
        Logger * const _logger = GetLogger(logger);
        return _logger->GetLogger();
    } catch (...) {
        FatalErrorMessageBox(L"DllLoggerGetLogger - called on already destroyed logger.");
        return NULL;
    }
}

//
// WriteLog
//
void Logger::WriteLog(std::wstringstream & log_message)
{
    std::string _log_message;
    UnicodeToAnsi(log_message.str(), &_log_message);

    SYSTEMTIME st;
    std::stringstream timestamp;
    std::stringstream formatted_message;
    unsigned long bytes_writen;

    GetLocalTime(&st);
    timestamp << st.wYear << "-"
        << std::setw(2) << std::setfill('0') << st.wMonth << "-"
        << std::setw(2) << std::setfill('0') << st.wDay
        << " "
        << std::setw(2) << std::setfill('0') << st.wHour << ":"
        << std::setw(2) << std::setfill('0') << st.wMinute << ":"
        << std::setw(2) << std::setfill('0') << st.wSecond << "."
        << std::setw(3) << std::setfill('0') << st.wMilliseconds;

    formatted_message << timestamp.str() << " ";
    if (!this->log_prefix.empty()) {
        formatted_message << "[" << this->log_prefix << "] ";
    }
    formatted_message << _log_message << std::endl;

    if (this->log_to_stdout) { std::cout << formatted_message.str(); }
    
    if (this->log_file_handle != NULL) {
        WriteFile(this->log_file_handle, formatted_message.str().c_str(), strlen(formatted_message.str().c_str()), &bytes_writen, NULL);
    }
    
    log_message.str(L"");
    return;
}

DLLAPI void DllLoggerWriteLog(const int logger, const wchar_t * const log_message)
{
    try {
        Logger * const _logger = GetLogger(logger);
        std::wstringstream _log_message;
        _log_message << log_message;
        return _logger->WriteLog(_log_message);
    } catch (...) {
        FatalErrorMessageBox(L"DllLoggerWriteLog - called on already destroyed wrapper.");
    }
}