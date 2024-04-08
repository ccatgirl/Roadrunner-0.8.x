#include <sys/stat.h>
#include <io.h>

#ifdef _WIN32
	#include <windows.h>
	
	void createDirectory(char* path){
		CreateDirectory(path, NULL);
	}
#else
	void createDirectory(char* path){
		mkdir(path, 777);
	}
#endif

inline void createDirectory(const char* path){
	createDirectory((char*) path);
}

bool hasDirectory(char* path){
	if(_access(path, 0) == 0){
		struct stat status;
		stat(path, &status);
		return (status.st_mode & S_IFDIR) != 0;
	}
	return false;
}

inline bool hasDirectory(const char* path){
	return hasDirectory((char*) path);
}