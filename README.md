# Mt4PostgreSqlWrapper
PostgreSQL wrapper for MetaTrader4 (build >= 600) with independed logger.

## MQL4 example use
```c++
Logger * logger = new Logger("C:\\test.log", StringSubstr(Symbol(), 0, 6));
PostgreSql * psql = new PostgreSql("host=localhost user=postgres dbname=test", logger.GetLogger());

Print("query = " + psql.Query("SELECT * FROM _test_data_table"));
Print("num_rows = " + psql.NumRows());
Print("num_fields = " + psql.NumFields());
string fields[];
Print("fetchrow = " + psql.FetchRow(fields, 0));
for (int i = 0; i < psql.NumFields(); i++)
    Print("field[" + i + "] = " + field[i]);

delete psql;
delete logger;
```

## MQL4 example implementation
### Logger.mqh
```c++
//
// Logger.mqh
//
#property copyright "axdel"
#property link      "https://github.com/axdel/Mt4PostgreSqlWrapper"
#property strict

#import "Mt4PostgreSqlWrapper.dll"
    void DllLoggerDestroy(const int logger);
    const int DllLoggerInit(const string log_file, const string log_prefix);
    const int DllLoggerGetLogger(const int logger);
    void DllLoggerWriteLog(const int logger, const string log_message);
#import

class Logger
{
private:
    int logger;
    
public:
    Logger(const string log_file, const string log_prefix = "");
    ~Logger();
    
    const int GetLogger();
    
    void Debug(const string log_message) { this.WriteLog("DEBUG: " + log_message); }
    void Info(const string log_message) { this.WriteLog("INFO: " + log_message); }
    void Warning(const string log_message) { this.WriteLog("WARNING: " + log_message); }
    void Error(const string log_message) { this.WriteLog("ERROR: " + log_message); }
    void Critical(const string log_message) { this.WriteLog("CRITICAL: " + log_message); }
    
    void WriteLog(const string log_message);
};

//
// Logger
//
Logger::Logger(const string log_file, const string log_prefix = "")
{
    this.logger = DllLoggerInit(log_file, log_prefix);
}

//
// ~Logger
//
Logger::~Logger()
{
    DllLoggerDestroy(this.logger);
}

//
// GetLogger
//
const int Logger::GetLogger()
{
    return DllLoggerGetLogger(this.logger);
}

//
// WriteLog
//
Logger::WriteLog(const string log_message)
{
    DllLoggerWriteLog(this.logger, log_message);
}
```

### PostgreSql.mqh

```c++
//
// PostgreSql.mqh
//
#property copyright "axdel"
#property link      "https://github.com/axdel/Mt4PostgreSqlWrapper"
#property strict

#include "Logger.mqh"

#import "Mt4PostgreSqlWrapper.dll"
    void DllPostgreSqlDestroy(const int wrapper);
    const int DllPostgreSqlInit(const string connection_string, const int logger);
    void DllPostgreSqlAffectedRows(const int wrapper, string & affected_rows);
    void DllPostgreSqlClearResult(const int wrapper);
    const int DllPostgreSqlClientVersion();
    void DllPostgreSqlClose(const int wrapper);
    const bool DllPostgreSqlConnect(const int wrapper, const string connection_string);
    const bool DllPostgreSqlFetchField(const int wrapper, string & field, const int row_num, const int field_num);
    void DllPostgreSqlFieldList(const int wrapper, string & field_list);
    const int DllPostgreSqlNumFields(const int wrapper);
    const int DllPostgreSqlNumRows(const int wrapper);
    const bool DllPostgreSqlQuery(const int wrapper, const string query);
    const int DllPostgreSqlServerVersion(const int wrapper);
    void DllPostgreSqlSetLogger(const int wrapper, const int logger);
    void DllPostgreSqlWriteLog(const int wapper, const string log_message);
    const string DllPostgreSqlWrapperVersion();
#import

const int BUFFER_SIZE = 1024;

class PostgreSql
{
private:
    int wrapper;
    
public:
    PostgreSql(const string connection_string, const int logger = NULL);
    ~PostgreSql();
    
    void AffectedRows(string & affected_rows);
    void ClearResult();
    const int ClientVersion();
    void Close();
    const bool Connect(const string connection_string);
    const bool FetchField(string & field, const int row_num, const int field_num);
    const bool FetchRow(string & row[], const int row_num);
    void FieldList(string & field_list);
    const int NumFields();
    const int NumRows();
    const bool Query(string query);
    const int ServerVersion();
    
    void SetLogger(const int logger);
    void Debug(const string log_message) { this.WriteLog("DEBUG: " + log_message); }
    void Info(const string log_message) { this.WriteLog("INFO: " + log_message); }
    void Warning(const string log_message) { this.WriteLog("WARNING: " + log_message); }
    void Error(const string log_message) { this.WriteLog("ERROR: " + log_message); }
    void Critical(const string log_message) { this.WriteLog("CRITICAL: " + log_message); }
    void WriteLog(const string message);
    
    const string WrapperVersion();
};

//
// PostgreSql
//
PostgreSql::PostgreSql(const string connection_string, const int logger = NULL)
{
    this.wrapper = DllPostgreSqlInit(connection_string, logger);
}

//
// ~PostgreSql
//
PostgreSql::~PostgreSql()
{
    DllPostgreSqlDestroy(this.wrapper);
}

//
// AffectedRows
//
void PostgreSql::AffectedRows(string & affected_rows)
{
    DllPostgreSqlAffectedRows(this.wrapper, affected_rows);
}

//
// ClearResult
//
void PostgreSql::ClearResult()
{
    DllPostgreSqlClearResult(this.wrapper);
}

//
// ClientVersion
//
const int PostgreSql::ClientVersion()
{
    return DllPostgreSqlClientVersion();
}

//
// Close
//
void PostgreSql::Close()
{
    DllPostgreSqlClose(this.wrapper);
}

//
// Connect
//
const bool PostgreSql::Connect(const string connection_string)
{
    return DllPostgreSqlConnect(this.wrapper, connection_string);
}

//
// FetchField
//
const bool PostgreSql::FetchField(string & field, const int row_num, const int field_num)
{
    StringInit(field, BUFFER_SIZE, 0);
    return DllPostgreSqlFetchField(this.wrapper, field, row_num, field_num);
}

//
// FetchRow
//
const bool PostgreSql::FetchRow(string & row[], const int row_num)
{
    bool fetch_successful = true;
    int num_fields = this.NumFields();
    if (ArrayResize(row, num_fields) == num_fields) {
        this.WriteLog("Fetching row: " + row_num);
        for (int i = 0; i < num_fields; i++) {
            if (!this.FetchField(row[i], row_num, i)) {
                fetch_successful = false;
            }
        }
        return fetch_successful;
    } else {
        this.Error("Cannot resize array (Error code:" + GetLastError()+ ")");
        return false;
    }
}

//
// FieldList
//
void PostgreSql::FieldList(string & field_list)
{
    StringInit(field_list, BUFFER_SIZE, 0);
    DllPostgreSqlFieldList(this.wrapper, field_list);
}

//
// NumFields
//
const int PostgreSql::NumFields()
{
    return DllPostgreSqlNumFields(this.wrapper);
}

//
// NumRows
//
const int PostgreSql::NumRows()
{
    return DllPostgreSqlNumRows(this.wrapper);
}

//
// Query
//
const bool PostgreSql::Query(string query)
{
    return DllPostgreSqlQuery(this.wrapper, query);
}

//
// ServerVersion
//
const int PostgreSql::ServerVersion()
{
    return DllPostgreSqlServerVersion(this.wrapper);
}

//
// WrapperVersion
//
const string PostgreSql::WrapperVersion()
{
    return DllPostgreSqlWrapperVersion();
}

//
// WriteLog
//
void PostgreSql::WriteLog(const string log_message)
{
    DllPostgreSqlWriteLog(this.wrapper, log_message);
}

//
// SetLogger
//
void PostgreSql::SetLogger(const int logger)
{
    DllPostgreSqlSetLogger(this.wrapper, logger);
}
```
