# Test stdout (should be pretty self-explanatory)

```
CASE: UNSUCCESSFUL CONNECTION
2015-10-18 22:34:02.244 [EURUSD] Opening database connection (attempt:1) ... failed [015292E0, w:01525750]
fe_sendauth: no password supplied

2015-10-18 22:34:03.404 [EURUSD] Opening database connection (attempt:2) ... failed [015392D0, w:01525750]
fe_sendauth: no password supplied

2015-10-18 22:34:05.475 [EURUSD] Closing connection [c:015392D0, w:01525750] ... closed
2015-10-18 22:34:05.519 [EURUSD] Closing connection [c:00000000, w:01525750] ... was already closed

CASE: WRITE LOG
2015-10-18 22:34:05.571 [EURUSD] Is this the most important message or what?

CASE: SUCCESSFUL CONNECTION
2015-10-18 22:34:05.684 [EURUSD] Opening database connection (attempt:1) ... opened [c:0155E6D8, w:01525750]
client version = 90404
server version = 90404

CASE: EMPTY QUERY
2015-10-18 22:34:05.752 [EURUSD] SQL:
2015-10-18 22:34:05.769 [EURUSD] Clearing result... cleared
2015-10-18 22:34:05.802 [EURUSD] ERROR: empty query
2015-10-18 22:34:05.818 [EURUSD] Clearing result... was already cleared

CASE: DROP TABLE IF EXISTS
2015-10-18 22:34:05.897 [EURUSD] SQL: DROP TABLE IF EXISTS "_test_data_table"
2015-10-18 22:34:05.934 [EURUSD] OK: nothing returned

CASE: CREATE TABLE
2015-10-18 22:34:06.071 [EURUSD] Clearing result... cleared
2015-10-18 22:34:06.256 [EURUSD] SQL: CREATE TABLE "_test_data_table" (id SERIAL NOT NULL,symbol VARCHAR,timeframe INTEG
ER,open NUMERIC(10, 5),high NUMERIC(10, 5),low NUMERIC(10, 5),close NUMERIC(10, 5),PRIMARY KEY (id))
2015-10-18 22:34:06.521 [EURUSD] OK: nothing returned

CASE: INSERT RANDOM DATA
2015-10-18 22:34:06.624 [EURUSD] Clearing result... cleared
2015-10-18 22:34:06.684 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol", "timeframe", "open", "high", "low", "clo
se") VALUES ('EURUSD', 15, 1.60448, 1.78115, 1.82315, 1.16446)
2015-10-18 22:34:06.853 [EURUSD] OK: 1 affected row(s)
affected_rows = 1
2015-10-18 22:34:06.925 [EURUSD] Clearing result... cleared
2015-10-18 22:34:06.986 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol", "timeframe", "open", "high", "low", "clo
se") VALUES ('USDCHF', 15, 1.90802, 1.53893, 1.08792, 1.85806)
2015-10-18 22:34:07.173 [EURUSD] OK: 1 affected row(s)
affected_rows = 1
2015-10-18 22:34:07.257 [EURUSD] Clearing result... cleared
2015-10-18 22:34:07.316 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol", "timeframe", "open", "high", "low", "clo
se") VALUES ('USDCHF', 15, 1.41081, 1.17316, 1.62563, 1.12735)
2015-10-18 22:34:07.463 [EURUSD] OK: 1 affected row(s)
affected_rows = 1
2015-10-18 22:34:07.533 [EURUSD] Clearing result... cleared
2015-10-18 22:34:07.585 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol", "timeframe", "open", "high", "low", "clo
se") VALUES ('USDJPY', 5, 1.47856, 1.70681, 1.20667, 1.81036)
2015-10-18 22:34:07.743 [EURUSD] OK: 1 affected row(s)
affected_rows = 1
2015-10-18 22:34:07.862 [EURUSD] Clearing result... cleared
2015-10-18 22:34:08.023 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol", "timeframe", "open", "high", "low", "clo
se") VALUES ('GBPUSD', 5, 1.86889, 1.95532, 1.52965, 1.98273)
2015-10-18 22:34:08.234 [EURUSD] OK: 1 affected row(s)
affected_rows = 1
2015-10-18 22:34:08.316 [EURUSD] Clearing result... cleared
2015-10-18 22:34:08.404 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol", "timeframe", "open", "high", "low", "clo
se") VALUES ('USDJPY', 5, 1.60097, 1.42851, 1.52336, 1.76711)
2015-10-18 22:34:08.540 [EURUSD] OK: 1 affected row(s)
affected_rows = 1
2015-10-18 22:34:08.597 [EURUSD] Clearing result... cleared
2015-10-18 22:34:08.638 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol", "timeframe", "open", "high", "low", "clo
se") VALUES ('EURUSD', 240, 1.61193, 1.31346, 1.84094, 1.33934)
2015-10-18 22:34:08.762 [EURUSD] OK: 1 affected row(s)
affected_rows = 1
2015-10-18 22:34:08.816 [EURUSD] Clearing result... cleared
2015-10-18 22:34:08.855 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol", "timeframe", "open", "high", "low", "clo
se") VALUES ('EURUSD', 1440, 1.48048, 1.3621, 1.18757, 1.16651)
2015-10-18 22:34:08.950 [EURUSD] OK: 1 affected row(s)
affected_rows = 1
2015-10-18 22:34:09.009 [EURUSD] Clearing result... cleared
2015-10-18 22:34:09.061 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol", "timeframe", "open", "high", "low", "clo
se") VALUES ('GBPUSD', 15, 1.57158, 1.14911, 1.24381, 1.14087)
2015-10-18 22:34:09.158 [EURUSD] OK: 1 affected row(s)
affected_rows = 1
2015-10-18 22:34:09.178 [EURUSD] Clearing result... cleared
2015-10-18 22:34:09.216 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol", "timeframe", "open", "high", "low", "clo
se") VALUES ('GBPUSD', 5, 1.63674, 1.60497, 1.79891, 1.32032)
2015-10-18 22:34:09.328 [EURUSD] OK: 1 affected row(s)
affected_rows = 1

CASE: INSERT RANDOM DATA RETURNING ID
2015-10-18 22:34:09.387 [EURUSD] Clearing result... cleared
2015-10-18 22:34:09.454 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol", "timeframe", "open", "high", "low", "clo
se") VALUES ('USDJPY', 1440, 1.82095, 1.09012, 1.92276, 1.58348) RETURNING "id"
2015-10-18 22:34:09.602 [EURUSD] OK: returned 1 rows (1 fields)
2015-10-18 22:34:09.635 [EURUSD] Fetching row: 0
last_inserted_id = 11

CASE: UPDATE DATA
2015-10-18 22:34:09.701 [EURUSD] Clearing result... cleared
2015-10-18 22:34:09.742 [EURUSD] SQL: UPDATE "_test_data_table" SET "symbol" = 'SVKCZK' WHERE "id" = 11
2015-10-18 22:34:09.803 [EURUSD] OK: 1 affected row(s)
affected_rows = 1

CASE: DELETE DATA
2015-10-18 22:34:09.864 [EURUSD] Clearing result... cleared
2015-10-18 22:34:09.909 [EURUSD] SQL: DELETE FROM "_test_data_table" WHERE "id" = 11
2015-10-18 22:34:09.964 [EURUSD] OK: 1 affected row(s)
affected_rows = 1

CASE: UPDATE NON-EXISTENT DATA
2015-10-18 22:34:10.023 [EURUSD] Clearing result... cleared
2015-10-18 22:34:10.067 [EURUSD] SQL: UPDATE "_test_data_table" SET "symbol" = 'SVKCZK' WHERE "id" = 11
2015-10-18 22:34:10.155 [EURUSD] OK: 0 affected row(s)
affected_rows = 0

CASE: DELETE NON-EXISTENT DATA
2015-10-18 22:34:10.229 [EURUSD] Clearing result... cleared
2015-10-18 22:34:10.279 [EURUSD] SQL: DELETE FROM "_test_data_table" WHERE "id" = 11
2015-10-18 22:34:10.322 [EURUSD] OK: 0 affected row(s)
affected_rows = 0

CASE: CREATE IMPOSSIBLE UNIQUE INDEX
2015-10-18 22:34:10.398 [EURUSD] Clearing result... cleared
2015-10-18 22:34:10.437 [EURUSD] SQL: CREATE UNIQUE INDEX impossible_unique_index_idx ON "_test_data_table" ("symbol")
2015-10-18 22:34:10.488 [EURUSD] Clearing result... cleared
2015-10-18 22:34:10.515 [EURUSD] ERROR:  could not create unique index "impossible_unique_index_idx"
DETAIL:  Key (symbol)=(USDCHF) is duplicated.


affected_rows =

CASE: CREATE POSSIBLE UNIQUE INDEX
2015-10-18 22:34:10.707 [EURUSD] SQL: CREATE UNIQUE INDEX possible_unique_index_idx ON "_test_data_table" ("symbol", "ti
meframe", "open")
2015-10-18 22:34:10.776 [EURUSD] OK: nothing returned
affected_rows =

CASE: INSERT COLLISION
2015-10-18 22:34:10.865 [EURUSD] Clearing result... cleared
2015-10-18 22:34:10.905 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol", "timeframe", "open", "high", "low", "clo
se") VALUES ('SVKCZK', 1993, 1.0, 1.0, 1.0, 1.0)
2015-10-18 22:34:10.998 [EURUSD] OK: 1 affected row(s)
2015-10-18 22:34:11.030 [EURUSD] Clearing result... cleared
2015-10-18 22:34:11.062 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol", "timeframe", "open", "high", "low", "clo
se") VALUES ('SVKCZK', 1993, 1.0, 1.0, 1.0, 1.0)
2015-10-18 22:34:11.171 [EURUSD] Clearing result... cleared
2015-10-18 22:34:11.207 [EURUSD] ERROR:  duplicate key value violates unique constraint "possible_unique_index_idx"
DETAIL:  Key (symbol, timeframe, open)=(SVKCZK, 1993, 1.00000) already exists.



CASE: UPDATE COLLISION
2015-10-18 22:34:11.335 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol", "timeframe", "open", "high", "low", "clo
se") VALUES ('SVKCZK', 1993, 2.0, 2.0, 2.0, 2.0)
2015-10-18 22:34:11.419 [EURUSD] OK: 1 affected row(s)
2015-10-18 22:34:11.454 [EURUSD] Clearing result... cleared
2015-10-18 22:34:11.494 [EURUSD] SQL: UPDATE "_test_data_table" SET "open" = 1.0 WHERE "open" = 2.0
2015-10-18 22:34:11.537 [EURUSD] Clearing result... cleared
2015-10-18 22:34:11.573 [EURUSD] ERROR:  duplicate key value violates unique constraint "possible_unique_index_idx"
DETAIL:  Key (symbol, timeframe, open)=(SVKCZK, 1993, 1.00000) already exists.



CASE: SELECT * FROM
2015-10-18 22:34:11.838 [EURUSD] SQL: SELECT * FROM "_test_data_table" LIMIT 5
2015-10-18 22:34:11.891 [EURUSD] OK: returned 5 rows (7 fields)
num_rows = 5, num_fields = 7
affected_rows =

CASE: GET FIELD LIST
2015-10-18 22:34:11.969 [EURUSD] Field list: "id" "symbol" "timeframe" "open" "high" "low" "close"
field_list = "id" "symbol" "timeframe" "open" "high" "low" "close"

CASE: FETCH ROW(S)
fetching row 1 of 5
2015-10-18 22:34:12.109 [EURUSD] Fetching row: 0
field[0][0] = 1
field[0][1] = EURUSD
field[0][2] = 15
field[0][3] = 1.60448
field[0][4] = 1.78115
field[0][5] = 1.82315
field[0][6] = 1.16446

fetching row 2 of 5
2015-10-18 22:34:12.319 [EURUSD] Fetching row: 1
field[1][0] = 2
field[1][1] = USDCHF
field[1][2] = 15
field[1][3] = 1.90802
field[1][4] = 1.53893
field[1][5] = 1.08792
field[1][6] = 1.85806

fetching row 3 of 5
2015-10-18 22:34:12.474 [EURUSD] Fetching row: 2
field[2][0] = 3
field[2][1] = USDCHF
field[2][2] = 15
field[2][3] = 1.41081
field[2][4] = 1.17316
field[2][5] = 1.62563
field[2][6] = 1.12735

fetching row 4 of 5
2015-10-18 22:34:12.640 [EURUSD] Fetching row: 3
field[3][0] = 4
field[3][1] = USDJPY
field[3][2] = 5
field[3][3] = 1.47856
field[3][4] = 1.70681
field[3][5] = 1.20667
field[3][6] = 1.81036

fetching row 5 of 5
2015-10-18 22:34:12.824 [EURUSD] Fetching row: 4
field[4][0] = 5
field[4][1] = GBPUSD
field[4][2] = 5
field[4][3] = 1.86889
field[4][4] = 1.95532
field[4][5] = 1.52965
field[4][6] = 1.98273

2015-10-18 22:34:13.018 [EURUSD] Clearing result... cleared

CASE: FIELD LIST ON CLEARED RESULT
2015-10-18 22:34:13.091 [EURUSD] Field list: N_A
2015-10-18 22:34:13.116 [EURUSD] ERROR: no active result found (probably cleared?)
field_list = N_A

CASE: FETCH ROW(S) ON CLEARED RESULT
fetching row 1 of 5
2015-10-18 22:34:13.232 [EURUSD] Fetching row: 0
2015-10-18 22:34:13.280 [EURUSD] ERROR: no active result found (probably cleared?)
field[0][0] = 5
field[0][1] = GBPUSD
field[0][2] = 5
field[0][3] = 1.86889
field[0][4] = 1.95532
field[0][5] = 1.52965
field[0][6] = 1.98273

fetching row 2 of 5
2015-10-18 22:34:13.465 [EURUSD] Fetching row: 1
2015-10-18 22:34:13.497 [EURUSD] ERROR: no active result found (probably cleared?)
field[1][0] = 5
field[1][1] = GBPUSD
field[1][2] = 5
field[1][3] = 1.86889
field[1][4] = 1.95532
field[1][5] = 1.52965
field[1][6] = 1.98273

fetching row 3 of 5
2015-10-18 22:34:13.733 [EURUSD] Fetching row: 2
2015-10-18 22:34:13.767 [EURUSD] ERROR: no active result found (probably cleared?)
field[2][0] = 5
field[2][1] = GBPUSD
field[2][2] = 5
field[2][3] = 1.86889
field[2][4] = 1.95532
field[2][5] = 1.52965
field[2][6] = 1.98273

fetching row 4 of 5
2015-10-18 22:34:13.973 [EURUSD] Fetching row: 3
2015-10-18 22:34:14.011 [EURUSD] ERROR: no active result found (probably cleared?)
field[3][0] = 5
field[3][1] = GBPUSD
field[3][2] = 5
field[3][3] = 1.86889
field[3][4] = 1.95532
field[3][5] = 1.52965
field[3][6] = 1.98273

fetching row 5 of 5
2015-10-18 22:34:14.218 [EURUSD] Fetching row: 4
2015-10-18 22:34:14.259 [EURUSD] ERROR: no active result found (probably cleared?)
field[4][0] = 5
field[4][1] = GBPUSD
field[4][2] = 5
field[4][3] = 1.86889
field[4][4] = 1.95532
field[4][5] = 1.52965
field[4][6] = 1.98273


CASE: FETCH NON-EXISTENT ROW
2015-10-18 22:34:14.507 [EURUSD] Fetching row: 100
2015-10-18 22:34:14.544 [EURUSD] ERROR: no active result found (probably cleared?)
field[0] = 5
field[1] = GBPUSD
field[2] = 5
field[3] = 1.86889
field[4] = 1.95532
field[5] = 1.52965
field[6] = 1.98273

CASE: CLOSE CONNECTION
2015-10-18 22:34:14.742 [EURUSD] Closing connection [c:0155E6D8, w:01525750] ... closed

CASE: QUERY ON CLOSED CONNECTION (SHOULD TRY RECONNECT)
2015-10-18 22:34:14.865 [EURUSD] ERROR: connection closed, trying to reconnect...
2015-10-18 22:34:14.932 [EURUSD] Closing connection [c:00000000, w:01525750] ... was already closed
2015-10-18 22:34:15.085 [EURUSD] Opening database connection (attempt:1) ... opened [c:0155E6D8, w:01525750]
2015-10-18 22:34:15.142 [EURUSD] SQL: SELECT * FROM "_test_data_table" LIMIT 5
2015-10-18 22:34:15.197 [EURUSD] OK: returned 5 rows (7 fields)

CASE: CLOSE ALREADY CLOSED CONNECTION
2015-10-18 22:34:15.277 [EURUSD] Closing connection [c:0155E6D8, w:01525750] ... closed
2015-10-18 22:34:15.330 [EURUSD] Closing connection [c:00000000, w:01525750] ... was already closed

CASE: CALL QUERY ON DESTROYED WRAPPER

SUCCESS, HIT SOME KEY AND ENTER
```