# Mt4PostgreSqlWrapper
PostgreSQL wrapper for MetaTrader4 (build >= 600) with independed logger.

Licence: http://www.wtfpl.net/txt/copying/

## MQL4 example use
```c++
#property strict

#include <Logger.mqh>
#include <Postgresql.mqh>

void OnStart()
{
    Logger * logger = new Logger("C:\\test.log", "[" + Symbol() + "]");
    logger.Info("logger & message box test...", true);
    
    PostgreSql * psql = new PostgreSql("host=localhost user=test dbname=test", logger);
    
    Print("query = " + psql.Query("SELECT * FROM _test_data_table"));
    Print("num_rows = " + psql.NumRows());
    Print("num_fields = " + psql.NumFields());
    string fields[];
    Print("fetchrow = " + psql.FetchRow(fields, 0));
    for (int i = 0; i < psql.NumFields(); i++)
       Print("field[" + i + "] = " + fields[i]);
    
    delete psql;
    delete logger;
}
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
    void DllLoggerDebug(const int logger, const string log_message, const bool message_box);
    void DllLoggerInfo(const int logger, const string log_message, const bool message_box);
    void DllLoggerWarning(const int logger, const string log_message, const bool message_box);
    void DllLoggerError(const int logger, const string log_message, const bool message_box);
    void DllLoggerCritical(const int logger, const string log_message, const bool message_box);
#import

#include <Common.mqh>

class Logger
{
private:
    int logger;

public:
    Logger(const string log_file, const string log_prefix = "") {
        this.logger = DllLoggerInit(log_file, log_prefix);
    }
    ~Logger() {
        DllLoggerDestroy(this.logger);
    }

    const int GetLogger() {
        return DllLoggerGetLogger(this.logger);
    }
    
    void Debug(const string log_message, const bool message_box = false) {
        DllLoggerDebug(this.logger, log_message, message_box);
    }
    void Info(const string log_message, const bool message_box = false) {
        DllLoggerInfo(this.logger, log_message, message_box);
    }
    void Warning(const string log_message, const bool message_box = false) {
        DllLoggerWarning(this.logger, log_message, message_box);
    }
    void Error(const string log_message, const bool message_box = false) {
        DllLoggerError(this.logger, log_message, message_box);
    }
    void Critical(const string log_message, const bool message_box = false) {
        DllLoggerCritical(this.logger, log_message, message_box);
    }
};
```

### PostgreSql.mqh

```c++
//
// PostgreSql.mqh
//
#property copyright "axdel"
#property link      "https://github.com/axdel/Mt4PostgreSqlWrapper"
#property strict

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
    const string DllPostgreSqlWrapperVersion();
#import

#include <Common.mqh>
#include <Logger.mqh>

const int BUFFER_SIZE = 1024;

class PostgreSql
{
private:
    int wrapper;
    Logger * logger;
    
public:

    PostgreSql(const string connection_string, Logger * _logger);
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
    const string WrapperVersion();
};

//
// PostgreSql
//
PostgreSql::PostgreSql(const string connection_string, Logger * _logger)
{
    this.logger = _logger;
    this.wrapper = DllPostgreSqlInit(connection_string, this.logger.GetLogger());
}

//
// ~PostgreSql
//
PostgreSql::~PostgreSql()
{
    delete(this.logger);
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
    int num_fields = this.NumFields();
    if (num_fields == 0) {
        return false;
    }
 
    bool message_box = false;
    if (DEBUG) { message_box = true; }
    
    if (ArrayResize(row, num_fields) == num_fields) {
        this.logger.Debug("fetching row: " + row_num);
        for (int i = 0; i < num_fields; i++) {
            if (!this.FetchField(row[i], row_num, i)) {
                this.logger.Error("cannot fetch row: " + row_num + " field: " + i, message_box);
                return false;
            }
        }
        return true;
    } else {
        this.logger.Error("cannot resize array (error code:" + GetLastError()+ ")", message_box);
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
```
