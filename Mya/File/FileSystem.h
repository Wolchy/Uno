#pragma once

#include <iostream>
#include <fstream>
#include <direct.h>

class FileSystem {
public:
	FileSystem();

	void createDir(std::string);
	void deleteDir(std::string);
	void createFile(std::string);
	void deleteFile(std::string);
};