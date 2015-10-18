// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

#include <iomanip>
#include <sstream>

// PostgreSQL
#include "libpq-fe.h"


#define DLLAPI extern "C" __declspec(dllexport)
#include "Mt4PostrgeSqlWrapper.h"
