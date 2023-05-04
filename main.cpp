#include "header.h"

int main()
{
    std::string dirName = "input_files";

    parseData data(dirName);

    std::cout << data.getDirectory() << std::endl;
    data.getFilesFromDirectory();
    data.showFiles();
    data.getStudentsInfo();
    
    data.printStudents();
}

// Добавляю функцію виведення всіх елементів students
