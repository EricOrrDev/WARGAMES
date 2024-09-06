#include "oldprint.h"

#include <stdio.h>

void oldSchoolPrint(const char* str, const size_t length, const unsigned int delayMS){
	for(size_t i = 0; i < length && str[i] != '\0'; i++){
		printf("%c", str[i]);
		fflush(stdout);
	#ifdef _WIN32
		Sleep(delayMS);
	#else
		usleep(delayMS * 1000); //linux uses microseconds instead of milliseconds
	#endif
	}
};
