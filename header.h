#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>


class inputData
{
private:
	std::vector<std::string> files;
	std::string directory;

public:
	inputData() = default;
	inputData(std::string dirName);

	std::string getDirectory();
	void setDirectory(std::string);

	void getFilesFromDirectory();
	void showFiles();
};