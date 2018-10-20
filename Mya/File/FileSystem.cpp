#include "FileSystem.h"

FileSystem::FileSystem(){}

void FileSystem::createDir(std::string string){
	_mkdir(string.c_str());
}

void FileSystem::deleteDir(std::string string){
	_rmdir(string.c_str());
}

void FileSystem::createFile(std::string string){
	std::ofstream o(string);
	o.close();
}

void FileSystem::deleteFile(std::string string){
	remove(string.c_str());
}