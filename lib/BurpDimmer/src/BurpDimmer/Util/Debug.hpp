#pragma once

#define BURP_DEBUG_LEVEL_OFF    0
#define BURP_DEBUG_LEVEL_ERROR  1
#define BURP_DEBUG_LEVEL_WARN   2
#define BURP_DEBUG_LEVEL_INFO   3

#define BURP_DEBUG_ERROR(...)
#define BURP_DEBUG_WARN(...)
#define BURP_DEBUG_INFO(...)
#define BURP_DEBUG_DO
#define BURP_DEBUG_STR(VAL)

/*
 * Default debug level is off, override in build flags
 * to enable debug
 */
#ifndef BURP_DEBUG_LEVEL
#define BURP_DEBUG_LEVEL BURP_DEBUG_LEVEL_OFF
#endif

#if BURP_DEBUG_LEVEL > BURP_DEBUG_LEVEL_OFF // BURP_DEBUG_ERROR and up
#ifdef NATIVE
#define _BURP_DEBUG_PRINTF printf
#else
#include <Arduino.h>
#define _BURP_DEBUG_PRINTF Serial.printf
#endif

#define _BURP_DEBUG_PRINT(LEVEL, ...) { _BURP_DEBUG_PRINTF("%s: %s: %s: %d: ", LEVEL, __FILE__, __func__, __LINE__); _BURP_DEBUG_PRINTF(__VA_ARGS__); _BURP_DEBUG_PRINTF("\n"); }

#undef BURP_DEBUG_STR
#define BURP_DEBUG_STR(VAL) (VAL.toString().c_str())

#undef BURP_DEBUG_ERROR
#define BURP_DEBUG_ERROR(...) _BURP_DEBUG_PRINT("ERROR ", __VA_ARGS__)
#endif

#if BURP_DEBUG_LEVEL > BURP_DEBUG_LEVEL_ERROR // BURP_DEBUG_WARN and up
#undef BURP_DEBUG_WARN
#define BURP_DEBUG_WARN(...) _BURP_DEBUG_PRINT("WARN  ", __VA_ARGS__)
#endif

#if BURP_DEBUG_LEVEL > BURP_DEBUG_LEVEL_WARN // BURP_DEBUG_INFO and up
#undef BURP_DEBUG_INFO
#define BURP_DEBUG_INFO(...) _BURP_DEBUG_PRINT("INFO  ", __VA_ARGS__)
#endif
