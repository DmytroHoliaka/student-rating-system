#include "header.h"

bool isConvertibleToNumber(std::string& word)
{
	try {
		std::stoi(word);
		return true;
	}
	catch (const std::exception&) {
		return false;
	}
}

std::ostream& operator<<(std::ostream& output, std::vector<Student*>& students)
{
	for (int i = 0; i < students.size(); ++i)
	{
		output << students[i] << std::endl;
	}

	return output;
}


std::ostream& operator<<(std::ostream& output, std::vector<std::string>& files)
{
	std::string spacer = "------------------------";

	std::cout << spacer << std::endl;
	for (const auto& file : files)
		output << file << std::endl;
	output << spacer << std::endl;
	return output;
}

std::ostream& operator<<(std::ostream& output, Student* student)
{
	output << student->getName() << "," << student->getAvgScore();

	return output;
}

std::ostream& operator<<(std::ostream& output, Table& table)
{
	for (int i = 0; i < table.scolarshipAmount; ++i)
	{
		output << table.scolarshipStudents[i];

		if (i < table.scolarshipAmount - 1)
			output << std::endl;;
	}
	return output;
}

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

double Table::calculateMinScolarshipScore()
{
	this->minScolarshipScore = this->scolarshipStudents[this->scolarshipAmount - 1]->getAvgScore();
	return this->minScolarshipScore;
}


double Table::getMinScolarshipScore()
{
	return this->minScolarshipScore;
}

std::vector<Student*>& Table::getScolarshipStudents()
{
	return this->scolarshipStudents;
}

int Table::calculateBudgetAmount()
{
	int size = this->scolarshipStudents.size();
	if (size == 0)
		throw std::range_error("There are no scholarship students");
	this->budgetAmount = size;
	return size;
}

void Table::fillBudgetStudents(parseData& data, std::vector<Student*> students)
{
	for (int i = 0; i < data.getTotalLine(); ++i)
	{
		if (students[i]->getContractPlace() == false)
		{
			this->scolarshipStudents.push_back(new Student(
				students[i]->getName(),
				students[i]->getAvgScore(),
				students[i]->getContractPlace()
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

int Table::calculateScolarshipAmount()
{
	this->scolarshipAmount = std::ceil(this->budgetAmount * this->scolarshipRatio);
	return this->scolarshipAmount;
}

// ---------------------- inputData ---------------------- 


inputData::inputData(std::string dirName)
{
	if (std::filesystem::exists(dirName) && std::filesystem::is_directory(dirName)) {
		this->directory = dirName;
	}
	else if (std::filesystem::exists(dirName) && !std::filesystem::is_directory(dirName)) {
		throw std::range_error("Such a directory doesn't exist");
	}
	else if (!std::filesystem::exists(dirName))
	{
		throw std::range_error("There is no such name.");
	}
	else
	{
		throw std::range_error("Error. Change directory name.");
	}
}

std::vector<std::string>& inputData::getFiles()
{
	return this->files;
}

std::string inputData::getDirectory()
{
	return this->directory;
}

void inputData::setDirectory(std::string dirName)
{
	this->directory = dirName;
}


void inputData::processFilesFromDirectory()
{
	for (const auto& file : std::filesystem::directory_iterator(this->directory))
	{
		if (std::filesystem::is_regular_file(file)) {
			files.push_back(file.path().string());
		}
	}

	if (this->files.size() == 0)
		throw std::range_error("Directory is empty.");
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

void parseData::checkTotalLine()
{
	if (this->totalLine == 0)
	{
		throw std::runtime_error("There is no record");
	}
}

//void parseData::removeRecord()
//{
//	this->totalLine -= 1;
//	this->students.pop_back();
//	return;
//}

int parseData::getTotalLine()
{
	return this->totalLine;
}

std::vector<Student*> parseData::getStudents()
{
	std::vector<Student*> students;
	for (int i = 0; i < files.size(); ++i)
	{
		this->fileName = files[i];

		std::ifstream input;
		input.open(this->fileName);

		assert(input.is_open());  // Така собі ідея, близько до широфринії

		input >> this->lineCount;
		input.get();

		if (this->lineCount == 0)
			continue;

		this->totalLine += this->lineCount;

		for (int j = 0; j < this->lineCount; ++j)
		{
			parseLineOfStudent(input, students);
		}

		input.close();
	}

	return students;
}

void parseData::parseLineOfStudent(std::istream& input, std::vector<Student*>& students)
{
	students.push_back(new Student());
	int index = students.size();

	int sum = 0;
	std::string line;

	std::getline(input, line);

	if (line.empty())
	{
		this->totalLine -= 1;
		students.pop_back();
		return;
	}

	std::istringstream is(line);

	std::string word;
	std::getline(is, word, ',');

	if (word.empty() || isConvertibleToNumber(word))
	{
		this->totalLine -= 1;
		students.pop_back();
		return;
	}

	students[index - 1]->setName(word);

	int count = 0;
	while (std::getline(is, word, ',') && word != "TRUE" && word != "FALSE" && isConvertibleToNumber(word))
	{
		//std::cout << word << " ";
		sum += std::stoi(word);
		++count;
	}

	if (count == 0)
	{
		this->totalLine -= 1;
		students.pop_back();
		return;
	}
	students[index - 1]->setAvgScore(sum / (double)count);

	if (word != "TRUE" && word != "FALSE")
	{
		this->totalLine -= 1;
		students.pop_back();
		return;
	}
	students[index - 1]->setContractPlace(word == "TRUE");
}

