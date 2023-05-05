#include "header.h"
// ---------------------- Person ---------------------- 

Person::Person(std::string name_val)
{
	this->name = name_val;
}

std::string Person::getName()
{
	return this->name;
}

void Person::setName(std::string name_val)
{
	this->name = name_val;
}

Student::Student()
{
	this->avgScore = 0;
	this->contractPlace = true;
}

Student::Student(std::string _name, double _avgScore, bool _contractPlace) : Person(_name)
{
	this->avgScore = _avgScore;
	this->contractPlace = _contractPlace;
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

bool Student::getContractPlace()
{
	return this->contractPlace;
}

void Student::setContractPlace(bool val)
{
	this->contractPlace = val;
}

void Student::printStudent()
{
	std::cout << "name: " << this->getName() << std::endl;
	std::cout << "avgScore: " << std::fixed << std::setprecision(3) << this->avgScore << std::endl;
	std::cout << "budgetPlace: " << ((this->contractPlace) ? "True" : "False") << std::endl;
	std::cout << std::endl;
}

// ---------------------- Table ---------------------- 

Table::Table()
{
	this->budgetAmount = 0;
	this->scolarshipAmount = 0;
	this->scolarshipRatio = 0.4;
	this->minScolarshipScore = 100;
}


void Table::sortStudents()
{
	for (int i = 0; i < this->budgetAmount - 1; ++i)
	{
		int j = i + 1;

		while (j > 0 && (this->scolarshipStudents[j]->getAvgScore()) > (this->scolarshipStudents[j - 1]->getAvgScore()))
		{
			Student* temp = this->scolarshipStudents[j - 1];
			this->scolarshipStudents[j - 1] = this->scolarshipStudents[j];
			this->scolarshipStudents[j] = temp;
			--j;
		}
	}
}

void Table::calculateMinScolarshipScore()
{
	this->minScolarshipScore = this->scolarshipStudents[this->scolarshipAmount - 1]->getAvgScore();
}

double Table::getMinScolarshipScore()
{
	return this->minScolarshipScore;
}

void Table::calculateBudgetAmount()
{
	this->budgetAmount = this->scolarshipStudents.size();
}

void Table::fillBudgetStudents(parseData& data)
{
	for (int i = 0; i < data.getTotalLine(); ++i)
	{
		if (data.students[i]->getContractPlace() == false)
		{
			this->scolarshipStudents.push_back(new Student(
				data.students[i]->getName(),
				data.students[i]->getAvgScore(),
				data.students[i]->getContractPlace()
			));

			/*
			int index = scolarshipStudents.size() - 1;

			this->scolarshipStudents[index]->setName(data.students[i]->getName());
			this->scolarshipStudents[index]->setAvgScore(data.students[i]->getAvgScore());
			this->scolarshipStudents[index]->setContractPlace(data.students[i]->getContractPlace());
			*/
		}
	}
}

void Table::calculateScolarshipAmount()
{
	this->scolarshipAmount = this->budgetAmount * this->scolarshipRatio;
}


void Table::printStudents()
{
	for (int i = 0; i < int(this->budgetAmount); ++i)
		this->scolarshipStudents[i]->printStudent();
}

void Table::outputDataIntoFile()
{
	std::ofstream output;
	output.open("rating.csv");

	assert(output.is_open());

	for (int i = 0; i < this->scolarshipAmount; ++i)
	{
		output << scolarshipStudents[i]->getName() << "," << scolarshipStudents[i]->getAvgScore();

		if (i < this->scolarshipAmount - 1)
			output << std::endl;;
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

parseData::parseData()
{
	this->lineCount = 0;;
	this->totalLine = 0;
}

parseData::parseData(std::string dirName) : inputData(dirName)
{
	this->lineCount = 0;
	this->totalLine = 0;
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

int parseData::getTotalLine()
{
	return this->totalLine;
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
	students[index - 1]->setContractPlace(word == "TRUE");
}

