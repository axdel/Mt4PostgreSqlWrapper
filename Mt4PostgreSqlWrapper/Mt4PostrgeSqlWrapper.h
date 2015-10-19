#include <ctime>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>
#include <Windows.h>

#include "libpq-fe.h" 

const wchar_t WRAPPER_VERSION[] = L"0.1";
const wchar_t NOT_AVAILABLE[] = L"N_A";

const int MAX_RECONNECT_ATTEMPTS = 2;
const int SLEEP_RECONNECT_FAILED = 1000;

class Mt4PostgreSqlWrapper
{
private:
    PGconn * connection = NULL;
    std::wstring connection_string = L"";
    std::string _connection_string = "";

    PGresult * result = NULL;
    int num_rows = 0;
    int num_fields = 0;
    std::wstring affected_rows = L"";

    bool log_to_stdout = true;
    std::string log_file = "";
    std::string log_prefix = "";

    const bool PostgreSqlCheckConnection();

public:
    Mt4PostgreSqlWrapper();
    ~Mt4PostgreSqlWrapper();

    const std::wstring PostgreSqlAffectedRows();
    void PostgreSqlClearResult();
    const int PostgreSqlClientVersion();
    void PostgreSqlClose();
    const bool PostgreSqlConnect(const std::wstring connection_string);
    const bool PostgreSqlFetchRow(wchar_t ** const row, const int row_number);
    const std::wstring PostgreSqlFieldList();
    void PostgreSqlLog(const std::wstring message);
    const int PostgreSqlNumFields();
    const int PostgreSqlNumRows();
    const bool PostgreSqlQuery(const std::wstring query);
    const int PostgreSqlServerVersion();

    void WrapperLogFile(const std::string log_file);
    void WrapperLogPrefix(const std::string log_prefix);
    void WrapperLogToStdout(const bool log_stdout);
    void WriteLog(std::wstringstream & log_message);
};

//
// DLLAPI
//
#define DLLAPI extern "C" __declspec(dllexport)

DLLAPI void DllWrapperDestroy(const int wrapper);
DLLAPI const int DllWrapperInit();
DLLAPI void DllWrapperLogFile(const int wrapper, const wchar_t * const log_file);
DLLAPI void DllWrapperLogPrefix(const int wrapper, const wchar_t * const log_prefix);
DLLAPI void DllWrapperLogToStdout(const int wrapper, const bool log_stdout);
DLLAPI const wchar_t * DllWrapperVersion();
DLLAPI void DllWrapperWriteLog(const int wapper, const wchar_t * const message);

DLLAPI void DllPostgreSqlAffectedRows(const int wrapper, wchar_t * const affected_rows);
DLLAPI void DllPostgreSqlClearResult(const int wrapper);
DLLAPI const int DllPostgreSqlClientVersion();
DLLAPI void DllPostgreSqlClose(const int wrapper);
DLLAPI const bool DllPostgreSqlConnect(const int wrapper, const wchar_t * const connection_string);
DLLAPI const bool DllPostgreSqlFetchRow(const int wrapper, wchar_t ** const row, const int row_number);
DLLAPI void DllPostgreSqlFieldList(const int wrapper, wchar_t * const field_list);
DLLAPI const int DllPostgreSqlNumFields(const int wrapper);
DLLAPI const int DllPostgreSqlNumRows(const int wrapper);
DLLAPI const bool DllPostgreSqlQuery(const int wrapper, const wchar_t * const query);
DLLAPI const int DllPostgreSqlServerVersion(const int wrapper);