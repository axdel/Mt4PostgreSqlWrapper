//
// NOTES:
//    - exception handling model has to be "/EHa"
//
#include "Common.h"
#include "Logger.h"
#include "PostgreSql.h"

//
// PostgreSqlInit
//
PostgreSql::PostgreSql(Logger * const logger)
{
    std::wstringstream log_message;
    log_message << "PostgreSQL wrapper created (wrapper: 0x" << this << ")";

    this->logger = logger;
    this->logger->Info(LOG(log_message));
}

const int DllPostgreSqlInit(const int logger)
{
    return reinterpret_cast<const int>(
        new PostgreSql(GetLogger(logger))
    );
}

//
// PostgreSqlDestroy
//
PostgreSql::~PostgreSql()
{
    std::wstringstream log_message;
    log_message << "PostgreSQL wrapper destroyed (wrapper: 0x" << this << ")";
    this->logger->Info(LOG(log_message));
}

DLLAPI void DllPostgreSqlDestroy(const int wrapper)
{
    try {
        PostgreSql * const _wrapper = GetPostgreSql(wrapper);
        _wrapper->Close();
        delete _wrapper;
    } catch (...) {
        FatalErrorMessageBox(L"DllPostgreSqlWrapperDestroy - called on already destroyed wrapper.");
    }
}

//
// AffectedRows
//
const std::wstring PostgreSql::AffectedRows()
{
    return this->affected_rows;
}

DLLAPI void DllPostgreSqlAffectedRows(const int wrapper, wchar_t * const affected_rows)
{
    try {
        PostgreSql  * const _wrapper = GetPostgreSql(wrapper);
        std::wstring _affected_rows = _wrapper->AffectedRows();
        wcscpy_s(affected_rows, (_affected_rows.length() + 1), _affected_rows.c_str());
    } catch (...) {
        FatalErrorMessageBox(L"DllPostgreSqlAffectedRows - called on already destroyed wrapper.");
    }
}

//
// ClearResult
//
void PostgreSql::ClearResult()
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
    this->logger->Debug(LOG(log_message));
}

DLLAPI void DllPostgreSqlClearResult(const int wrapper)
{
    try {
        PostgreSql * const _wrapper = GetPostgreSql(wrapper);
        _wrapper->ClearResult();
    } catch (...) {
        FatalErrorMessageBox(L"DllPostgreSqlClearResult - called on already destroyed wrapper.");
    }
}

//
// ClientVersion
//
const int PostgreSql::ClientVersion()
{
    return PQlibVersion();
}

DLLAPI const int DllPostgreSqlClientVersion(const int wrapper)
{
    try {
        PostgreSql * const _wrapper = GetPostgreSql(wrapper);
        return _wrapper->ClientVersion();
    }
    catch (...) {
        FatalErrorMessageBox(L"DllPostgreSqlClientVersion - called on already destroyed wrapper.");
        return 0;
    }
}

//
// Connect
//
const bool PostgreSql::Connect(const std::wstring connection_string, const int max_attempts, const int sleep)
{
    std::wstringstream log_message;

    this->connection_string = connection_string;
    UnicodeToAnsi(connection_string, &this->_connection_string);

    this->max_connection_attempts = max_attempts;
    this->failed_connection_sleep = sleep;

    int attempt = 1;
    int _max_attepts = this->max_connection_attempts;
    do {
        log_message << "Opening database connection (attempt: " << attempt << ") ... ";
        this->connection = PQconnectdb(this->_connection_string.c_str());
        if (PQstatus(this->connection) == CONNECTION_OK) {
            log_message << "opened (connection: 0x" << this->connection << ", wrapper: 0x" << this << ")";
            this->logger->Info(LOG(log_message));
            log_message << "PostgreSQL server " << this->ServerVersion() << " - connected with client " << this->ClientVersion() << " (wrapper-" << WRAPPER_VERSION << ")";
            this->logger->Info(LOG(log_message));
            return true;
        } else {
            log_message << "failed (connection: 0x" << this->connection << ", wrapper: 0x" << this << ")" << std::endl << PQerrorMessage(this->connection);
            this->logger->Error(LOG(log_message));
            Sleep(sleep);
        }
        attempt++;
    } while (PQstatus(this->connection) == CONNECTION_BAD && --_max_attepts);

    return false;
}

DLLAPI const bool DllPostgreSqlConnect(const int wrapper, const wchar_t * const connection_string, const int max_attempts, const int sleep)
{
    try {
        PostgreSql * const _wrapper = GetPostgreSql(wrapper);
        return _wrapper->Connect(connection_string, max_attempts, sleep);
    } catch (...) {
        FatalErrorMessageBox(L"DllPostgreSqlConnect - called on already destroyed wrapper.");
        return false;
    }
}

//
// CheckConnection
//
const bool PostgreSql::CheckConnection()
{
    std::wstringstream log_message;

    if (PQstatus(this->connection) == CONNECTION_OK) { return true; }

    if (this->connection_string.empty()) {
        log_message << "Cannot connect, connection string is empty (Connect(...) not called?)";
        this->logger->Error(LOG(log_message));
        return false;
    }

    log_message << "Connection dropped, trying to reconnect...";
    this->logger->Warning(LOG(log_message));
    this->Close();
    return this->Connect(this->connection_string, this->max_connection_attempts, this->failed_connection_sleep);
}

DLLAPI const bool DllPostgreSqlCheckConnection(const int wrapper)
{
    try {
        PostgreSql * const _wrapper = GetPostgreSql(wrapper);
        return _wrapper->CheckConnection();
    }
    catch (...) {
        FatalErrorMessageBox(L"DllPostgreSqlCheckConnection - called on already destroyed wrapper.");
        return false;
    }
}

//
// Close
//
void PostgreSql::Close()
{
    std::wstringstream log_message;

    log_message << "Closing connection (connection:0x" << this->connection << ", wrapper:0x" << this << ") ... ";
    if (this->connection != NULL) {
        PQfinish(this->connection);
        this->connection = NULL;
        log_message << "closed";
    } else {
        log_message << "was already closed";
    }
    this->logger->Info(LOG(log_message));
}

DLLAPI void DllPostgreSqlClose(const int wrapper)
{
    std::wstringstream log_message;

    try {
        PostgreSql * const _wrapper = GetPostgreSql(wrapper);
        _wrapper->Close();
    } catch (...) {
        FatalErrorMessageBox(L"DllPostgreSqlClose - called on already destroyed wrapper.");
    }
}

//
// FetchField
//
const bool PostgreSql::FetchField(wchar_t * const field, const int row_num, const int field_num)
{
    std::wstringstream log_message;
    std::wstring _field;

    if (this->result == NULL) {
        log_message << "Cannot fetch row: " << row_num << ", field: " << field_num;
        log_message << ", no active result found (probably cleared?)";
        this->logger->Error(LOG(log_message));
        return false;
    }
    if ((row_num + 1) > this->num_rows || (field_num + 1) > this->num_fields) {
        log_message << "Cannot fetch row: " << row_num << ", field: " << field_num;
        log_message << " (rows: " << this->num_rows << ", fields: " << this->num_fields << ")";
        this->logger->Error(LOG(log_message));
        wcscpy_s(field, 4, L"N_A");
        return false;
    }

    if (!PQgetisnull(this->result, row_num, field_num)) {
        AnsiToUnicode(PQgetvalue(this->result, row_num, field_num), &_field);
        wcscpy_s(field, (_field.length() + 1), _field.c_str());
    } else {
        wcscpy_s(field, 5, L"NULL");
    }
    
    return true;
}

DLLAPI const bool DllPostgreSqlFetchField(const int wrapper, wchar_t * field, const int row_num, const int field_num)
{
   try {
        PostgreSql * const _wrapper = GetPostgreSql(wrapper);
        return _wrapper->FetchField(field, row_num, field_num);
    } catch (...) {
        FatalErrorMessageBox(L"DllPostgreSqlFetchField - called on already destroyed wrapper.");
        return false;
    }
}

//
// GetFieldList
//
const std::wstring PostgreSql::GetFieldList()
{
    std::wstringstream log_message;
    std::wstringstream field_list;

    if (this->result == NULL) {
        log_message << "Cannot get field list - no active result found (probably cleared?)";
        this->logger->Error(LOG(log_message));
        return L"";
    }

    for (int i = 0; i < this->num_fields; i++) {
        field_list << "\"" << PQfname(this->result, i) << "\" ";
    }

    log_message << "Field list: " << field_list.str();
    this->logger->Debug(LOG(log_message));

    return field_list.str();
}

DLLAPI void DllPostgreSqlGetFieldList(const int wrapper, wchar_t * const field_list)
{
    try {
        PostgreSql * const _wrapper = GetPostgreSql(wrapper);
        std::wstring _field_list = _wrapper->GetFieldList();
        wcscpy_s(field_list, (_field_list.length() + 1), _field_list.c_str());
    } catch (...) {
        FatalErrorMessageBox(L"DllPostgreSqlGetFieldList - called on already destroyed wrapper.");
    }
}

//
// NumFields
//
const int PostgreSql::NumFields()
{
    return this->num_fields;
}

DLLAPI const int DllPostgreSqlNumFields(const int wrapper)
{
    try {
        PostgreSql * const _wrapper = GetPostgreSql(wrapper);
        return _wrapper->NumFields();
    } catch (...) {
        FatalErrorMessageBox(L"DllPostgreSqlNumFields - called on already destroyed wrapper.");
        return 0;
    }
}

//
// NumRows
//
const int PostgreSql::NumRows()
{
    return this->num_rows;
}

DLLAPI const int DllPostgreSqlNumRows(const int wrapper)
{
    try {
        PostgreSql * const _wrapper = GetPostgreSql(wrapper);
        return _wrapper->NumRows();
    } catch (...) {
        FatalErrorMessageBox(L"DllPostgreSqlNumRows - called on already destroyed wrapper.");
        return 0;
    }
}

//
// Query
//
const bool PostgreSql::Query(const std::wstring query)
{
    std::wstringstream log_message;

    if (!this->CheckConnection()) {
        log_message << "Cannot query database - no database connection";
        this->logger->Error(LOG(log_message));
        return false;
    }

    if (this->result != NULL) {
        this->ClearResult();
        log_message << "Uncleared result before new query";
        this->logger->Warning(LOG(log_message));
    }

    std::string _query;
    UnicodeToAnsi(query, &_query);
    this->result = PQexec(this->connection, _query.c_str());

    if (query.empty()) {
        log_message << "SQL: empty query";
    }
    else {
        log_message << "SQL: " << query;
    }
    this->logger->Debug(LOG(log_message));
    
    switch (PQresultStatus(this->result))
    {
        case PGRES_EMPTY_QUERY: {
            // clear result manualy
            break;
        }
        case PGRES_COMMAND_OK: {
            AnsiToUnicode(PQcmdTuples(this->result), &this->affected_rows);
            if (!this->affected_rows.empty()) {
                log_message << this->affected_rows << " affected row(s)";
            } else {
                log_message << "Nothing returned";
            }
            this->logger->Debug(LOG(log_message));
            // clear result manualy
            break;
        }
        case PGRES_TUPLES_OK: {
            this->num_rows = PQntuples(this->result);
            this->num_fields = PQnfields(this->result);
            log_message << "Returned " << this->num_rows << " rows, " << this->num_fields << " fields";
            this->logger->Debug(LOG(log_message));
            // clear result manualy
            break;
        }
        case PGRES_BAD_RESPONSE:
            log_message << " PGRES_BAD_RESPONSE ";
        case PGRES_NONFATAL_ERROR:
            log_message << " PGRES_NONFATAL_ERROR ";
        case PGRES_FATAL_ERROR: {
            log_message << PQresultErrorMessage(this->result);
            this->logger->Error(LOG(log_message));
            this->ClearResult();
            return false;
        }
    }

    return true;
}

DLLAPI const bool DllPostgreSqlQuery(const int wrapper, wchar_t const * const query)
{
    try {
        PostgreSql * const _wrapper = GetPostgreSql(wrapper);
        return _wrapper->Query(query);
    } catch (...) {
        FatalErrorMessageBox(L"DllPostgreSqlQuery - called on already destroyed wrapper.");
        return false;
    }
}

//
// ServerVersion
//
const int PostgreSql::ServerVersion()
{
    return PQserverVersion(this->connection);
}

DLLAPI const int DllPostgreSqlServerVersion(const int wrapper)
{
    try {
        PostgreSql * const _wrapper = GetPostgreSql(wrapper);
        return _wrapper->ServerVersion();
    } catch (...) {
        FatalErrorMessageBox(L"DllPostgreSqlServerVersion - called on already destroyed wrapper.");
        return 0;
    }
}

//
// WrapperVersion
//
DLLAPI const wchar_t * const DllPostgreSqlWrapperVersion()
{
    return WRAPPER_VERSION;
}