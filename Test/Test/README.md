# Test stdout (should be pretty self-explanatory)

```
CASE: UNSUCCESSFUL CONNECTION

CASE: WRITE LOG
2015-10-23 11:45:44.206 [EURUSD] This is message from logger

CASE: SUCCESSFUL CONNECTION
2015-10-23 11:45:44.284 [EURUSD] This is again from postgresql
client version = 90404
server version = 90404

CASE: EMPTY QUERY
2015-10-23 11:45:44.347 [EURUSD] SQL:
2015-10-23 11:45:44.362 [EURUSD] Clearing result... cleared
2015-10-23 11:45:44.394 [EURUSD] ERROR: empty query
2015-10-23 11:45:44.425 [EURUSD] Clearing result... was already cleared

CASE: DROP TABLE IF EXISTS
2015-10-23 11:45:44.472 [EURUSD] SQL: DROP TABLE IF EXISTS "_test_data_table"
2015-10-23 11:45:44.487 [EURUSD] OK: nothing returned

CASE: CREATE TABLE
2015-10-23 11:45:44.550 [EURUSD] Clearing result... cleared
2015-10-23 11:45:44.612 [EURUSD] SQL: CREATE TABLE "_test_data_table" (id SERIAL NOT NULL,symbol VARCHAR,timeframe INTEGER,open NUMERIC(10, 5),high NUMERIC(10, 5),low NUMERIC(10, 5),close NUMERIC(10,
5),PRIMARY KEY (id))
2015-10-23 11:45:44.753 [EURUSD] OK: nothing returned

CASE: INSERT RANDOM DATA
2015-10-23 11:45:44.816 [EURUSD] Clearing result... cleared
2015-10-23 11:45:44.862 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol", "timeframe", "open", "high", "low", "close") VALUES ('EURUSD', 15, 1.71554, 1.5085, 1.99399, 1.33964)
2015-10-23 11:45:44.926 [EURUSD] OK: 1 affected row(s)
affected_rows = 1
2015-10-23 11:45:45.019 [EURUSD] Clearing result... cleared
2015-10-23 11:45:45.066 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol", "timeframe", "open", "high", "low", "close") VALUES ('EURUSD', 30, 1.23484, 1.16288, 1.33064, 1.06192)
2015-10-23 11:45:45.206 [EURUSD] OK: 1 affected row(s)
affected_rows = 1
2015-10-23 11:45:45.253 [EURUSD] Clearing result... cleared
2015-10-23 11:45:45.253 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol", "timeframe", "open", "high", "low", "close") VALUES ('USDJPY', 1440, 1.06507, 1.2067, 1.95389, 1.91189)
2015-10-23 11:45:45.362 [EURUSD] OK: 1 affected row(s)
affected_rows = 1
2015-10-23 11:45:45.425 [EURUSD] Clearing result... cleared
2015-10-23 11:45:45.488 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol", "timeframe", "open", "high", "low", "close") VALUES ('EURUSD', 5, 1.98517, 1.65969, 1.53478, 1.8496)
2015-10-23 11:45:45.612 [EURUSD] OK: 1 affected row(s)
affected_rows = 1
2015-10-23 11:45:45.659 [EURUSD] Clearing result... cleared
2015-10-23 11:45:45.691 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol", "timeframe", "open", "high", "low", "close") VALUES ('GBPUSD', 240, 1.75082, 1.79681, 1.07694, 1.08521)
2015-10-23 11:45:45.784 [EURUSD] OK: 1 affected row(s)
affected_rows = 1
2015-10-23 11:45:45.816 [EURUSD] Clearing result... cleared
2015-10-23 11:45:45.894 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol", "timeframe", "open", "high", "low", "close") VALUES ('USDCHF', 60, 1.2284, 1.65972, 1.33824, 1.29637)
2015-10-23 11:45:46.050 [EURUSD] OK: 1 affected row(s)
affected_rows = 1
2015-10-23 11:45:46.129 [EURUSD] Clearing result... cleared
2015-10-23 11:45:46.159 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol", "timeframe", "open", "high", "low", "close") VALUES ('EURUSD', 5, 1.48598, 1.00955, 1.07453, 1.9154)
2015-10-23 11:45:46.394 [EURUSD] OK: 1 affected row(s)
affected_rows = 1
2015-10-23 11:45:46.566 [EURUSD] Clearing result... cleared
2015-10-23 11:45:46.612 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol", "timeframe", "open", "high", "low", "close") VALUES ('USDCHF', 5, 1.21503, 1.84634, 1.97989, 1.77822)
2015-10-23 11:45:46.800 [EURUSD] OK: 1 affected row(s)
affected_rows = 1
2015-10-23 11:45:46.847 [EURUSD] Clearing result... cleared
2015-10-23 11:45:46.925 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol", "timeframe", "open", "high", "low", "close") VALUES ('GBPUSD', 1440, 1.75607, 1.65438, 1.51982, 1.31922)
2015-10-23 11:45:47.129 [EURUSD] OK: 1 affected row(s)
affected_rows = 1
2015-10-23 11:45:47.253 [EURUSD] Clearing result... cleared
2015-10-23 11:45:47.316 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol", "timeframe", "open", "high", "low", "close") VALUES ('USDJPY', 15, 1.38554, 1.73782, 1.78738, 1.18574)
2015-10-23 11:45:47.581 [EURUSD] OK: 1 affected row(s)
affected_rows = 1

CASE: INSERT RANDOM DATA RETURNING ID
2015-10-23 11:45:47.691 [EURUSD] Clearing result... cleared
2015-10-23 11:45:47.786 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol", "timeframe", "open", "high", "low", "close") VALUES ('USDJPY', 1440, 1.01663, 1.51155, 1.67531, 1.75729) RETURNING "id"
2015-10-23 11:45:48.238 [EURUSD] OK: returned 1 rows (1 fields)
last_inserted_id = 11

CASE: UPDATE DATA
2015-10-23 11:45:48.348 [EURUSD] Clearing result... cleared
2015-10-23 11:45:48.566 [EURUSD] SQL: UPDATE "_test_data_table" SET "symbol" = 'SVKCZK' WHERE "id" = 1
2015-10-23 11:45:48.691 [EURUSD] OK: 1 affected row(s)
affected_rows = 1

CASE: DELETE DATA
2015-10-23 11:45:48.878 [EURUSD] Clearing result... cleared
2015-10-23 11:45:48.925 [EURUSD] SQL: DELETE FROM "_test_data_table" WHERE "id" = 1
2015-10-23 11:45:49.102 [EURUSD] OK: 1 affected row(s)
affected_rows = 1

CASE: UPDATE NON-EXISTENT DATA
2015-10-23 11:45:49.237 [EURUSD] Clearing result... cleared
2015-10-23 11:45:49.394 [EURUSD] SQL: UPDATE "_test_data_table" SET "symbol" = 'SVKCZK' WHERE "id" = 1
2015-10-23 11:45:49.581 [EURUSD] OK: 0 affected row(s)
affected_rows = 0

CASE: DELETE NON-EXISTENT DATA
2015-10-23 11:45:49.769 [EURUSD] Clearing result... cleared
2015-10-23 11:45:49.831 [EURUSD] SQL: DELETE FROM "_test_data_table" WHERE "id" = 1
2015-10-23 11:45:49.896 [EURUSD] OK: 0 affected row(s)
affected_rows = 0

CASE: CREATE IMPOSSIBLE UNIQUE INDEX
2015-10-23 11:45:49.977 [EURUSD] Clearing result... cleared
2015-10-23 11:45:50.003 [EURUSD] SQL: CREATE UNIQUE INDEX impossible_unique_index_idx ON "_test_data_table" ("symbol")
2015-10-23 11:45:50.066 [EURUSD] Clearing result... cleared
2015-10-23 11:45:50.097 [EURUSD] ERROR:  could not create unique index "impossible_unique_index_idx"
DETAIL:  Key (symbol)=(EURUSD) is duplicated.


affected_rows =

CASE: CREATE POSSIBLE UNIQUE INDEX
2015-10-23 11:45:50.206 [EURUSD] SQL: CREATE UNIQUE INDEX possible_unique_index_idx ON "_test_data_table" ("symbol", "timeframe", "open")
2015-10-23 11:45:50.253 [EURUSD] OK: nothing returned
affected_rows =

CASE: INSERT COLLISION
2015-10-23 11:45:50.300 [EURUSD] Clearing result... cleared
2015-10-23 11:45:50.316 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol", "timeframe", "open", "high", "low", "close") VALUES ('SVKCZK', 1993, 1.0, 1.0, 1.0, 1.0)
2015-10-23 11:45:50.378 [EURUSD] OK: 1 affected row(s)
2015-10-23 11:45:50.409 [EURUSD] Clearing result... cleared
2015-10-23 11:45:50.441 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol", "timeframe", "open", "high", "low", "close") VALUES ('SVKCZK', 1993, 1.0, 1.0, 1.0, 1.0)
2015-10-23 11:45:50.534 [EURUSD] Clearing result... cleared
2015-10-23 11:45:50.566 [EURUSD] ERROR:  duplicate key value violates unique constraint "possible_unique_index_idx"
DETAIL:  Key (symbol, timeframe, open)=(SVKCZK, 1993, 1.00000) already exists.



CASE: UPDATE COLLISION
2015-10-23 11:45:50.644 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol", "timeframe", "open", "high", "low", "close") VALUES ('SVKCZK', 1993, 2.0, 2.0, 2.0, 2.0)
2015-10-23 11:45:50.737 [EURUSD] OK: 1 affected row(s)
2015-10-23 11:45:50.769 [EURUSD] Clearing result... cleared
2015-10-23 11:45:50.784 [EURUSD] SQL: UPDATE "_test_data_table" SET "open" = 1.0 WHERE "open" = 2.0
2015-10-23 11:45:50.816 [EURUSD] Clearing result... cleared
2015-10-23 11:45:50.851 [EURUSD] ERROR:  duplicate key value violates unique constraint "possible_unique_index_idx"
DETAIL:  Key (symbol, timeframe, open)=(SVKCZK, 1993, 1.00000) already exists.



CASE: SELECT * FROM
2015-10-23 11:45:50.925 [EURUSD] SQL: SELECT * FROM "_test_data_table" LIMIT 5
2015-10-23 11:45:50.956 [EURUSD] OK: returned 5 rows (7 fields)
num_rows = 5, num_fields = 7
affected_rows =

CASE: GET FIELD LIST
2015-10-23 11:45:51.003 [EURUSD] Field list: "id" "symbol" "timeframe" "open" "high" "low" "close"
field_list = "id" "symbol" "timeframe" "open" "high" "low" "close"

CASE: FETCH FIELDS
fetching row 1 of 5
field[0][0] = 2
field[0][1] = EURUSD
field[0][2] = 30
field[0][3] = 1.23484
field[0][4] = 1.16288
field[0][5] = 1.33064
field[0][6] = 1.06192

fetching row 2 of 5
field[1][0] = 3
field[1][1] = USDJPY
field[1][2] = 1440
field[1][3] = 1.06507
field[1][4] = 1.20670
field[1][5] = 1.95389
field[1][6] = 1.91189

fetching row 3 of 5
field[2][0] = 4
field[2][1] = EURUSD
field[2][2] = 5
field[2][3] = 1.98517
field[2][4] = 1.65969
field[2][5] = 1.53478
field[2][6] = 1.84960

fetching row 4 of 5
field[3][0] = 5
field[3][1] = GBPUSD
field[3][2] = 240
field[3][3] = 1.75082
field[3][4] = 1.79681
field[3][5] = 1.07694
field[3][6] = 1.08521

fetching row 5 of 5
field[4][0] = 6
field[4][1] = USDCHF
field[4][2] = 60
field[4][3] = 1.22840
field[4][4] = 1.65972
field[4][5] = 1.33824
field[4][6] = 1.29637


CASE: FETCH NON-EXISTENT ROW/FIELD
2015-10-23 11:45:51.582 [EURUSD] ERROR: cannot fetch row: 100, field: 0 (#rows:5, #fields:7)
field[0] row[100] = N_A
2015-10-23 11:45:51.630 [EURUSD] ERROR: cannot fetch row: 0, field: 100 (#rows:5, #fields:7)
field[100] row[0] = N_A
2015-10-23 11:45:51.706 [EURUSD] Clearing result... cleared

CASE: FIELD LIST ON CLEARED RESULT
2015-10-23 11:45:51.737 [EURUSD] Field list:
2015-10-23 11:45:51.753 [EURUSD] ERROR: no active result found (probably cleared?)
field_list =

CASE: FETCH ROW(S) ON CLEARED RESULT

CASE: CLOSE CONNECTION
2015-10-23 11:45:51.800 [EURUSD] Closing connection [c:01037440, w:00FF16B8] ... closed

CASE: QUERY ON CLOSED CONNECTION (SHOULD TRY RECONNECT)
2015-10-23 11:45:51.847 [EURUSD] ERROR: connection closed, trying to reconnect...
2015-10-23 11:45:51.878 [EURUSD] Closing connection [c:00000000, w:00FF16B8] ... was already closed
2015-10-23 11:45:51.925 [EURUSD] Opening database connection (attempt:1) ... opened [c:01037440, w:00FF16B8]
2015-10-23 11:45:51.941 [EURUSD] SQL: SELECT * FROM "_test_data_table" LIMIT 5
2015-10-23 11:45:51.972 [EURUSD] OK: returned 5 rows (7 fields)

CASE: CLOSE ALREADY CLOSED CONNECTION
2015-10-23 11:45:51.987 [EURUSD] Closing connection [c:01037440, w:00FF16B8] ... closed
2015-10-23 11:45:52.003 [EURUSD] Closing connection [c:00000000, w:00FF16B8] ... was already closed

CASE: WRITE LOG ON DESTROYED LOGGER
2015-10-23 11:45:52.050 [2015-10-23 11:45:52.066 [
CASE: CALL QUERY ON DESTROYED WRAPPER

SUCCESS, HIT SOME KEY AND ENTER
```
