#include <utils/logging.h>

#include <stdio.h>
#include <stdlib.h>

void kdLogInit()
{
    FILE* log_file = fopen("traceback.log", "w");
    fprintf(log_file, "");
    fclose(log_file);
}

void kdLogRow(const char* message, int line, const char* file)
{
    FILE* log_file = fopen("traceback.log", "a");
    fprintf(log_file, "LOG: %s\n(file: %s, line: %d)\n", message, file, line);
    fclose(log_file);
}