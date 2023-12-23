#pragma once

extern void kdLogInit();
extern void kdLogRow(const char* message, int line, const char* file);

#define kdLog(message) kdLogRow(message, __LINE__, __FILE__)