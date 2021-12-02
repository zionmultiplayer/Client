#include "Zion/Log.hh"
#include <stdarg.h>
#include <stdio.h>

static FILE *file = nullptr;

void Zion::Log::Open(const char *filename)
{
    file = fopen("zion/log.txt", "w");
}

void Zion::Log::Close()
{
    fclose(file);
    file = nullptr;
}

void Zion::Log::Write(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    vfprintf(file, format, args);

    va_end(args);
}