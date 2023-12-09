
#include "SharedLibrary.hpp"

SharedLibrary::~SharedLibrary() {
	Unload();
}
SharedLibrary::SharedLibrary() {};
SharedLibrary::SharedLibrary(std::string path) {
	Load(path);
}
std::string SharedLibrary::GetError() {
	return error;
}
bool SharedLibrary::isLoaded() {
	return handle != libHandle();
}

void SharedLibrary::FillErrorOS() {
#if defined _WIN32
	const DWORD size = 1024;
	CHAR buffer[size];
	FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(), 0, buffer, size, NULL);
	error = buffer;
#elif defined __linux__
	error = dlerror();
#endif
}
bool SharedLibrary::Load(std::string pathLibrary) {
	error.clear();

	if (isLoaded())
		Unload();

	auto len = pathLibrary.length();
	if (len == 0) {
		error = "Incorrect path library";
		return false;
	}

#if defined _WIN32
	len++;
	wchar_t* path = new wchar_t[len];
	memset(path, 0, len);

	for (auto i = 0; i < len; i++) {
		path[i] = (int)pathLibrary[i];
	}

	handle = LoadLibrary(path);
	delete[] path;
#elif defined __linux__
	handle = dlopen(pathLibrary.c_str(), RTLD_LAZY);
#endif

	if (handle == libHandle())
		FillErrorOS();

	if (error.length() > 0)
		return false;

	return true;
}
void SharedLibrary::Unload() {
	error.clear();
	if (!isLoaded())
		return;

#if defined _WIN32
	FreeLibrary(handle);
#elif defined __linux__
	dlclose(handle);
#endif
	handle = libHandle();
}
void* SharedLibrary::GetDataAddress(std::string name) {
	error.clear();
	if (!isLoaded()) {
		error = "Library not loaded";
		return nullptr;
	}

	dataHandle hnd = dataHandle();
#if defined _WIN32
	hnd = GetProcAddress(handle, name.c_str());
#elif defined __linux__
	hnd = dlsym(handle, name.c_str());
#endif

	if (hnd == dataHandle()) {
		FillErrorOS();
		return nullptr;
	}
	return (void*)hnd;
}