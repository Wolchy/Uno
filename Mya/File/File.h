#pragma once

#include <iostream>
#include <fstream>
#include <string>

class File {
public:
	File(std::string);

	std::string read();
	bool writeString(std::string,bool);
	bool isGood();
	std::string getPath();

private:
	std::string path;
};