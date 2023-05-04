#include "header.h"

int main()
{
    std::string dirName = "input_files";

    parseData data(dirName);

    std::cout << data.getDirectory() << std::endl;
    data.getFilesFromDirectory();
    data.showFiles();
    data.getStudentsInfo();


    //Table table;
    //table.sortStudents();
    /*for (int i = 0; i < 40; ++i)
        std::cout << data.students[i]->name << std::endl;*/
}
