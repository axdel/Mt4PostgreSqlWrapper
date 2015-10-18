# Test stdout (should be pretty self-explanatory)

```
CASE: UNSUCCESSFUL CONNECTION
2015-10-18 20:50:37.418 [EURUSD] Opening database connection (attempt:1) ... fai
led [004592E0, w:00455750]
fe_sendauth: no password supplied

2015-10-18 20:50:38.605 [EURUSD] Opening database connection (attempt:2) ... fai
led [004692D0, w:00455750]
fe_sendauth: no password supplied

2015-10-18 20:50:40.573 [EURUSD] Closing connection [c:004692D0, w:00455750] ...
 closed
2015-10-18 20:50:40.589 [EURUSD] Closing connection [c:00000000, w:00455750] ...
 was already closed

CASE: WRITE LOG
2015-10-18 20:50:40.651 [EURUSD] Is this the most important message or what?

CASE: SUCCESSFUL CONNECTION
2015-10-18 20:50:40.854 [EURUSD] Opening database connection (attempt:1) ... ope
ned [c:0048E6D8, w:00455750]
client version = 90404
server version = 90404

CASE: EMPTY QUERY
2015-10-18 20:50:41.011 [EURUSD] SQL:
2015-10-18 20:50:41.027 [EURUSD] Clearing result... cleared
2015-10-18 20:50:41.136 [EURUSD] ERROR: empty query
2015-10-18 20:50:41.230 [EURUSD] Clearing result... was already cleared

CASE: DROP TABLE IF EXISTS
2015-10-18 20:50:41.605 [EURUSD] SQL: DROP TABLE IF EXISTS "_test_data_table"
2015-10-18 20:50:41.652 [EURUSD] OK: nothing returned

CASE: CREATE TABLE
2015-10-18 20:50:41.776 [EURUSD] Clearing result... cleared
2015-10-18 20:50:41.995 [EURUSD] SQL: CREATE TABLE "_test_data_table" (id SERIAL
 NOT NULL,symbol VARCHAR,timeframe INTEGER,open NUMERIC(10, 5),high NUMERIC(10,
5),low NUMERIC(10, 5),close NUMERIC(10, 5),PRIMARY KEY (id))
2015-10-18 20:50:42.230 [EURUSD] OK: nothing returned

CASE: INSERT RANDOM DATA
2015-10-18 20:50:42.276 [EURUSD] Clearing result... cleared
2015-10-18 20:50:42.401 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol",
"timeframe", "open", "high", "low", "close") VALUES ('EURUSD', 15, 1.6719, 1.538
74, 1.81603, 1.54619)
2015-10-18 20:50:42.542 [EURUSD] OK: 1 affected row(s)
affected_rows = 1
2015-10-18 20:50:42.589 [EURUSD] Clearing result... cleared
2015-10-18 20:50:42.636 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol",
"timeframe", "open", "high", "low", "close") VALUES ('GBPUSD', 1440, 1.92816, 1.
38212, 1.31199, 1.57442)
2015-10-18 20:50:42.808 [EURUSD] OK: 1 affected row(s)
affected_rows = 1
2015-10-18 20:50:42.870 [EURUSD] Clearing result... cleared
2015-10-18 20:50:42.933 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol",
"timeframe", "open", "high", "low", "close") VALUES ('USDCHF', 60, 1.77178, 1.50
768, 1.89227, 1.55068)
2015-10-18 20:50:43.089 [EURUSD] OK: 1 affected row(s)
affected_rows = 1
2015-10-18 20:50:43.137 [EURUSD] Clearing result... cleared
2015-10-18 20:50:43.198 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol",
"timeframe", "open", "high", "low", "close") VALUES ('EURUSD', 15, 1.45628, 1.39
717, 1.25608, 1.19834)
2015-10-18 20:50:43.323 [EURUSD] OK: 1 affected row(s)
affected_rows = 1
2015-10-18 20:50:43.417 [EURUSD] Clearing result... cleared
2015-10-18 20:50:43.480 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol",
"timeframe", "open", "high", "low", "close") VALUES ('EURUSD', 30, 1.51018, 1.58
547, 1.759, 1.18619)
2015-10-18 20:50:43.653 [EURUSD] OK: 1 affected row(s)
affected_rows = 1
2015-10-18 20:50:43.683 [EURUSD] Clearing result... cleared
2015-10-18 20:50:43.761 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol",
"timeframe", "open", "high", "low", "close") VALUES ('GBPUSD', 240, 1.17594, 1.8
5134, 1.6813, 1.59511)
2015-10-18 20:50:43.901 [EURUSD] OK: 1 affected row(s)
affected_rows = 1
2015-10-18 20:50:43.980 [EURUSD] Clearing result... cleared
2015-10-18 20:50:44.026 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol",
"timeframe", "open", "high", "low", "close") VALUES ('GBPUSD', 15, 1.51448, 1.36
363, 1.56331, 1.12235)
2015-10-18 20:50:44.183 [EURUSD] OK: 1 affected row(s)
affected_rows = 1
2015-10-18 20:50:44.230 [EURUSD] Clearing result... cleared
2015-10-18 20:50:44.292 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol",
"timeframe", "open", "high", "low", "close") VALUES ('EURUSD', 15, 1.65603, 1.53
917, 1.60582, 1.27537)
2015-10-18 20:50:44.448 [EURUSD] OK: 1 affected row(s)
affected_rows = 1
2015-10-18 20:50:44.495 [EURUSD] Clearing result... cleared
2015-10-18 20:50:44.526 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol",
"timeframe", "open", "high", "low", "close") VALUES ('USDCHF', 240, 1.78088, 1.6
675, 1.03317, 1.83764)
2015-10-18 20:50:44.651 [EURUSD] OK: 1 affected row(s)
affected_rows = 1
2015-10-18 20:50:44.745 [EURUSD] Clearing result... cleared
2015-10-18 20:50:44.808 [EURUSD] SQL: INSERT INTO "_test_data_table" ("symbol",
"timeframe", "open", "high", "low", "close") VALUES ('GBPUSD', 30, 1.87655, 1.20
414, 1.70287, 1.09662)
2015-10-18 20:50:44.980 [EURUSD] OK: 1 affected row(s)
affected_rows = 1

CASE: SELECT * FROM
2015-10-18 20:50:45.059 [EURUSD] Clearing result... cleared
2015-10-18 20:50:45.136 [EURUSD] SQL: SELECT * FROM "_test_data_table" LIMIT 5
2015-10-18 20:50:45.324 [EURUSD] OK: returned 5 rows (7 fields)
num_rows = 5, num_fields = 7
affected_rows =

CASE: GET FIELD LIST
2015-10-18 20:50:45.448 [EURUSD] Field list: "id" "symbol" "timeframe" "open" "h
igh" "low" "close"
field_list = "id" "symbol" "timeframe" "open" "high" "low" "close"

CASE: FETCH ROW(S)
fetching row 1 of 5
2015-10-18 20:50:45.729 [EURUSD] Fetching row: 0
field[0][0] = 1
field[0][1] = EURUSD
field[0][2] = 15
field[0][3] = 1.67190
field[0][4] = 1.53874
field[0][5] = 1.81603
field[0][6] = 1.54619

fetching row 2 of 5
2015-10-18 20:50:45.979 [EURUSD] Fetching row: 1
field[1][0] = 2
field[1][1] = GBPUSD
field[1][2] = 1440
field[1][3] = 1.92816
field[1][4] = 1.38212
field[1][5] = 1.31199
field[1][6] = 1.57442

fetching row 3 of 5
2015-10-18 20:50:46.245 [EURUSD] Fetching row: 2
field[2][0] = 3
field[2][1] = USDCHF
field[2][2] = 60
field[2][3] = 1.77178
field[2][4] = 1.50768
field[2][5] = 1.89227
field[2][6] = 1.55068

fetching row 4 of 5
2015-10-18 20:50:46.512 [EURUSD] Fetching row: 3
field[3][0] = 4
field[3][1] = EURUSD
field[3][2] = 15
field[3][3] = 1.45628
field[3][4] = 1.39717
field[3][5] = 1.25608
field[3][6] = 1.19834

fetching row 5 of 5
2015-10-18 20:50:46.699 [EURUSD] Fetching row: 4
field[4][0] = 5
field[4][1] = EURUSD
field[4][2] = 30
field[4][3] = 1.51018
field[4][4] = 1.58547
field[4][5] = 1.75900
field[4][6] = 1.18619

2015-10-18 20:50:47.012 [EURUSD] Clearing result... cleared

CASE: FIELD LIST ON CLEARED RESULT
2015-10-18 20:50:47.136 [EURUSD] Field list: N_A
2015-10-18 20:50:47.183 [EURUSD] ERROR: no active result found (probably cleared
?)
field_list = N_A

CASE: FETCH ROW(S) ON CLEARED RESULT
fetching row 1 of 5
2015-10-18 20:50:47.292 [EURUSD] Fetching row: 0
2015-10-18 20:50:47.354 [EURUSD] ERROR: no active result found (probably cleared
?)
field[0][0] = 5
field[0][1] = EURUSD
field[0][2] = 30
field[0][3] = 1.51018
field[0][4] = 1.58547
field[0][5] = 1.75900
field[0][6] = 1.18619

fetching row 2 of 5
2015-10-18 20:50:47.651 [EURUSD] Fetching row: 1
2015-10-18 20:50:47.730 [EURUSD] ERROR: no active result found (probably cleared
?)
field[1][0] = 5
field[1][1] = EURUSD
field[1][2] = 30
field[1][3] = 1.51018
field[1][4] = 1.58547
field[1][5] = 1.75900
field[1][6] = 1.18619

fetching row 3 of 5
2015-10-18 20:50:48.120 [EURUSD] Fetching row: 2
2015-10-18 20:50:48.183 [EURUSD] ERROR: no active result found (probably cleared
?)
field[2][0] = 5
field[2][1] = EURUSD
field[2][2] = 30
field[2][3] = 1.51018
field[2][4] = 1.58547
field[2][5] = 1.75900
field[2][6] = 1.18619

fetching row 4 of 5
2015-10-18 20:50:48.513 [EURUSD] Fetching row: 3
2015-10-18 20:50:48.558 [EURUSD] ERROR: no active result found (probably cleared
?)
field[3][0] = 5
field[3][1] = EURUSD
field[3][2] = 30
field[3][3] = 1.51018
field[3][4] = 1.58547
field[3][5] = 1.75900
field[3][6] = 1.18619

fetching row 5 of 5
2015-10-18 20:50:48.761 [EURUSD] Fetching row: 4
2015-10-18 20:50:48.808 [EURUSD] ERROR: no active result found (probably cleared
?)
field[4][0] = 5
field[4][1] = EURUSD
field[4][2] = 30
field[4][3] = 1.51018
field[4][4] = 1.58547
field[4][5] = 1.75900
field[4][6] = 1.18619


CASE: FETCH NON-EXISTENT ROW
2015-10-18 20:50:48.995 [EURUSD] Fetching row: 100
2015-10-18 20:50:49.042 [EURUSD] ERROR: no active result found (probably cleared
?)
field[0] = 5
field[1] = EURUSD
field[2] = 30
field[3] = 1.51018
field[4] = 1.58547
field[5] = 1.75900
field[6] = 1.18619
2015-10-18 20:50:49.214 [EURUSD] Closing connection [c:0048E6D8, w:00455750] ...
 closed

CASE: QUERY ON CLOSED CONNECTION (SHOULD TRY RECONNECT)
2015-10-18 20:50:49.417 [EURUSD] ERROR: connection closed, trying to reconnect..
.
2015-10-18 20:50:49.495 [EURUSD] Closing connection [c:00000000, w:00455750] ...
 was already closed
2015-10-18 20:50:49.714 [EURUSD] Opening database connection (attempt:1) ... ope
ned [c:0048E6D8, w:00455750]
2015-10-18 20:50:49.839 [EURUSD] SQL: SELECT * FROM "_test_data_table" LIMIT 5
2015-10-18 20:50:50.012 [EURUSD] OK: returned 5 rows (7 fields)

CASE: CLOSE ALREADY CLOSED CONNECTION
2015-10-18 20:50:50.167 [EURUSD] Closing connection [c:0048E6D8, w:00455750] ...
 closed
2015-10-18 20:50:50.294 [EURUSD] Closing connection [c:00000000, w:00455750] ...
 was already closed

SUCCESS, HIT SOME KEY AND ENTER
```