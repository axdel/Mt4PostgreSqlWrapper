//
// NOTES:
//    - test asumes a database with name "test" exists
//
#include "stdafx.h"

int wmain(int argc, wchar_t * argv[])
{
    size_t BUFFER_SIZE = 1024;	// max string size

    std::wstring _test_data_table = L"_test_data_table";
    std::wstringstream query;

    const int wrapper = DllWrapperInit();
    DllWrapperLogPrefix(wrapper, L"EURUSD");
    DllWrapperLogFile(wrapper, L"C:\\test.log");

    // CASE: UNSUCCESSFUL CONNECTION
    std::wcout << std::endl << "CASE: UNSUCCESSFUL CONNECTION" << std::endl;
    DllPostgreSqlConnect(wrapper, L"host=localhost user=bad_user dbname=bad_database");
    DllPostgreSqlClose(wrapper);
    DllPostgreSqlClose(wrapper);

    // CASE: WRITE LOG
    std::wcout << std::endl << "CASE: WRITE LOG" << std::endl;
    DllWrapperWriteLog(wrapper, L"Is this the most important message or what?");

    // CASE: SUCCESSFUL CONNECTION
    std::wcout << std::endl << "CASE: SUCCESSFUL CONNECTION" << std::endl;
    DllPostgreSqlConnect(wrapper, L"host=localhost user=postgres dbname=test");

    std::wcout << "client version = " << DllPostgreSqlClientVersion() << std::endl;
    std::wcout << "server version = " << DllPostgreSqlServerVersion(wrapper) << std::endl;

    // CASE: EMPTY QUERY
    std::wcout << std::endl << "CASE: EMPTY QUERY" << std::endl;
    DllPostgreSqlQuery(wrapper, L"");
    DllPostgreSqlClearResult(wrapper);

    // CASE: DROP TABLE IF EXISTS
    std::wcout << std::endl << "CASE: DROP TABLE IF EXISTS" << std::endl;
    query << "DROP TABLE IF EXISTS \"" << _test_data_table << "\"";
    DllPostgreSqlQuery(wrapper, query.str().c_str());
    query.str(L"");

    // CASE: CREATE TABLE
    std::wcout << std::endl << "CASE: CREATE TABLE" << std::endl;
    query << "CREATE TABLE \"" << _test_data_table << "\" ("
        << "id SERIAL NOT NULL,"
        << "symbol VARCHAR,"
        << "timeframe INTEGER,"
        << "open NUMERIC(10, 5),"
        << "high NUMERIC(10, 5),"
        << "low NUMERIC(10, 5),"
        << "close NUMERIC(10, 5)," 
        << "PRIMARY KEY (id)"
        << ")";
    DllPostgreSqlQuery(wrapper, query.str().c_str());
    query.str(L"");

    // CASE: INSERT RANDOM DATA
    std::wcout << std::endl << "CASE: INSERT RANDOM DATA" << std::endl;
    std::vector<std::wstring> SYMBOLS = {L"EURUSD", L"USDJPY", L"GBPUSD", L"USDCHF"};
    std::vector<int> TIMEFRAMES = {5, 15, 30, 60, 240, 1440};
    srand(static_cast<unsigned int>(time(0)));
    wchar_t * const affected_rows = new wchar_t[BUFFER_SIZE];
    for (int i = 0; i < 10; i++) {
        query << "INSERT INTO \"" << _test_data_table << "\" (\"symbol\", \"timeframe\", \"open\", \"high\", \"low\", \"close\") ";
        query << "VALUES ('"
            << SYMBOLS[rand() % SYMBOLS.size()] << "', "
            << TIMEFRAMES[rand() % TIMEFRAMES.size()] << ", "
            << (1.0 + rand()/(RAND_MAX/1.0)) << ", "
            << (1.0 + rand()/(RAND_MAX/1.0)) << ", "
            << (1.0 + rand()/(RAND_MAX/1.0)) << ", "
            << (1.0 + rand()/(RAND_MAX/1.0)) << ")";
        DllPostgreSqlQuery(wrapper, query.str().c_str());
        DllPostgreSqlAffectedRows(wrapper, affected_rows);
        std::wcout << "affected_rows = " << affected_rows << std::endl;
        query.str(L"");
    }

    // CREATE TABLE
    // INSERT, UPDATE, DELETE
    // DROP TABLE
    // CASE: CREATE UNIQUE INDEX
    // CASE: CREATE IMPOSSIBLE UNIQUE INDEX
    // CASE: CAUSE INSERT COLLISION
    // CASE: CAUSE UPDATE COLLISION
    // CASE: DELETE
    // CASE: DELETE NON-EXISTENT

    // CASE: SELECT * FROM
    std::wcout << std::endl << "CASE: SELECT * FROM" << std::endl;
    query << "SELECT * FROM \"" << _test_data_table << "\" LIMIT 5";
    DllPostgreSqlQuery(wrapper,	query.str().c_str());
    query.str(L"");
    int num_rows = DllPostgreSqlNumRows(wrapper);
    int num_fields = DllPostgreSqlNumFields(wrapper);
    std::wcout << "num_rows = " << num_rows << ", num_fields = " << num_fields << std::endl;
    DllPostgreSqlAffectedRows(wrapper, affected_rows);
    std::wcout << "affected_rows = " << affected_rows << std::endl;

    // CASE: GET FIELD LIST
    std::wcout << std::endl << "CASE: GET FIELD LIST" << std::endl;
    wchar_t * const field_list = new wchar_t[BUFFER_SIZE];
    DllPostgreSqlFieldList(wrapper, field_list);
    std::wcout << "field_list = " << field_list << std::endl;

    // CASE: FETCH ROW(S)
    std::wcout << std::endl << "CASE: FETCH ROW(S)" << std::endl;
    wchar_t ** row = new wchar_t * [num_fields];
    for (int i = 0; i < num_fields; i++) { row[i] = new wchar_t[BUFFER_SIZE]; }
    for (int i = 0; i < num_rows; i++) {
        std::wcout << "fetching row " << (i + 1) << " of " << num_rows << std::endl;
        DllPostgreSqlFetchRow(wrapper, row, i);
        for (int j = 0; j < num_fields; j++) {
            std::wcout << "field[" << i << "][" << j << "] = " << row[j] << std::endl;
        }
        std::wcout << std::endl;
    }

    // CASE: FIELD LIST, FETCH ROW(S) ON CLEARED RESULT
    DllPostgreSqlClearResult(wrapper);

    // CASE: FIELD LIST ON CLEARED RESULT
    std::wcout << std::endl << "CASE: FIELD LIST ON CLEARED RESULT" << std::endl;
    DllPostgreSqlFieldList(wrapper, field_list);
    std::wcout << "field_list = " << field_list << std::endl;

    // CASE: FETCH ROW(S) ON CLEARED RESULT
    std::wcout << std::endl << "CASE: FETCH ROW(S) ON CLEARED RESULT" << std::endl;
    for (int i = 0; i < num_rows; i++) {
        std::wcout << "fetching row " << (i + 1) << " of " << num_rows << std::endl;
        DllPostgreSqlFetchRow(wrapper, row, i);
        for (int j = 0; j < num_fields; j++) {
            std::wcout << "field[" << i << "][" << j << "] = " << row[j] << std::endl;
        }
        std::wcout << std::endl;
    }

    // CASE: FETCH NON-EXISTENT ROW
    std::wcout << std::endl << "CASE: FETCH NON-EXISTENT ROW" << std::endl;
    DllPostgreSqlFetchRow(wrapper, row, 100);
    for (int i = 0; i < num_fields; i++) {
        std::wcout << "field[" << i << "] = " << row[i] << std::endl;
    }

    // CASE: UNSUCCESSFUL SELECT

    // CASE: SUCCESSFUL CLOSE
    DllPostgreSqlClose(wrapper);

    // CASE: QUERY ON CLOSED CONNECTION (SHOULD TRY RECONNECT)
    std::wcout << std::endl << "CASE: QUERY ON CLOSED CONNECTION (SHOULD TRY RECONNECT)" << std::endl;
    query << "SELECT * FROM \"" << _test_data_table << "\" LIMIT 5";
    DllPostgreSqlQuery(wrapper,	query.str().c_str());
    query.str(L"");
    
    // CASE: CLOSE ALREADY CLOSED CONNECTION
    std::wcout << std::endl << "CASE: CLOSE ALREADY CLOSED CONNECTION" << std::endl;
    DllPostgreSqlClose(wrapper);
    DllPostgreSqlClose(wrapper);
    
    DllWrapperDestroy(wrapper);

    std::wcout << std::endl << "SUCCESS, HIT SOME KEY AND ENTER" << std::endl;
    wchar_t c;
    std::wcin >> c;

    return 0;
}