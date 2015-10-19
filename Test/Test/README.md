# Test stdout (should be pretty self-explanatory)

```
CASE: UNSUCCESSFUL CONNECTION
2015-10-19 13:48:28.657 [EURUSD] Opening database connection (attempt:1) ... failed [011B9270, w:011B56F8]
fe_sendauth: no password supplied

2015-10-19 13:48:29.798 [EURUSD] Opening database connection (attempt:2) ... failed [011C92B0, w:011B56F8]
fe_sendauth: no password supplied

2015-10-19 13:48:31.813 [EURUSD] Closing connection [c:011C92B0, w:011B56F8] ... closed
2015-10-19 13:48:31.845 [EURUSD] Closing connection [c:00000000, w:011B56F8] ... was already closed

CASE: WRITE LOG
2015-10-19 13:48:31.907 [EURUSD] Is this the most important message or what?

CASE: SUCCESSFUL CONNECTION
2015-10-19 13:48:32.017 [EURUSD] Opening database connection (attempt:1) ... opened [c:011EE6B8, w:011B56F8]
client version = 90404
server version = 90404

CASE: EMPTY QUERY
2015-10-19 13:48:32.143 [EURUSD] SQL:
2015-10-19 13:48:32.157 [EURUSD] Clearing result... cleared
2015-10-19 13:48:32.220 [EURUSD] ERROR: empty query
2015-10-19 13:48:32.267 [EURUSD] Clearing result... was already cleared

CASE: DROP TABLE IF EXISTS
2015-10-19 13:48:32.392 [EURUSD] SQL: DROP TABLE IF EXISTS "_test_data_table"
2015-10-19 13:48:32.470 [EURUSD] OK: nothing returned

CASE: CREATE TABLE
2015-10-19 13:48:32.532 [EURUSD] Clearing result... cleared
2015-10-19 13:48:32.626 [EURUSD] SQL: CREATE TABLE "_test_data_table" (id SERIAL NOT NULL,symbol VARCHAR,timeframe INTEGER,open NUMERIC(10, 5),high NUMERIC(10, 5),low NUMERIC(10, 5),close NUMERIC(10,
5),PRIMARY KEY (id))
2015-10-19 13:48:32.813 [EURUSD] OK: nothing returned

CASE: INSERT RANDOM DATA
2015-10-19 13:48:32.860 [EURUSD] Clearing result... cleared
2015-10-19 13:48:32.939 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol", "timeframe", "open", "high", "low", "close") VALUES ('USDJPY', 5, 1.67415, 1.14686, 1.71233, 1.63228)
2015-10-19 13:48:33.017 [EURUSD] OK: 1 affected row(s)
affected_rows = 1
2015-10-19 13:48:33.064 [EURUSD] Clearing result... cleared
2015-10-19 13:48:33.095 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol", "timeframe", "open", "high", "low", "close") VALUES ('USDCHF', 15, 1.7221, 1.17319, 1.72494, 1.2758)
2015-10-19 13:48:33.204 [EURUSD] OK: 1 affected row(s)
affected_rows = 1
2015-10-19 13:48:33.251 [EURUSD] Clearing result... cleared
2015-10-19 13:48:33.282 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol", "timeframe", "open", "high", "low", "close") VALUES ('USDCHF', 1440, 1.919, 1.22932, 1.42073, 1.96139)
2015-10-19 13:48:33.392 [EURUSD] OK: 1 affected row(s)
affected_rows = 1
2015-10-19 13:48:33.423 [EURUSD] Clearing result... cleared
2015-10-19 13:48:33.454 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol", "timeframe", "open", "high", "low", "close") VALUES ('GBPUSD', 60, 1.41173, 1.571, 1.38377, 1.12546)
2015-10-19 13:48:33.563 [EURUSD] OK: 1 affected row(s)
affected_rows = 1
2015-10-19 13:48:33.611 [EURUSD] Clearing result... cleared
2015-10-19 13:48:33.657 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol", "timeframe", "open", "high", "low", "close") VALUES ('EURUSD', 240, 1.38307, 1.50728, 1.10291, 1.87307)
2015-10-19 13:48:33.751 [EURUSD] OK: 1 affected row(s)
affected_rows = 1
2015-10-19 13:48:33.798 [EURUSD] Clearing result... cleared
2015-10-19 13:48:33.829 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol", "timeframe", "open", "high", "low", "close") VALUES ('GBPUSD', 1440, 1.08792, 1.23618, 1.41096, 1.48115)
2015-10-19 13:48:33.954 [EURUSD] OK: 1 affected row(s)
affected_rows = 1
2015-10-19 13:48:33.970 [EURUSD] Clearing result... cleared
2015-10-19 13:48:34.001 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol", "timeframe", "open", "high", "low", "close") VALUES ('USDJPY', 5, 1.27027, 1.31364, 1.34761, 1.43782)
2015-10-19 13:48:34.110 [EURUSD] OK: 1 affected row(s)
affected_rows = 1
2015-10-19 13:48:34.157 [EURUSD] Clearing result... cleared
2015-10-19 13:48:34.204 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol", "timeframe", "open", "high", "low", "close") VALUES ('EURUSD', 60, 1.16904, 1.93677, 1.97027, 1.42604)
2015-10-19 13:48:34.298 [EURUSD] OK: 1 affected row(s)
affected_rows = 1
2015-10-19 13:48:34.345 [EURUSD] Clearing result... cleared
2015-10-19 13:48:34.392 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol", "timeframe", "open", "high", "low", "close") VALUES ('EURUSD', 15, 1.78545, 1.06693, 1.01971, 1.8659)
2015-10-19 13:48:34.501 [EURUSD] OK: 1 affected row(s)
affected_rows = 1
2015-10-19 13:48:34.548 [EURUSD] Clearing result... cleared
2015-10-19 13:48:34.595 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol", "timeframe", "open", "high", "low", "close") VALUES ('USDCHF', 30, 1.52944, 1.93707, 1.84387, 1.13157)
2015-10-19 13:48:34.704 [EURUSD] OK: 1 affected row(s)
affected_rows = 1

CASE: INSERT RANDOM DATA RETURNING ID
2015-10-19 13:48:34.767 [EURUSD] Clearing result... cleared
2015-10-19 13:48:34.798 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol", "timeframe", "open", "high", "low", "close") VALUES ('USDCHF', 30, 1.42204, 1.80044, 1.20893, 1.48271) RETURNING "id"
2015-10-19 13:48:34.923 [EURUSD] OK: returned 1 rows (1 fields)
2015-10-19 13:48:34.954 [EURUSD] Fetching row: 0
last_inserted_id = 11

CASE: UPDATE DATA
2015-10-19 13:48:34.970 [EURUSD] Clearing result... cleared
2015-10-19 13:48:35.001 [EURUSD] SQL: UPDATE "_test_data_table" SET "symbol" = 'SVKCZK' WHERE "id" = 11
2015-10-19 13:48:35.064 [EURUSD] OK: 1 affected row(s)
affected_rows = 1

CASE: DELETE DATA
2015-10-19 13:48:35.110 [EURUSD] Clearing result... cleared
2015-10-19 13:48:35.142 [EURUSD] SQL: DELETE FROM "_test_data_table" WHERE "id" = 11
2015-10-19 13:48:35.204 [EURUSD] OK: 1 affected row(s)
affected_rows = 1

CASE: UPDATE NON-EXISTENT DATA
2015-10-19 13:48:35.267 [EURUSD] Clearing result... cleared
2015-10-19 13:48:35.314 [EURUSD] SQL: UPDATE "_test_data_table" SET "symbol" = 'SVKCZK' WHERE "id" = 11
2015-10-19 13:48:35.360 [EURUSD] OK: 0 affected row(s)
affected_rows = 0

CASE: DELETE NON-EXISTENT DATA
2015-10-19 13:48:35.423 [EURUSD] Clearing result... cleared
2015-10-19 13:48:35.470 [EURUSD] SQL: DELETE FROM "_test_data_table" WHERE "id" = 11
2015-10-19 13:48:35.517 [EURUSD] OK: 0 affected row(s)
affected_rows = 0

CASE: CREATE IMPOSSIBLE UNIQUE INDEX
2015-10-19 13:48:35.579 [EURUSD] Clearing result... cleared
2015-10-19 13:48:35.626 [EURUSD] SQL: CREATE UNIQUE INDEX impossible_unique_index_idx ON "_test_data_table" ("symbol")
2015-10-19 13:48:35.704 [EURUSD] Clearing result... cleared
2015-10-19 13:48:35.737 [EURUSD] ERROR:  could not create unique index "impossible_unique_index_idx"
DETAIL:  Key (symbol)=(USDCHF) is duplicated.


affected_rows =

CASE: CREATE POSSIBLE UNIQUE INDEX
2015-10-19 13:48:35.892 [EURUSD] SQL: CREATE UNIQUE INDEX possible_unique_index_idx ON "_test_data_table" ("symbol", "timeframe", "open")
2015-10-19 13:48:35.970 [EURUSD] OK: nothing returned
affected_rows =

CASE: INSERT COLLISION
2015-10-19 13:48:36.017 [EURUSD] Clearing result... cleared
2015-10-19 13:48:36.048 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol", "timeframe", "open", "high", "low", "close") VALUES ('SVKCZK', 1993, 1.0, 1.0, 1.0, 1.0)
2015-10-19 13:48:36.142 [EURUSD] OK: 1 affected row(s)
2015-10-19 13:48:36.173 [EURUSD] Clearing result... cleared
2015-10-19 13:48:36.204 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol", "timeframe", "open", "high", "low", "close") VALUES ('SVKCZK', 1993, 1.0, 1.0, 1.0, 1.0)
2015-10-19 13:48:36.314 [EURUSD] Clearing result... cleared
2015-10-19 13:48:36.345 [EURUSD] ERROR:  duplicate key value violates unique constraint "possible_unique_index_idx"
DETAIL:  Key (symbol, timeframe, open)=(SVKCZK, 1993, 1.00000) already exists.



CASE: UPDATE COLLISION
2015-10-19 13:48:36.501 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol", "timeframe", "open", "high", "low", "close") VALUES ('SVKCZK', 1993, 2.0, 2.0, 2.0, 2.0)
2015-10-19 13:48:36.610 [EURUSD] OK: 1 affected row(s)
2015-10-19 13:48:36.642 [EURUSD] Clearing result... cleared
2015-10-19 13:48:36.673 [EURUSD] SQL: UPDATE "_test_data_table" SET "open" = 1.0 WHERE "open" = 2.0
2015-10-19 13:48:36.720 [EURUSD] Clearing result... cleared
2015-10-19 13:48:36.751 [EURUSD] ERROR:  duplicate key value violates unique constraint "possible_unique_index_idx"
DETAIL:  Key (symbol, timeframe, open)=(SVKCZK, 1993, 1.00000) already exists.



CASE: SELECT * FROM
2015-10-19 13:48:36.892 [EURUSD] SQL: SELECT * FROM "_test_data_table" LIMIT 5
2015-10-19 13:48:36.938 [EURUSD] OK: returned 5 rows (7 fields)
num_rows = 5, num_fields = 7
affected_rows =

CASE: GET FIELD LIST
2015-10-19 13:48:37.001 [EURUSD] Field list: "id" "symbol" "timeframe" "open" "high" "low" "close"
field_list = "id" "symbol" "timeframe" "open" "high" "low" "close"

CASE: FETCH ROW(S)
fetching row 1 of 5
2015-10-19 13:48:37.095 [EURUSD] Fetching row: 0
field[0][0] = 1
field[0][1] = USDJPY
field[0][2] = 5
field[0][3] = 1.67415
field[0][4] = 1.14686
field[0][5] = 1.71233
field[0][6] = 1.63228

fetching row 2 of 5
2015-10-19 13:48:37.235 [EURUSD] Fetching row: 1
field[1][0] = 2
field[1][1] = USDCHF
field[1][2] = 15
field[1][3] = 1.72210
field[1][4] = 1.17319
field[1][5] = 1.72494
field[1][6] = 1.27580

fetching row 3 of 5
2015-10-19 13:48:37.376 [EURUSD] Fetching row: 2
field[2][0] = 3
field[2][1] = USDCHF
field[2][2] = 1440
field[2][3] = 1.91900
field[2][4] = 1.22932
field[2][5] = 1.42073
field[2][6] = 1.96139

fetching row 4 of 5
2015-10-19 13:48:37.501 [EURUSD] Fetching row: 3
field[3][0] = 4
field[3][1] = GBPUSD
field[3][2] = 60
field[3][3] = 1.41173
field[3][4] = 1.57100
field[3][5] = 1.38377
field[3][6] = 1.12546

fetching row 5 of 5
2015-10-19 13:48:37.642 [EURUSD] Fetching row: 4
field[4][0] = 5
field[4][1] = EURUSD
field[4][2] = 240
field[4][3] = 1.38307
field[4][4] = 1.50728
field[4][5] = 1.10291
field[4][6] = 1.87307

2015-10-19 13:48:37.751 [EURUSD] Clearing result... cleared

CASE: FIELD LIST ON CLEARED RESULT
2015-10-19 13:48:37.814 [EURUSD] Field list: ERROR: no active result found (probably cleared?)
field_list =

CASE: FETCH ROW(S) ON CLEARED RESULT

CASE: FETCH NON-EXISTENT ROW
2015-10-19 13:48:37.938 [EURUSD] Fetching row: 100
2015-10-19 13:48:37.954 [EURUSD] ERROR: no active result found (probably cleared?)

CASE: CLOSE CONNECTION
2015-10-19 13:48:38.017 [EURUSD] Closing connection [c:011EE6B8, w:011B56F8] ... closed

CASE: QUERY ON CLOSED CONNECTION (SHOULD TRY RECONNECT)
2015-10-19 13:48:38.095 [EURUSD] ERROR: connection closed, trying to reconnect...
2015-10-19 13:48:38.142 [EURUSD] Closing connection [c:00000000, w:011B56F8] ... was already closed
2015-10-19 13:48:38.251 [EURUSD] Opening database connection (attempt:1) ... opened [c:011EE6B8, w:011B56F8]
2015-10-19 13:48:38.313 [EURUSD] SQL: SELECT * FROM "_test_data_table" LIMIT 5
2015-10-19 13:48:38.360 [EURUSD] OK: returned 5 rows (7 fields)

CASE: CLOSE ALREADY CLOSED CONNECTION
2015-10-19 13:48:38.407 [EURUSD] Closing connection [c:011EE6B8, w:011B56F8] ... closed
2015-10-19 13:48:38.454 [EURUSD] Closing connection [c:00000000, w:011B56F8] ... was already closed

CASE: CALL QUERY ON DESTROYED WRAPPER

SUCCESS, HIT SOME KEY AND ENTER
```