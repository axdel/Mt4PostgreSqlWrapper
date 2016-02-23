//
// NOTES:
//    - test asumes a database with name "test" exists
//
#include <vector>

#include "Common.h"
#include "Logger.h"
#include "PostgreSql.h"

int wmain(int argc, wchar_t * argv[])
{
    size_t BUFFER_SIZE = 1024;	// max string size

    std::wstring _test_data_table = L"_test_data_table";
    std::wstringstream query;

    const int logger = DllLoggerInit(L"C:\\Logs\\dll-test.log", L"[wrapper]");
    DllLoggerLogToStdout(logger, true);
    DllLoggerLogDebug(logger, true);

    const int wrapper = DllPostgreSqlInit(logger);

    // CASE: QUERY ON UNKNOWN DATABASE
    std::wcout << std::endl << "CASE: QUERY ON UNKNOWN DATABASE" << std::endl;
    DllPostgreSqlQuery(wrapper, L"SELECT 1");

    // CASE: FAILED CONNECTION CHECK
    std::wcout << std::endl << "CASE: FAILED CONNECTION CHECK" << std::endl;
    bool conneciton_check = DllPostgreSqlCheckConnection(wrapper);
    std::wcout << conneciton_check << std::endl;

    // CASE: UNSUCCESSFUL CONNECTION
    std::wcout << std::endl << "CASE: UNSUCCESSFUL CONNECTION" << std::endl;
    DllPostgreSqlConnect(wrapper, L"host=localhost user=bad_user dbname=bad_database");
    DllPostgreSqlClose(wrapper);

    // CASE: WRITE LOG
    std::wcout << std::endl << "CASE: WRITE LOG" << std::endl;
    DllLoggerInfo(logger, L"This is info message from logger");

    // CASE: SUCCESSFUL CONNECTION
    std::wcout << std::endl << "CASE: SUCCESSFUL CONNECTION" << std::endl;
    //DllPostgreSqlConnect(wrapper, L"host=192.168.0.107 user=test dbname=test");
    //DllPostgreSqlConnect(wrapper, L"host=172.16.42.4 user=test dbname=test");
    DllPostgreSqlConnect(wrapper, L"host=10.0.1.14 user=test dbname=test");

    std::wcout << "client version = " << DllPostgreSqlClientVersion(wrapper) << std::endl;
    std::wcout << "server version = " << DllPostgreSqlServerVersion(wrapper) << std::endl;

    // CASE: SUCCESSFUL CONNECTION CHECK
    std::wcout << std::endl << "CASE: SUCCESSFUL CONNECTION CHECK" << std::endl;
    conneciton_check = DllPostgreSqlCheckConnection(wrapper);
    std::wcout << conneciton_check << std::endl;

    // CASE: EMPTY QUERY
    std::wcout << std::endl << "CASE: EMPTY QUERY" << std::endl;
    DllPostgreSqlQuery(wrapper, L"");
    DllPostgreSqlClearResult(wrapper);

    // CASE: DROP TABLE IF EXISTS (UNCLEARED RESULT)
    std::wcout << std::endl << "CASE: DROP TABLE IF EXISTS (UNCLEARED RESULT)" << std::endl;
    query << "DROP TABLE IF EXISTS \"" << _test_data_table << "\"";
    DllPostgreSqlQuery(wrapper, query.str().c_str());
    query.str(L"");

    // CASE: CREATE TABLE (MULTI CLEAR)
    std::wcout << std::endl << "CASE: CREATE TABLE (MULTI CLEAR)" << std::endl;
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
    DllPostgreSqlClearResult(wrapper);
    DllPostgreSqlClearResult(wrapper);
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
        DllPostgreSqlClearResult(wrapper);
        query.str(L"");
    }

    // CASE: INSERT RANDOM DATA RETURNING ID
    std::wcout << std::endl << "CASE: INSERT RANDOM DATA RETURNING ID" << std::endl;
    wchar_t * returned_id = new wchar_t[BUFFER_SIZE]; // INSERT returns id
    query << "INSERT INTO \"" << _test_data_table << "\" (\"symbol\", \"timeframe\", \"open\", \"high\", \"low\", \"close\") ";
    query << "VALUES ('"
        << SYMBOLS[rand() % SYMBOLS.size()] << "', "
        << TIMEFRAMES[rand() % TIMEFRAMES.size()] << ", "
        << (1.0 + rand()/(RAND_MAX/1.0)) << ", "
        << (1.0 + rand()/(RAND_MAX/1.0)) << ", "
        << (1.0 + rand()/(RAND_MAX/1.0)) << ", "
        << (1.0 + rand()/(RAND_MAX/1.0)) << ") RETURNING \"id\"";
    DllPostgreSqlQuery(wrapper, query.str().c_str());
    DllPostgreSqlFetchField(wrapper, returned_id, 0, 0);
    std::wcout << "last_inserted_id = " << returned_id << std::endl;
    DllPostgreSqlClearResult(wrapper);
    query.str(L"");

    // CASE: UPDATE DATA
    std::wcout << std::endl << "CASE: UPDATE DATA" << std::endl;
    query << "UPDATE \"" << _test_data_table << "\" SET \"symbol\" = 'SVKCZK' WHERE \"id\" = " << returned_id[0];
    DllPostgreSqlQuery(wrapper, query.str().c_str());
    DllPostgreSqlAffectedRows(wrapper, affected_rows);
    std::wcout << "affected_rows = " << affected_rows << std::endl;
    DllPostgreSqlClearResult(wrapper);
    query.str(L"");

    // CASE: DELETE DATA
    std::wcout << std::endl << "CASE: DELETE DATA" << std::endl;
    query << "DELETE FROM \"" << _test_data_table << "\" WHERE \"id\" = " << returned_id[0];
    DllPostgreSqlQuery(wrapper, query.str().c_str());
    DllPostgreSqlAffectedRows(wrapper, affected_rows);
    std::wcout << "affected_rows = " << affected_rows << std::endl;
    DllPostgreSqlClearResult(wrapper);
    query.str(L"");

    // CASE: UPDATE NON-EXISTENT DATA
    std::wcout << std::endl << "CASE: UPDATE NON-EXISTENT DATA" << std::endl;
    query << "UPDATE \"" << _test_data_table << "\" SET \"symbol\" = 'SVKCZK' WHERE \"id\" = " << returned_id[0];
    DllPostgreSqlQuery(wrapper, query.str().c_str());
    DllPostgreSqlAffectedRows(wrapper, affected_rows);
    std::wcout << "affected_rows = " << affected_rows << std::endl;
    DllPostgreSqlClearResult(wrapper);
    query.str(L"");

    // CASE: DELETE NON-EXISTENT DATA
    std::wcout << std::endl << "CASE: DELETE NON-EXISTENT DATA" << std::endl;
    query << "DELETE FROM \"" << _test_data_table << "\" WHERE \"id\" = " << returned_id[0];
    DllPostgreSqlQuery(wrapper, query.str().c_str());
    DllPostgreSqlAffectedRows(wrapper, affected_rows);
    std::wcout << "affected_rows = " << affected_rows << std::endl;
    DllPostgreSqlClearResult(wrapper);
    query.str(L"");

    // CASE: CREATE IMPOSSIBLE UNIQUE INDEX
    std::wcout << std::endl << "CASE: CREATE IMPOSSIBLE UNIQUE INDEX" << std::endl;
    query << "CREATE UNIQUE INDEX impossible_unique_index_idx ON \"" << _test_data_table << "\" (\"symbol\")";
    DllPostgreSqlQuery(wrapper, query.str().c_str());
    DllPostgreSqlAffectedRows(wrapper, affected_rows);
    std::wcout << "affected_rows = " << affected_rows << std::endl;
    DllPostgreSqlClearResult(wrapper);
    query.str(L"");

    // CASE: CREATE POSSIBLE UNIQUE INDEX
    std::wcout << std::endl << "CASE: CREATE POSSIBLE UNIQUE INDEX" << std::endl;
    query << "CREATE UNIQUE INDEX possible_unique_index_idx ON \"" << _test_data_table << "\" ";
    query << "(\"symbol\", \"timeframe\", \"open\")";  // unlikely to collide
    DllPostgreSqlQuery(wrapper, query.str().c_str());
    DllPostgreSqlAffectedRows(wrapper, affected_rows);
    std::wcout << "affected_rows = " << affected_rows << std::endl;
    DllPostgreSqlClearResult(wrapper);
    query.str(L"");

    // CASE: INSERT COLLISION
    std::wcout << std::endl << "CASE: INSERT COLLISION" << std::endl;
    query << "INSERT INTO \"" << _test_data_table << "\" (\"symbol\", \"timeframe\", \"open\", \"high\", \"low\", \"close\") ";
    query << "VALUES ('SVKCZK', 1993, 1.0, 1.0, 1.0, 1.0)";
    DllPostgreSqlQuery(wrapper, query.str().c_str());
    DllPostgreSqlClearResult(wrapper);
    DllPostgreSqlQuery(wrapper, query.str().c_str()); // collison on unique index
    DllPostgreSqlClearResult(wrapper);
    query.str(L"");

    // CASE: GET LAST ERROR (FROM SILENCED COLLISION)
    std::wcout << std::endl << "CASE: GET LAST ERROR (FROM SILENCED COLLISION)" << std::endl;
    wchar_t * last_error = new wchar_t[BUFFER_SIZE];
    DllPostgreSqlGetLastError(wrapper, last_error);
    std::wcout << "last_error = " << last_error << std::endl;

    // CASE: UPDATE COLLISION
    std::wcout << std::endl << "CASE: UPDATE COLLISION" << std::endl;
    query << "INSERT INTO \"" << _test_data_table << "\" (\"symbol\", \"timeframe\", \"open\", \"high\", \"low\", \"close\") ";
    query << "VALUES ('SVKCZK', 1993, 2.0, 2.0, 2.0, 2.0)";
    DllPostgreSqlQuery(wrapper, query.str().c_str());
    DllPostgreSqlClearResult(wrapper);
    query.str(L"");
    DllPostgreSqlGetLastError(wrapper, last_error); // last error on successful query
    std::wcout << "last_error = " << last_error << std::endl;
    query << "UPDATE \"" << _test_data_table << "\" SET \"open\" = 1.0 WHERE \"open\" = 2.0";
    DllPostgreSqlQuery(wrapper, query.str().c_str()); // collison on unique index
    DllPostgreSqlClearResult(wrapper);
    query.str(L"");

    // CASE: SELECT * FROM
    std::wcout << std::endl << "CASE: SELECT * FROM" << std::endl;
    query << "SELECT * FROM \"" << _test_data_table << "\" LIMIT 5";
    DllPostgreSqlQuery(wrapper,	query.str().c_str());
    query.str(L"");
    int num_rows = DllPostgreSqlNumRows(wrapper);
    int num_fields = DllPostgreSqlNumFields(wrapper);
    std::wcout << "num_rows = " << num_rows << ", num_fields = " << num_fields << std::endl;
    DllPostgreSqlAffectedRows(wrapper, affected_rows);
    std::wcout << "affected_rows = " << affected_rows << std::endl; // will be "" after SELECT

    // CASE: GET FIELD LIST
    std::wcout << std::endl << "CASE: GET FIELD LIST" << std::endl;
    wchar_t * const field_list = new wchar_t[BUFFER_SIZE];
    DllPostgreSqlGetFieldList(wrapper, field_list);
    std::wcout << "field_list = " << field_list << std::endl;

    // CASE: FETCH FIELDS
    std::wcout << std::endl << "CASE: FETCH FIELDS" << std::endl;
    wchar_t ** row = new wchar_t * [num_fields];
    for (int i = 0; i < num_fields; i++) { row[i] = new wchar_t[BUFFER_SIZE]; }
    for (int i = 0; i < num_rows; i++) {
        std::wcout << "fetching row " << (i + 1) << " of " << num_rows << std::endl;
        for (int j = 0; j < num_fields; j++) {
            DllPostgreSqlFetchField(wrapper, row[j], i, j);
            std::wcout << "field[" << i << "][" << j << "] = " << row[j] << std::endl;
        }
        std::wcout << std::endl;
    }

    // CASE: FETCH NON-EXISTENT ROW/FIELD
    std::wcout << std::endl << "CASE: FETCH NON-EXISTENT ROW/FIELD" << std::endl;
    wchar_t * const field = new wchar_t[BUFFER_SIZE];
    DllPostgreSqlFetchField(wrapper, field, 100, 0);
    std::wcout << "field[0] row[100] = " << field << std::endl;
    DllPostgreSqlFetchField(wrapper, field, 0, 100);
    std::wcout << "field[100] row[0] = " << field << std::endl;

    // CASE: FIELD LIST, FETCH ROW(S) ON CLEARED RESULT
    DllPostgreSqlClearResult(wrapper);

    // CASE: FIELD LIST ON CLEARED RESULT
    std::wcout << std::endl << "CASE: FIELD LIST ON CLEARED RESULT" << std::endl;
    DllPostgreSqlGetFieldList(wrapper, field_list);
    std::wcout << "field_list = " << field_list << std::endl;

    // CASE: FETCH ROW(S) ON CLEARED RESULT
    std::wcout << std::endl << "CASE: FETCH ROW(S) ON CLEARED RESULT" << std::endl;
    for (int i = 0; i < DllPostgreSqlNumRows(wrapper); i++) {
        std::wcout << "fetching row " << (i + 1) << " of " << num_rows << std::endl;
        for (int j = 0; j < DllPostgreSqlNumFields(wrapper); j++) {
            DllPostgreSqlFetchField(wrapper, row[j], i, j);
            std::wcout << "field[" << i << "][" << j << "] = " << row[j] << std::endl;
        }
        std::wcout << std::endl;
    }

    // CASE: CLOSE CONNECTION
    std::wcout << std::endl << "CASE: CLOSE CONNECTION" << std::endl;
    DllPostgreSqlClose(wrapper);

    // CASE: QUERY ON CLOSED CONNECTION (SHOULD TRY RECONNECT)
    std::wcout << std::endl << "CASE: QUERY ON CLOSED CONNECTION (SHOULD TRY RECONNECT)" << std::endl;
    query << "SELECT * FROM \"" << _test_data_table << "\" LIMIT 5";
    DllPostgreSqlQuery(wrapper,	query.str().c_str());
    DllPostgreSqlClearResult(wrapper);
    query.str(L"");
    
    // CASE: CLOSE ALREADY CLOSED CONNECTION
    std::wcout << std::endl << "CASE: CLOSE ALREADY CLOSED CONNECTION" << std::endl;
    DllPostgreSqlClose(wrapper);
    DllPostgreSqlClose(wrapper);

    DllPostgreSqlDestroy(wrapper);
    // CASE: CALL QUERY ON DESTROYED WRAPPER
    std::wcout << std::endl << "CASE: CALL QUERY ON DESTROYED WRAPPER" << std::endl;
    query << "SELECT * FROM \"" << _test_data_table << "\" LIMIT 5";
    DllPostgreSqlQuery(wrapper,	query.str().c_str());
    query.str(L"");

    DllLoggerDestroy(logger);
    // CASE: WRITE LOG ON DESTROYED LOGGER
    std::wcout << std::endl << "CASE: WRITE LOG ON DESTROYED LOGGER" << std::endl;
    DllLoggerInfo(logger, L"This is info message from logger");

    std::wcout << std::endl << "SUCCESS, HIT SOME KEY AND ENTER" << std::endl;
    wchar_t c;
    std::wcin >> c;
 
    return 0;
}