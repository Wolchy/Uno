#include "File.h"

File::File(std::string _path) {
	path = _path;
}

std::string File::read() {
	std::ifstream out(path);
	std::string line, output;
	if (out.is_open()){
		while (std::getline(out, line))
		{
			output = output + line + "\n";
		}
		out.close();
		return output;
	}
	return NULL;
	
}

bool File::writeString(std::string string, bool app) {
	std::ofstream in;
	if(app)
		in.open(path, std::ios::app);
	else
		in.open(path);
	if (!in) {
		std::cout << "ofstream error: connot open file!" << std::endl;
		return false;
	}
	if (in.is_open())
		in << string;
	in.close();
	return true;
}

bool File::isGood() {
	std::ifstream out(path);
	return out.good();
}

std::string File::getPath() {
	return path;
}
