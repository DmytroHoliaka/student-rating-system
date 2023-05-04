#include "header.h"

// ---------------------- inputData ---------------------- 


inputData::inputData(std::string dirName) : directory(dirName) 
{ 

}

std::string inputData::getDirectory()
{
	return this->directory;
}

void inputData::setDirectory(std::string dirName)
{
	this->directory = dirName;
}

void inputData::showFiles()
{
    std::string spacer = "------------------------";

    std::cout << spacer << std::endl;
    for (const auto& file : this->files)
        std::cout << file << std::endl;
    std::cout << spacer << std::endl;
}

void inputData::getFilesFromDirectory()
{
    for (const auto& file : std::filesystem::directory_iterator(this->directory))
    {
        if (std::filesystem::is_regular_file(file)) {
            files.push_back(file.path().string());
        }
    }
}























// ---------------------- inputData ---------------------- 






// ---------------------- inputData ---------------------- 






// ---------------------- inputData ---------------------- 






// ---------------------- inputData ---------------------- 