#include "header.h"

int main()
{
    std::string dirName = "input_files";
    parseData data(dirName);

    //std::cout << data.getDirectory() << std::endl;
    data.getFilesFromDirectory();
    //data.showFiles();

    data.getStudentsInfo();
    //data.printStudents();

    Table table;
    table.fillBudgetStudents(data);
    
    table.calculateBudgetAmount();
    table.calculateScolarshipAmount();

    table.sortStudents();
    table.outputDataIntoFile();

    table.calculateMinScolarshipScore();
    std::cout << "Minimum scolarship score: ";
    std::cout << std::fixed << std::setprecision(3) << table.getMinScolarshipScore() << std::endl;
    
    //data.printStudents();
}
