#pragma once

#include <sys/stat.h>


#ifdef _WIN32
	#include <io.h>
	#include <windows.h>
	#include <limits.h>
	#include <winnt.h>
	void createDirectory(char* path);
	extern unsigned long currentResolution;
	unsigned long setHighestTimerResolution(unsigned long timer_res_us);
	void usleep(__int64 usec);

#else
	#include <sys/io.h>
	#include <unistd.h>
	void createDirectory(char* path);
#endif

inline void createDirectory(const char* path){
	createDirectory((char*) path);
}

bool hasDirectory(char* path);

inline bool hasDirectory(const char* path){
	return hasDirectory((char*) path);
}

void sleepmicro(unsigned long long int usec);
