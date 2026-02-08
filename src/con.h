#pragma once

#include <stdio.h>
#define CON_LOG(L, FMT, ...) printf(__FILE__ ":%d: " FMT "\n", __LINE__, ## __VA_ARGS__)
#define CON_INFO(FMT, ...) CON_LOG(CON_LOG_INFO, FMT, ## __VA_ARGS__)
#define CON_ERROR(FMT, ...) CON_LOG(CON_LOG_ERROR, FMT, ## __VA_ARGS__)

typedef enum {
  CON_LOG_ERROR,
  CON_LOG_WARN,
  CON_LOG_INFO,
} CON_LogLevel;

void CON_Log(CON_LogLevel level, const char* fmt, ...);

