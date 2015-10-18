//
// NOTES:
//    - exception handling model has to be "/EHa"
//
#include "stdafx.h"

inline void AnsiToUnicode(const std::string & in, std::wstring * const out) {
    out->assign(in.begin(), in.end()); 
}

inline void UnicodeToAnsi(const std::wstring & in, std::string * const out) {
    out->assign(in.begin(), in.end());
}

inline void FatalErrorMessageBox(const std::wstring & message) {
    MessageBoxW(NULL, message.c_str(), L"Fatal Error (exception)", MB_ICONERROR | MB_OK);
}

inline void FillDataNotAvailable(wchar_t ** row, const int num_fields) {
    for (int i = 0; i < num_fields; i++) {
        wcscpy_s(row[i], (wcslen(NOT_AVAILABLE) + 1), NOT_AVAILABLE);
    }
}

inline Mt4PostgreSqlWrapper * const GetMt4PostgreSqlWrapper(const int wrapper) {
    return reinterpret_cast<Mt4PostgreSqlWrapper * const>(wrapper);
}

//
// WrapperInit
//
Mt4PostgreSqlWrapper::Mt4PostgreSqlWrapper() {}

const int DllWrapperInit()
{
    return reinterpret_cast<const int>(new Mt4PostgreSqlWrapper());
}

//
// WrapperDestroy
//
Mt4PostgreSqlWrapper::~Mt4PostgreSqlWrapper() {}

void DllWrapperDestroy(const int wrapper)
{
    try {
        Mt4PostgreSqlWrapper * _wrapper = GetMt4PostgreSqlWrapper(wrapper);
        delete _wrapper;
    } catch (...) {
        FatalErrorMessageBox(L"DllWrapperDestroy - called on already destroyed wrapper.");
    }
}

//
// PostgreSqlAffectedRows
//
const std::wstring Mt4PostgreSqlWrapper::PostgreSqlAffectedRows()
{
    return this->affected_rows;
}

void DllPostgreSqlAffectedRows(const int wrapper, wchar_t * affected_rows)
{
    try {
        Mt4PostgreSqlWrapper * _wrapper = GetMt4PostgreSqlWrapper(wrapper);
        std::wstring _affected_rows = _wrapper->PostgreSqlAffectedRows();
        wcscpy_s(affected_rows, (_affected_rows.length() + 1), _affected_rows.c_str());
    } catch (...) {
        FatalErrorMessageBox(L"DllPostgreSqlAffectedRows - called on already destroyed wrapper.");
    }
}

//
// PostgreSqlClearResult
//
void Mt4PostgreSqlWrapper::PostgreSqlClearResult()
{
    std::wstringstream log_message;

    log_message << "Clearing result... ";
    if (this->result != NULL) {
        PQclear(this->result);
        this->result = NULL;
        this->num_rows = 0;
        this->num_fields = 0;
        this->affected_rows = L"";
        log_message << "cleared";
    } else {
        log_message << "was already cleared";
    }
    this->WriteLog(log_message);
}

void DllPostgreSqlClearResult(const int wrapper)
{
    try {
        Mt4PostgreSqlWrapper * _wrapper = GetMt4PostgreSqlWrapper(wrapper);
        _wrapper->PostgreSqlClearResult();
    } catch (...) {
        FatalErrorMessageBox(L"DllPostgreSqlClearResult - called on already destroyed wrapper.");
    }
}

//
// PostrgeSqlClientVersion
//
const int DllPostgreSqlClientVersion()
{
    return PQlibVersion();
}

//
// PostgreSqlConnect
//
const bool Mt4PostgreSqlWrapper::PostgreSqlConnect(const std::wstring connection_string)
{
    std::wstringstream log_message;
    std::wstringstream error_message;
    error_message << "Unable to connect to database (repeatedly), logged error(s):\n\n";
    
    this->connection_string = connection_string;
    std::string _connection_string;
    UnicodeToAnsi(connection_string, &_connection_string);
    this->_connection_string = _connection_string;

    int reconnect_attepts = MAX_RECONNECT_ATTEMPTS;
    do {
        int i = (MAX_RECONNECT_ATTEMPTS-reconnect_attepts) + 1;
        log_message << "Opening database connection (attempt:" << i << ") ... ";
        this->connection = PQconnectdb(this->_connection_string.c_str());
        if (PQstatus(this->connection) == CONNECTION_OK) {
            log_message << "opened [c:" << this->connection << ", w:" << this << "]";
            this->WriteLog(log_message);
            return true;
        } else {
            log_message << "failed [" << this->connection << ", w:" << this << "]" << std::endl << PQerrorMessage(this->connection);
            this->WriteLog(log_message);
            error_message << "Attempt #" << i << ": ";
            error_message << PQerrorMessage(this->connection);
            Sleep(SLEEP_RECONNECT_FAILED);
        }
    } while (PQstatus(this->connection) == CONNECTION_BAD && --reconnect_attepts);

    FatalErrorMessageBox(error_message.str());
    return false;
}

const bool DllPostgreSqlConnect(const int wrapper, const wchar_t * connection_string)
{
    try {
        Mt4PostgreSqlWrapper * _wrapper = GetMt4PostgreSqlWrapper(wrapper);
        return _wrapper->PostgreSqlConnect(connection_string);
    } catch (...) {
        FatalErrorMessageBox(L"DllPostgreSqlConnect - called on already destroyed wrapper.");
        return false;
    }
}

//
// PostgreSqlCheckConnection
//
const bool Mt4PostgreSqlWrapper::PostgreSqlCheckConnection()
{
    std::wstringstream log_message;

    if (PQstatus(this->connection) == CONNECTION_OK) {
        return true;
    }

    log_message << "ERROR: connection closed, trying to reconnect...";
    this->WriteLog(log_message);

    this->PostgreSqlClose();
    return this->PostgreSqlConnect(this->connection_string);
}

//
// PostgreSqlClose
//
void Mt4PostgreSqlWrapper::PostgreSqlClose()
{
    std::wstringstream log_message;

    log_message << "Closing connection [c:" << this->connection << ", w:" << this << "] ... ";
    if (this->connection != NULL) {
        PQfinish(this->connection);
        this->connection = NULL;
        log_message << "closed";
    } else {
        log_message << "was already closed";
    }
    this->WriteLog(log_message);
}

void DllPostgreSqlClose(const int wrapper)
{
    std::wstringstream log_message;

    try {
        Mt4PostgreSqlWrapper * _wrapper = GetMt4PostgreSqlWrapper(wrapper);
        _wrapper->PostgreSqlClose();
    } catch (...) {
        FatalErrorMessageBox(L"DllPostgreSqlClose - called on already destroyed wrapper.");
    }
}

//
// PostgreSqlFetchRow
//
const bool Mt4PostgreSqlWrapper::PostgreSqlFetchRow(wchar_t ** const row, const int row_number)
{
    std::wstringstream log_message;

    if (!this->PostgreSqlCheckConnection()) {
        return false;
    }

    log_message << "Fetching row: " << row_number;
    this->WriteLog(log_message);
    if (this->result == NULL) {
        log_message << "ERROR: no active result found (probably cleared?)";
        this->WriteLog(log_message);
        FillDataNotAvailable(row, this->num_fields);
        return false;
    }
    if ((row_number + 1) > this->num_rows) {
        log_message << "ERROR: cannot fetch row " << row_number << " (#rows:" << this->num_rows << ")";
        this->WriteLog(log_message);
        FillDataNotAvailable(row, this->num_fields);
        return false;
    }

    std::wstring _field = L"";
    for (int i = 0; i < this->num_fields; i++) {
        if (!PQgetisnull(this->result, row_number, i)) {
            AnsiToUnicode(PQgetvalue(this->result, row_number, i), &_field);
            wcscpy_s(row[i], (_field.length() + 1), _field.c_str());
        } else {
            wcscpy_s(row[i], 5, L"NULL");
        }
    }

    return true;
}

const bool DllPostgreSqlFetchRow(const int wrapper, wchar_t ** const row, const int row_number)
{
    try {
        Mt4PostgreSqlWrapper * _wrapper = GetMt4PostgreSqlWrapper(wrapper);
        return _wrapper->PostgreSqlFetchRow(row, row_number);
    } catch (...) {
        FatalErrorMessageBox(L"DllPostgreSqlFetchRow - called on already destroyed wrapper.");
        return false;
    }
}

//
// PostgreSqlFieldList
//
const std::wstring Mt4PostgreSqlWrapper::PostgreSqlFieldList()
{
    std::wstringstream log_message;
    std::wstringstream field_list;

    log_message << "Field list: ";
    if (this->result == NULL) {
        log_message << NOT_AVAILABLE;
        this->WriteLog(log_message);
        log_message << "ERROR: no active result found (probably cleared?)";
        this->WriteLog(log_message);
        return NOT_AVAILABLE;
    }

    for (int i = 0; i < this->num_fields; i++) {
        field_list << "\"" << PQfname(this->result, i) << "\" ";
    }

    log_message << field_list.str();
    this->WriteLog(log_message);

    return field_list.str();
}

void DllPostgreSqlFieldList(const int wrapper, wchar_t * field_list)
{
    try {
        Mt4PostgreSqlWrapper * const _wrapper = GetMt4PostgreSqlWrapper(wrapper);
        std::wstring _field_list = _wrapper->PostgreSqlFieldList();
        wcscpy_s(field_list, (_field_list.length() + 1), _field_list.c_str());
    } catch (...) {
        FatalErrorMessageBox(L"DllPostgreSqlFieldList - called on already destroyed wrapper.");
    }
}

//
// PostgresqlNumFields
//
const int Mt4PostgreSqlWrapper::PostgreSqlNumFields()
{
    return this->num_fields;
}

const int DllPostgreSqlNumFields(const int wrapper)
{
    try {
        Mt4PostgreSqlWrapper * const _wrapper = GetMt4PostgreSqlWrapper(wrapper);
        return _wrapper->PostgreSqlNumFields();
    } catch (...) {
        FatalErrorMessageBox(L"DllPostgreSqlNumFields - called on already destroyed wrapper.");
        return 0;
    }
}

//
// PostgresqlNumRows
//
const int Mt4PostgreSqlWrapper::PostgreSqlNumRows()
{
    return this->num_rows;
}

const int DllPostgreSqlNumRows(const int wrapper)
{
    try {
        Mt4PostgreSqlWrapper * const _wrapper = GetMt4PostgreSqlWrapper(wrapper);
        return _wrapper->PostgreSqlNumRows();
    } catch (...) {
        FatalErrorMessageBox(L"DllPostgreSqlNumRows - called on already destroyed wrapper.");
        return 0;
    }
}

//
// PostgreSqlQuery
//
const bool Mt4PostgreSqlWrapper::PostgreSqlQuery(const std::wstring query)
{
    std::wstringstream log_message;

    if (!this->PostgreSqlCheckConnection()) {
        return false;
    }

    if (this->result != NULL) {
        this->PostgreSqlClearResult();
    }

    // TODO: use transactions

    std::string _query(query.begin(), query.end());
    this->result = PQexec(this->connection, _query.c_str());

    log_message << "SQL: " << query;
    this->WriteLog(log_message);
    switch (PQresultStatus(this->result))
    {
        case PGRES_EMPTY_QUERY: {
            log_message << "ERROR: empty query";
            this->PostgreSqlClearResult();
            break;
        }
        case PGRES_COMMAND_OK: {
            AnsiToUnicode(PQcmdTuples(this->result), &this->affected_rows);
            if (!this->affected_rows.empty()) {
                log_message << "OK: " << this->affected_rows << " affected row(s)";
            } else {
                log_message << "OK: nothing returned";
            }
            // clear result manualy
            break;
        }
        case PGRES_TUPLES_OK: {
            this->num_rows = PQntuples(this->result);
            this->num_fields = PQnfields(this->result);
            log_message << "OK: returned " << this->num_rows << " rows (" << this->num_fields << " fields)";
            // clear result manualy
            break;
        }
        case PGRES_BAD_RESPONSE:
        case PGRES_NONFATAL_ERROR:
        case PGRES_FATAL_ERROR: {
            log_message << PQresultErrorMessage(this->result) << std::endl;
            this->PostgreSqlClearResult();
            this->WriteLog(log_message);
            return false;
        }
    }
    this->WriteLog(log_message);

    return true;
}

const bool DllPostgreSqlQuery(const int wrapper, wchar_t const * const query)
{
    try {
        Mt4PostgreSqlWrapper * const _wrapper = GetMt4PostgreSqlWrapper(wrapper);
        return _wrapper->PostgreSqlQuery(query);
    } catch (...) {
        FatalErrorMessageBox(L"DllPostgreSqlQuery - called on already destroyed wrapper.");
        return false;
    }
}

//
// PostgreSqlServerVersion
//
const int Mt4PostgreSqlWrapper::PostgreSqlServerVersion()
{
    return PQserverVersion(this->connection);
}

const int DllPostgreSqlServerVersion(const int wrapper)
{
    try {
        Mt4PostgreSqlWrapper * const _wrapper = GetMt4PostgreSqlWrapper(wrapper);
        return _wrapper->PostgreSqlServerVersion();
    } catch (...) {
        FatalErrorMessageBox(L"DllPostgreSqlServerVersion - called on already destroyed wrapper.");
        return 0;
    }
}

//
// WrapperLogFile
//
void Mt4PostgreSqlWrapper::WrapperLogFile(const std::string log_file)
{
    this->log_file = log_file;
}

void DllWrapperLogFile(const int wrapper, const wchar_t * log_file)
{
    try {
        Mt4PostgreSqlWrapper * const _wrapper = GetMt4PostgreSqlWrapper(wrapper);
        std::string _log_file;
        UnicodeToAnsi(std::wstring(log_file), &_log_file);
        _wrapper->WrapperLogFile(_log_file);
    } catch (...) {
        FatalErrorMessageBox(L"DllWrapperLogFile - called on already destroyed wrapper.");
    }
}

//
// WrapperLogPrefix
//
void Mt4PostgreSqlWrapper::WrapperLogPrefix(const std::string log_prefix)
{
    this->log_prefix = log_prefix;
}

void DllWrapperLogPrefix(const int wrapper, const wchar_t * log_prefix)
{
    try {
        Mt4PostgreSqlWrapper * const _wrapper = GetMt4PostgreSqlWrapper(wrapper);
        std::string _log_prefix;
        UnicodeToAnsi(std::wstring(log_prefix), &_log_prefix);
        _wrapper->WrapperLogPrefix(_log_prefix);
    } catch (...) {
        FatalErrorMessageBox(L"DllWrapperLogPrefix - called on already destroyed wrapper.");
    }
}

//
// WrapperLogToStdout
//
void Mt4PostgreSqlWrapper::WrapperLogToStdout(const bool log_to_stdout)
{
    this->log_to_stdout = log_to_stdout;
}

void DllWrapperLogToStdout(const int wrapper, const bool log_to_stdout)
{
    try {
        Mt4PostgreSqlWrapper * const _wrapper = GetMt4PostgreSqlWrapper(wrapper);
        _wrapper->WrapperLogToStdout(log_to_stdout);
    } catch (...) {
        FatalErrorMessageBox(L"DllWrapperLogToStdout - called on already destroyed wrapper.");
    }
}

//
// WrapperVersion
//
const wchar_t * DllWrapperVersion()
{
    return WRAPPER_VERSION;
}

//
// WriteLog
//
void Mt4PostgreSqlWrapper::WriteLog(std::wstringstream & log_message)
{
    std::string _log_message;
    UnicodeToAnsi(log_message.str(), &_log_message);

    SYSTEMTIME st;
    std::stringstream timestamp;
    std::stringstream formatted_message;
    std::wstringstream error_message;
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
    
    if (!this->log_file.empty()) {
        HANDLE _log_file_handle = CreateFileA(
            this->log_file.c_str(), FILE_APPEND_DATA, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL
        );
        if (_log_file_handle == INVALID_HANDLE_VALUE) {
            error_message << "Cannot create file: " << this->log_file.c_str() << " (Error: " << GetLastError() << ")";
            this->log_file = "";
            FatalErrorMessageBox(error_message.str());
        } else {
            WriteFile(_log_file_handle, formatted_message.str().c_str(), strlen(formatted_message.str().c_str()), &bytes_writen, NULL);
        }
    }

    log_message.str(L"");
    return;
}

void DllWrapperWriteLog(const int wrapper, const wchar_t * log_message)
{
    try {
        Mt4PostgreSqlWrapper * const _wrapper = GetMt4PostgreSqlWrapper(wrapper);
        std::wstringstream _log_message;
        _log_message << log_message;
        return _wrapper->WriteLog(_log_message);
    } catch (...) {
        FatalErrorMessageBox(L"DllWrapperWriteLog - called on already destroyed wrapper.");
    }
}