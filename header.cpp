#include "header.h"
// ---------------------- Person ---------------------- 

std::string Person::getName()
{
	return this->name;
}

void Person::setName(std::string name_val)
{
	this->name = name_val;
}

// ---------------------- Student ---------------------- 
double Student::getAvgScore()
{
	return this->avgScore;
}

void Student::setAvgScore(double val)
{
	this->avgScore = val;
}

bool Student::getBudgetPlace()
{
	return this->budgetPlace;
}

void Student::setBudgetPlace(bool val)
{
	this->budgetPlace = val;
}

void Student::printStudent()
{
	std::cout << "name: " << this->getName() << std::endl;
	std::cout << "avgScore: " << this->avgScore << std::endl;
	std::cout << "budgetPlace: " << ((this->budgetPlace) ? "True" : "False") << std::endl;
	std::cout << std::endl;
}

// ---------------------- Table ---------------------- 

void Table::sortStudents(parseData& data)
{
	for (int i = 0; i < data.totalLine - 1; ++i)
	{
		int j = i + 1;

		while (j > 0 && (data.students[j]->getAvgScore()) > (data.students[j - 1]->getAvgScore()))
		{
			Student* temp = data.students[j - 1];
			data.students[j - 1] = data.students[j];
			data.students[j] = temp;
			--j;
		}
	}
}


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
// ---------------------- parseData ---------------------- 

parseData::parseData(std::string dirName) : inputData(dirName), lineCount(0), totalLine(0)
{

}

void parseData::getStudentsInfo()
{
	for (int i = 0; i < files.size(); ++i)
	{
		this->fileName = files[i];

		std::ifstream input;
		input.open(this->fileName);

		assert(input.is_open());

		input >> this->lineCount;
		input.get();

		this->totalLine += this->lineCount;

		for (int j = 0; j < this->lineCount; ++j)
		{
			parseStudentInfo(input);
		}

		input.close();
	}
}

void parseData::printStudents()
{
	for (int i = 0; i < this->totalLine; ++i)
		students[i]->printStudent();
}

void parseData::parseStudentInfo(std::istream& input)
{
	students.push_back(new Student());
	int index = students.size();

	int sum = 0;
	std::string line;

	std::getline(input, line);
	std::istringstream is(line);

	std::string word;
	std::getline(is, word, ',');

	students[index - 1]->setName(word);

	int count = 0;
	while (std::getline(is, word, ',') && word != "TRUE" && word != "FALSE")
	{
		//std::cout << word << " ";
		sum += std::stoi(word);
		++count;
	}

	students[index - 1]->setAvgScore(sum / (double)count);
	students[index - 1]->setBudgetPlace(word == "TRUE");
}

