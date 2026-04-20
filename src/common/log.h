#ifndef __LOG_H
#define __LOG_H

#include <stdio.h>
#include <errno.h>

//
#define TRACE_INFO(msg, ...) do { fprintf(stdout, "[INFO] %s(): " msg "", __func__, ##__VA_ARGS__); } while (0)
#define TRACE_WARNING(msg, ...) do { fprintf(stderr, "[WARNING] %s(): " msg "", __func__, ##__VA_ARGS__); } while(0)
#define TRACE_ERROR(msg, ...) do { fprintf(stderr, "[ERROR] %s(): " msg "", __func__, ##__VA_ARGS__); exit(1); } while(0)

#define TRACE_INFO_NO_FNC(msg, ...) do { fprintf(stdout, "[INFO]: " msg "", ##__VA_ARGS__); } while (0)
#define TRACE_WARNING_NO_FNC(msg, ...) do { fprintf(stderr, "[WARNING]: " msg "", ##__VA_ARGS__); } while(0)
#define TRACE_ERROR_NO_FNC(msg, ...) do { fprintf(stderr, "[ERROR]: " msg "", ##__VA_ARGS__); exit(1); } while(0)

// critical error for loading DLL
#define DLL_ERROR do { fprintf(stderr, "[DLL_ERROR] %s(): %s\n", __func__, dlerror()); exit(1); } while(0)

#endif // __LOG_H
