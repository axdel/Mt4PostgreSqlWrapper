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
        error_message << "Cannot create file: " << this->log_file.c_str() << " (Error code: " << GetLastError() << ")";
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
// LogDebug
//
void Logger::LogDebug(const bool log_debug)
{
    this->log_debug = log_debug;
}

DLLAPI void DllLoggerLogDebug(const int logger, const bool log_debug)
{
    try {
        Logger * const _logger = GetLogger(logger);
        _logger->LogDebug(log_debug);
    }
    catch (...) {
        FatalErrorMessageBox(L"DllLoggerLogDebug - called on already destroyed logger.");
    }
}

//
// LogToStdout
//
void Logger::LogToStdout(const bool log_to_stdout)
{
    this->log_to_stdout = log_to_stdout;
}

DLLAPI void DllLoggerLogToStdout(const int logger, const bool log_to_stdout)
{
    try {
        Logger * const _logger = GetLogger(logger);
        _logger->LogToStdout(log_to_stdout);
    }
    catch (...) {
        FatalErrorMessageBox(L"DllLoggerLogToStdout - called on already destroyed logger.");
    }
}

//
// Debug
//
void Logger::Debug(std::wstringstream & log_message, const bool message_box)
{
    if (this->log_debug) {
        this->WriteLog(log_message, L"DEBUG", message_box);
    }
}

DLLAPI void DllLoggerDebug(const int logger, const wchar_t * const log_message, const bool message_box)
{
    try {
        Logger * const _logger = GetLogger(logger);
        std::wstringstream _log_message;
        _log_message << log_message;
        return _logger->Debug(_log_message, message_box);
    }
    catch (...) {
        FatalErrorMessageBox(L"DllLoggerDebug - called on already destroyed logger.");
    }
}

//
// Info
//
void Logger::Info(std::wstringstream & log_message, const bool message_box)
{
    this->WriteLog(log_message, L"INFO", message_box);
}

DLLAPI void DllLoggerInfo(const int logger, const wchar_t * const log_message, const bool message_box)
{
    try {
        Logger * const _logger = GetLogger(logger);
        std::wstringstream _log_message;
        _log_message << log_message;
        return _logger->Info(_log_message, message_box);
    }
    catch (...) {
        FatalErrorMessageBox(L"DllLoggerInfo - called on already destroyed logger.");
    }
}

//
// Warning
//
void Logger::Warning(std::wstringstream & log_message, const bool message_box)
{
    this->WriteLog(log_message, L"WARNING", message_box);
}

DLLAPI void DllLoggerWarning(const int logger, const wchar_t * const log_message, const bool message_box)
{
    try {
        Logger * const _logger = GetLogger(logger);
        std::wstringstream _log_message;
        _log_message << log_message;
        return _logger->Warning(_log_message, message_box);
    }
    catch (...) {
        FatalErrorMessageBox(L"DllLoggerWarning - called on already destroyed logger.");
    }
}

//
// Error
//
void Logger::Error(std::wstringstream & log_message, const bool message_box)
{
    this->WriteLog(log_message, L"ERROR", message_box);
}

DLLAPI void DllLoggerError(const int logger, const wchar_t * const log_message, const bool message_box)
{
    try {
        Logger * const _logger = GetLogger(logger);
        std::wstringstream _log_message;
        _log_message << log_message;
        return _logger->Error(_log_message, message_box);
    }
    catch (...) {
        FatalErrorMessageBox(L"DllLoggerError - called on already destroyed logger.");
    }
}

//
// Critical
//
void Logger::Critical(std::wstringstream & log_message, const bool message_box)
{
    this->WriteLog(log_message, L"CRITICAL", message_box);
}

DLLAPI void DllLoggerCritical(const int logger, const wchar_t * const log_message, const bool message_box)
{
    try {
        Logger * const _logger = GetLogger(logger);
        std::wstringstream _log_message;
        _log_message << log_message;
        return _logger->Critical(_log_message, message_box);
    }
    catch (...) {
        FatalErrorMessageBox(L"DllLoggerCritical - called on already destroyed logger.");
    }
}

//
// WriteLog
//
void Logger::WriteLog(std::wstringstream & log_message, const std::wstring log_level, const bool message_box)
{
    std::string _log_message, _log_level;
    UnicodeToAnsi(log_message.str(), &_log_message);
    UnicodeToAnsi(log_level, &_log_level);

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
        << std::setw(2) << std::setfill('0') << st.wSecond << ","
        << std::setw(3) << std::setfill('0') << st.wMilliseconds;

    formatted_message << timestamp.str() << " " << _log_level << " ";
    if (!this->log_prefix.empty()) { formatted_message << this->log_prefix << " "; }
    formatted_message << _log_message << std::endl;

    if (this->log_to_stdout) { std::cout << formatted_message.str(); }
    
    if (this->log_file_handle != NULL) {
        WriteFile(this->log_file_handle, formatted_message.str().c_str(), strlen(formatted_message.str().c_str()), &bytes_writen, NULL);
    }
    if (message_box) {
        std::wstring _formatted_message;
        AnsiToUnicode(formatted_message.str(), &_formatted_message);
        WindowsMessageBox(_formatted_message, L"Logger", MB_ICONWARNING | MB_OK);
    }
    
    log_message.str(L""); // clear message
}