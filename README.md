# SharedLibrary
Helper class for using dynamic libraries

## Description
The class is a small class that, using the operating system API, loads a dynamic library into the program. The loaded library can be accessed by obtaining its methods or properties, leading to the required type already at the call site.

## Supported platforms
- Windows
- Linux
- Android

## Supported architectures
- x64
- x86
- ARM
- ARM64

## Example
	#include <iostream>
	#include "SharedLibrary.hpp"

	int main(int argc, char* argv[]) {
		//Create object
		SharedLibrary lib;
		
		//Call the "load" method to load the library into the application
		if (!lib.Load("Math")) {
			std::cout << "Library not load: " << lib.GetError() << std::endl;
			return 1;
		};

		//Get the address of the data (function or property)
		void* pfunc = lib.GetDataAddress("Add");
		if (!pfunc) {
			std::cout << "Function not load: " << lib.GetError() << std::endl;
			return 1;
		}

		//Casting a pointer to a function
		int(*funcAdd)(int, int) = (int(*)(int, int))pfunc;
		
		std::cout << funcAdd(1, 1) << std::endl;

		//Unloading the library from the application. It will also be unloaded when the object is destroyed
		lib.Unload();
		return 0;
	}