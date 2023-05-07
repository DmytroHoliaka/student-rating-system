#include "header.h"

int main(int argc, char* argv[])
{
	std::setlocale(LC_ALL, "uk_UA.UTF-8");

	try {
		if (argc <= 1)
			throw std::out_of_range("Parameter not passed");

		std::string dirName = argv[1];
		parseData data(dirName);

		//std::cout << data.getDirectory() << std::endl;
		data.getFilesFromDirectory();
		//data.showFiles();

		std::vector<Student*> studentsFromAllFiles = data.getStudentsInfo();
		//data.printStudents();
		data.checkTotalLine();

		Table table;
		table.fillBudgetStudents(data, studentsFromAllFiles);

		table.calculateBudgetAmount();
		table.calculateScolarshipAmount();

		table.sortStudents();
		table.outputDataIntoFile();

		table.calculateMinScolarshipScore();
		std::cout << "Minimum scolarship score: ";
		std::cout << std::fixed << std::setprecision(3) << table.getMinScolarshipScore() << std::endl;

		//data.printStudents();
	}
	catch (std::range_error err) {
		std::cout << err.what() << std::endl;
	}
	catch (std::runtime_error err) {
		std::cout << err.what() << std::endl;
	}
	catch (std::out_of_range err) {
		std::cout << err.what() << std::endl;
	}
}
