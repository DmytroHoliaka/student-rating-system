#include "header.h"

// ToDo: Оптимізувати метод getStudents
// ToDo: Опримізувати порядок методів в header.cpp

int main(int argc, char* argv[])
{
	std::setlocale(LC_ALL, "uk_UA.UTF-8");
	std::string fileOutputName = "rating.csv";
	Validator validator;
	try {
		if (argc == 1)
		{
			std::cerr << "Parameter not passed" << std::endl;
			exit(22);
		}

		std::string dirName = argv[1];
		ParseData data(dirName);

		data.processFilesFromDirectory();
		
		std::cout << data.getFiles();

		std::vector<Student*> studentsFromAllFiles = data.getStudents(validator);
		//std::cout << studentsFromAllFiles;

		checkTotalLine(data);

		Table table(data, studentsFromAllFiles);
		//table.fillBudgetStudents(data, studentsFromAllFiles);

		std::cout << "BudgetAmount: " << table.calculateBudgetAmount() << std::endl;
		std::cout << "ScolarshipAmount: " << table.calculateScolarshipAmount() << std::endl;

		//std::cout << table.getScolarshipStudents() << std::endl;
		
		table.sortStudents();

		std::ofstream file(fileOutputName);
		if (!file.is_open())
		{
			std::cerr << "Can't open file " << fileOutputName << " for writing" << std::endl;
			exit(2);
		}

		file << table;
		std::cout << "Minimum scolarship score: ";
		std::cout << std::fixed << std::setprecision(3) << table.calculateMinScolarshipScore() << std::endl;

		//std::cout << table.getScolarshipStudents() << std::endl;
		std::cout << validator << std::endl;
		std::cout << studentsFromAllFiles << std::endl;
	}
	catch (std::range_error err) {
		std::cout << err.what() << std::endl;
	}
	catch (std::domain_error err) {
		std::cout << err.what() << std::endl;
		std::cout << validator << std::endl;
	}
	catch (std::out_of_range err) {
		std::cout << err.what() << std::endl;
	}
}
