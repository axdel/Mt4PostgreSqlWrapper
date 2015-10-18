# Test stdout (should be pretty self-explanatory)

```
2015-10-18 22:28:04.138 [EURUSD] OK: 1 affected row(s)
affected_rows = 1
2015-10-18 22:28:04.175 [EURUSD] Clearing result... cleared
2015-10-18 22:28:04.196 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol",
"timeframe", "open", "high", "low", "close") VALUES ('GBPUSD', 30, 1.9826, 1.247
17, 1.6032, 1.52986)
2015-10-18 22:28:04.296 [EURUSD] OK: 1 affected row(s)
affected_rows = 1
2015-10-18 22:28:04.330 [EURUSD] Clearing result... cleared
2015-10-18 22:28:04.356 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol",
"timeframe", "open", "high", "low", "close") VALUES ('USDCHF', 30, 1.35322, 1.90
179, 1.02179, 1.21268)
2015-10-18 22:28:04.439 [EURUSD] OK: 1 affected row(s)
affected_rows = 1
2015-10-18 22:28:04.458 [EURUSD] Clearing result... cleared
2015-10-18 22:28:04.488 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol",
"timeframe", "open", "high", "low", "close") VALUES ('GBPUSD', 240, 1.68783, 1.1
0218, 1.37303, 1.523)
2015-10-18 22:28:04.581 [EURUSD] OK: 1 affected row(s)
affected_rows = 1
2015-10-18 22:28:04.610 [EURUSD] Clearing result... cleared
2015-10-18 22:28:04.636 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol",
"timeframe", "open", "high", "low", "close") VALUES ('EURUSD', 5, 1.61156, 1.587
66, 1.28211, 1.566)
2015-10-18 22:28:04.724 [EURUSD] OK: 1 affected row(s)
affected_rows = 1
2015-10-18 22:28:04.770 [EURUSD] Clearing result... cleared
2015-10-18 22:28:04.815 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol",
"timeframe", "open", "high", "low", "close") VALUES ('USDCHF', 60, 1.84182, 1.60
649, 1.30247, 1.82714)
2015-10-18 22:28:04.890 [EURUSD] OK: 1 affected row(s)
affected_rows = 1
2015-10-18 22:28:04.936 [EURUSD] Clearing result... cleared
2015-10-18 22:28:04.961 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol",
"timeframe", "open", "high", "low", "close") VALUES ('USDJPY', 240, 1.06784, 1.6
5285, 1.21552, 1.11249)
2015-10-18 22:28:05.035 [EURUSD] OK: 1 affected row(s)
affected_rows = 1
2015-10-18 22:28:05.070 [EURUSD] Clearing result... cleared
2015-10-18 22:28:05.097 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol",
"timeframe", "open", "high", "low", "close") VALUES ('EURUSD', 60, 1.21458, 1.54
427, 1.39433, 1.52)
2015-10-18 22:28:05.178 [EURUSD] OK: 1 affected row(s)
affected_rows = 1

CASE: INSERT RANDOM DATA RETURNING ID
2015-10-18 22:28:05.221 [EURUSD] Clearing result... cleared
2015-10-18 22:28:05.238 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol",
"timeframe", "open", "high", "low", "close") VALUES ('EURUSD', 5, 1.62621, 1.577
75, 1.90127, 1.1348) RETURNING "id"
2015-10-18 22:28:05.329 [EURUSD] OK: returned 1 rows (1 fields)
2015-10-18 22:28:05.356 [EURUSD] Fetching row: 0
last_inserted_id = 11

CASE: UPDATE DATA
2015-10-18 22:28:05.378 [EURUSD] Clearing result... cleared
2015-10-18 22:28:05.405 [EURUSD] SQL: UPDATE "_test_data_table" SET "symbol" = '
SVKCZK' WHERE "id" = 11
2015-10-18 22:28:05.475 [EURUSD] OK: 1 affected row(s)
affected_rows = 1

CASE: DELETE DATA
2015-10-18 22:28:05.509 [EURUSD] Clearing result... cleared
2015-10-18 22:28:05.529 [EURUSD] SQL: DELETE FROM "_test_data_table" WHERE "id"
= 11
2015-10-18 22:28:05.544 [EURUSD] OK: 1 affected row(s)
affected_rows = 1

CASE: UPDATE NON-EXISTENT DATA
2015-10-18 22:28:05.593 [EURUSD] Clearing result... cleared
2015-10-18 22:28:05.628 [EURUSD] SQL: UPDATE "_test_data_table" SET "symbol" = '
SVKCZK' WHERE "id" = 11
2015-10-18 22:28:05.672 [EURUSD] OK: 0 affected row(s)
affected_rows = 0

CASE: DELETE NON-EXISTENT DATA
2015-10-18 22:28:05.706 [EURUSD] Clearing result... cleared
2015-10-18 22:28:05.728 [EURUSD] SQL: DELETE FROM "_test_data_table" WHERE "id"
= 11
2015-10-18 22:28:05.779 [EURUSD] OK: 0 affected row(s)
affected_rows = 0

CASE: CREATE IMPOSSIBLE UNIQUE INDEX
2015-10-18 22:28:05.822 [EURUSD] Clearing result... cleared
2015-10-18 22:28:05.858 [EURUSD] SQL: CREATE UNIQUE INDEX impossible_unique_inde
x_idx ON "_test_data_table" ("symbol")
2015-10-18 22:28:05.909 [EURUSD] Clearing result... cleared
2015-10-18 22:28:05.945 [EURUSD] ERROR:  could not create unique index "impossib
le_unique_index_idx"
DETAIL:  Key (symbol)=(GBPUSD) is duplicated.


affected_rows =

CASE: CREATE POSSIBLE UNIQUE INDEX
2015-10-18 22:28:06.049 [EURUSD] SQL: CREATE UNIQUE INDEX possible_unique_index_
idx ON "_test_data_table" ("symbol", "timeframe", "open")
2015-10-18 22:28:06.128 [EURUSD] OK: nothing returned
affected_rows =

CASE: INSERT COLLISION
2015-10-18 22:28:06.172 [EURUSD] Clearing result... cleared
2015-10-18 22:28:06.204 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol",
"timeframe", "open", "high", "low", "close") VALUES ('SVKCZK', 1993, 1.0, 1.0, 1
.0, 1.0)
2015-10-18 22:28:06.290 [EURUSD] OK: 1 affected row(s)
2015-10-18 22:28:06.310 [EURUSD] Clearing result... cleared
2015-10-18 22:28:06.338 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol",
"timeframe", "open", "high", "low", "close") VALUES ('SVKCZK', 1993, 1.0, 1.0, 1
.0, 1.0)
2015-10-18 22:28:06.407 [EURUSD] Clearing result... cleared
2015-10-18 22:28:06.441 [EURUSD] ERROR:  duplicate key value violates unique con
straint "possible_unique_index_idx"
DETAIL:  Key (symbol, timeframe, open)=(SVKCZK, 1993, 1.00000) already exists.



CASE: UPDATE COLLISION
2015-10-18 22:28:06.590 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol",
"timeframe", "open", "high", "low", "close") VALUES ('SVKCZK', 1993, 2.0, 2.0, 2
.0, 2.0)
2015-10-18 22:28:06.661 [EURUSD] OK: 1 affected row(s)
2015-10-18 22:28:06.697 [EURUSD] Clearing result... cleared
2015-10-18 22:28:06.738 [EURUSD] SQL: UPDATE "_test_data_table" SET "open" = 1.0
 WHERE "open" = 2.0
2015-10-18 22:28:06.780 [EURUSD] Clearing result... cleared
2015-10-18 22:28:06.819 [EURUSD] ERROR:  duplicate key value violates unique con
straint "possible_unique_index_idx"
DETAIL:  Key (symbol, timeframe, open)=(SVKCZK, 1993, 1.00000) already exists.



CASE: SELECT * FROM
2015-10-18 22:28:06.963 [EURUSD] SQL: SELECT * FROM "_test_data_table" LIMIT 5
2015-10-18 22:28:06.994 [EURUSD] OK: returned 5 rows (7 fields)
num_rows = 5, num_fields = 7
affected_rows =

CASE: GET FIELD LIST
2015-10-18 22:28:07.062 [EURUSD] Field list: "id" "symbol" "timeframe" "open" "h
igh" "low" "close"
field_list = "id" "symbol" "timeframe" "open" "high" "low" "close"

CASE: FETCH ROW(S)
fetching row 1 of 5
2015-10-18 22:28:07.177 [EURUSD] Fetching row: 0
field[0][0] = 1
field[0][1] = USDJPY
field[0][2] = 240
field[0][3] = 1.03394
field[0][4] = 1.88400
field[0][5] = 1.75359
field[0][6] = 1.12827

fetching row 2 of 5
2015-10-18 22:28:07.286 [EURUSD] Fetching row: 1
field[1][0] = 2
field[1][1] = GBPUSD
field[1][2] = 1440
field[1][3] = 1.01556
field[1][4] = 1.62551
field[1][5] = 1.51595
field[1][6] = 1.37867

fetching row 3 of 5
2015-10-18 22:28:07.397 [EURUSD] Fetching row: 2
field[2][0] = 3
field[2][1] = USDCHF
field[2][2] = 60
field[2][3] = 1.34150
field[2][4] = 1.33103
field[2][5] = 1.32740
field[2][6] = 1.87555

fetching row 4 of 5
2015-10-18 22:28:07.503 [EURUSD] Fetching row: 3
field[3][0] = 4
field[3][1] = GBPUSD
field[3][2] = 30
field[3][3] = 1.98260
field[3][4] = 1.24717
field[3][5] = 1.60320
field[3][6] = 1.52986

fetching row 5 of 5
2015-10-18 22:28:07.640 [EURUSD] Fetching row: 4
field[4][0] = 5
field[4][1] = USDCHF
field[4][2] = 30
field[4][3] = 1.35322
field[4][4] = 1.90179
field[4][5] = 1.02179
field[4][6] = 1.21268

2015-10-18 22:28:07.757 [EURUSD] Clearing result... cleared

CASE: FIELD LIST ON CLEARED RESULT
2015-10-18 22:28:07.844 [EURUSD] Field list: N_A
2015-10-18 22:28:07.920 [EURUSD] ERROR: no active result found (probably cleared
?)
field_list = N_A

CASE: FETCH ROW(S) ON CLEARED RESULT
fetching row 1 of 5
2015-10-18 22:28:08.027 [EURUSD] Fetching row: 0
2015-10-18 22:28:08.053 [EURUSD] ERROR: no active result found (probably cleared
?)
field[0][0] = 5
field[0][1] = USDCHF
field[0][2] = 30
field[0][3] = 1.35322
field[0][4] = 1.90179
field[0][5] = 1.02179
field[0][6] = 1.21268

fetching row 2 of 5
2015-10-18 22:28:08.183 [EURUSD] Fetching row: 1
2015-10-18 22:28:08.290 [EURUSD] ERROR: no active result found (probably cleared
?)
field[1][0] = 5
field[1][1] = USDCHF
field[1][2] = 30
field[1][3] = 1.35322
field[1][4] = 1.90179
field[1][5] = 1.02179
field[1][6] = 1.21268

fetching row 3 of 5
2015-10-18 22:28:08.462 [EURUSD] Fetching row: 2
2015-10-18 22:28:08.505 [EURUSD] ERROR: no active result found (probably cleared
?)
field[2][0] = 5
field[2][1] = USDCHF
field[2][2] = 30
field[2][3] = 1.35322
field[2][4] = 1.90179
field[2][5] = 1.02179
field[2][6] = 1.21268

fetching row 4 of 5
2015-10-18 22:28:08.705 [EURUSD] Fetching row: 3
2015-10-18 22:28:08.738 [EURUSD] ERROR: no active result found (probably cleared
?)
field[3][0] = 5
field[3][1] = USDCHF
field[3][2] = 30
field[3][3] = 1.35322
field[3][4] = 1.90179
field[3][5] = 1.02179
field[3][6] = 1.21268

fetching row 5 of 5
2015-10-18 22:28:08.871 [EURUSD] Fetching row: 4
2015-10-18 22:28:08.916 [EURUSD] ERROR: no active result found (probably cleared
?)
field[4][0] = 5
field[4][1] = USDCHF
field[4][2] = 30
field[4][3] = 1.35322
field[4][4] = 1.90179
field[4][5] = 1.02179
field[4][6] = 1.21268


CASE: FETCH NON-EXISTENT ROW
2015-10-18 22:28:09.096 [EURUSD] Fetching row: 100
2015-10-18 22:28:09.120 [EURUSD] ERROR: no active result found (probably cleared
?)
field[0] = 5
field[1] = USDCHF
field[2] = 30
field[3] = 1.35322
field[4] = 1.90179
field[5] = 1.02179
field[6] = 1.21268

CASE: CLOSE CONNECTION
2015-10-18 22:28:09.312 [EURUSD] Closing connection [c:00FFE6D8, w:00FC5750] ...
 closed

CASE: QUERY ON CLOSED CONNECTION (SHOULD TRY RECONNECT)
2015-10-18 22:28:09.489 [EURUSD] ERROR: connection closed, trying to reconnect..
.
2015-10-18 22:28:09.540 [EURUSD] Closing connection [c:00000000, w:00FC5750] ...
 was already closed
2015-10-18 22:28:09.705 [EURUSD] Opening database connection (attempt:1) ... ope
ned [c:00FFE6D8, w:00FC5750]
2015-10-18 22:28:09.776 [EURUSD] SQL: SELECT * FROM "_test_data_table" LIMIT 5
2015-10-18 22:28:09.811 [EURUSD] OK: returned 5 rows (7 fields)

CASE: CLOSE ALREADY CLOSED CONNECTION
2015-10-18 22:28:09.914 [EURUSD] Closing connection [c:00FFE6D8, w:00FC5750] ...
 closed
2015-10-18 22:28:09.975 [EURUSD] Closing connection [c:00000000, w:00FC5750] ...
 was already closed

CASE: CALL QUERY ON DESTROYED WRAPPER

SUCCESS, HIT SOME KEY AND ENTER
```