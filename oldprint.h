#ifndef OLDPRINT_H
#define OLDPRINT_H

#include <stdio.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include <unistd.h>

void oldSchoolPrint(const char* str, const size_t length, const unsigned int delayMS);

#endif
