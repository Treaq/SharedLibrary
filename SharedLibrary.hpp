#pragma once

#include <string>

#if defined _WIN32
#include <Windows.h>
typedef HMODULE libHandle;
typedef FARPROC dataHandle;

#elif defined __linux__ || defined __ANDROID__
#include <dlfcn.h>
typedef void* libHandle;
typedef void* dataHandle;
#endif

class SharedLibrary {
private:
	libHandle handle = libHandle();
	std::string error;
	
	void FillErrorOS();

public:
	~SharedLibrary();
	SharedLibrary();
	SharedLibrary(std::string path);

	virtual bool isLoaded();
	virtual std::string GetError();
	virtual void Unload();
	virtual bool Load(std::string pathLibrary);
	virtual void* GetDataAddress(std::string name);
};