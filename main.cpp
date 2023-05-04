#include "header.h"

int main()
{
    std::string dirName = "input_files";

    inputData data(dirName);

    std::cout << data.getDirectory() << std::endl;
    data.getFilesFromDirectory();
    data.showFiles();
}
