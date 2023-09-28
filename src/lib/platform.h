#ifndef SOL2TEST_PLATFORM_H
#define SOL2TEST_PLATFORM_H

#if defined(_WIN32) && !defined(STATIC_LIB)
#ifdef EXPORT_API_SYMBOLS
#define API_EXPORT __declspec(dllexport)
#else
#define API_EXPORT __declspec(dllimport)
#endif //EXPORT_API_SYMBOLS
#else
#define API_EXPORT
#endif //_WIN32

#endif //SOL2TEST_PLATFORM_H
