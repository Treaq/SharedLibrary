#include <iostream>
#include "SharedLibrary.hpp"

int main(int argc, char* argv[]) {
	SharedLibrary lib;
	if (!lib.Load("Math")) {
		std::cout << "Library not load: " << lib.GetError() << std::endl;
		return 1;
	};

	void* pfunc = lib.GetDataAddress("Add");
	if (!pfunc) {
		std::cout << "Function not load: " << lib.GetError() << std::endl;
		return 1;
	}

	int(*funcAdd)(int, int) = (int(*)(int, int))pfunc;
	
	std::cout << funcAdd(1, 1) << std::endl;

	return 0;
}