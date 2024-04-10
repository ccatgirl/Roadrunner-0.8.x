#include <sys/stat.h>


#ifdef _WIN32
	#include <io.h>
	#include <windows.h>
	
	void createDirectory(char* path){
		CreateDirectory(path, NULL);
	}
#else
	#include <sys/io.h>
	void createDirectory(char* path){
		mkdir(path, 0777);
	}
#endif

inline void createDirectory(const char* path){
	createDirectory((char*) path);
}

bool hasDirectory(char* path){
	if(access(path, 0) == 0){
		struct stat status;
		stat(path, &status);
		return (status.st_mode & S_IFDIR) != 0;
	}
	return false;
}

inline bool hasDirectory(const char* path){
	return hasDirectory((char*) path);
}
