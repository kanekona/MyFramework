#pragma once

#if	defined(KL_DEBUG) || defined(ENGINE_DEBUG)
#define DEBUG_ENABLE true
#else
#define DEBUG_ENABLE false
#endif

#if defined(ENGINE_DEBUG) || defined(ENGINE_RELEASE)
#define ENGINE_DEVELOP true
#else
#define ENGINE_DEVELOP false
#endif

#if (DEBUG_ENABLE || ENGINE_DEVELOP)
#define PACKAGE false
#else
#define PACKAGE true
#endif

#ifdef _WIN64
#define WIN64_BUILD true
#else
#define WIN64_BUILD false
#endif // _WIN64

#ifdef _WIN32
#define WIN32_BUILD true
#else
#define WIN32_BUILD false
#endif // _WIN32

#if (WIN32_BUILD || WIN64_BUILD)
#define WINDOWS_BUILD true
#else
#define WINDOWS_BUILD false
#endif 

#ifdef __unix__
#define UNIX_BUILD true
#else
#define UNIX_BUILD false
#endif // __unix__

#ifdef __linux__
#define LINUX_BUILD true
#else
#define LINUX_BUILD false
#endif // __linux__



#if DEBUG_ENABLE

#include <stdio.h>
#include <stdlib.h>

bool KLEnsure(bool flag);
bool KLEnsure(bool flag, const char* msg);
bool KLCheck(bool flag);
bool KLCheck(bool flag, const char* msg);

#define ENSURE(flag) KLEnsure(flag)
#define ENSUREMSG(flag,ErrorMsg) KLEnsure(flag,ErrorMsg)
#define CHECK(flag) KLCheck(flag)
#define CHECKMSG(flag,ErrorMsg) KLCheck(flag,ErrorMsg)
#endif