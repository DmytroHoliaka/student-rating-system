#include "header.h"

void checkTotalLine(ParseData& data)
{
	if (data.totalLine == 0)
	{
		throw std::domain_error("There are no files with correct records");
	}
}

bool isConvertibleToNumber(std::string& word)
{
	for (int i = 0; i < word.size(); ++i)
	{
		if (!std::isdigit(word[i]))
			return false;
	}
	return true;
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

std::ostream& operator<<(std::ostream& output, Validator& validator)
{
	std::string space = "--------------------------------------";
	std::cout << space << "  Errors  " << space << std::endl;
	if (validator.getErrors().size() == 0) {
		output << "All data is processed correctly";
	}
	else {
		for (int i = 0; i < validator.getErrors().size(); ++i)
		{
			output << "File: " << validator.getErrors()[i]->getFileName() << "\t|\t";
			output << "Line: #" << validator.getErrors()[i]->getLineIndex() << "\t| ";
			output << "Column: " << validator.getErrors()[i]->getColumnName() << std::endl;
		}
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

// ---------------------- Student ---------------------- 
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

Table::Table(ParseData& data, std::vector<Student*> students)
{
	this->budgetAmount = 0;
	this->scolarshipAmount = 0;
	this->scolarshipRatio = 0.4;
	this->minScolarshipScore = 100;

	this->fillBudgetStudents(data, students);
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

void Table::fillBudgetStudents(ParseData& data, std::vector<Student*> students)
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
		}
	}
}

int Table::calculateScolarshipAmount()
{
	this->scolarshipAmount = std::ceil(this->budgetAmount * this->scolarshipRatio);
	return this->scolarshipAmount;
}

// ---------------------- inputData ---------------------- 


InputData::InputData(std::string dirName)
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

std::vector<std::string>& InputData::getFiles()
{
	return this->files;
}

std::string InputData::getDirectory()
{
	return this->directory;
}

void InputData::setDirectory(std::string dirName)
{
	this->directory = dirName;
}


void InputData::processFilesFromDirectory()
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
ParseData::ParseData()
{
	this->lineCount = 0;
	this->errorsCount = 0;
	this->totalLine = 0;
}

ParseData::ParseData(std::string dirName) : InputData(dirName)
{
	this->lineCount = 0;
	this->errorsCount = 0;
	this->totalLine = 0;
}

int ParseData::getTotalLine()
{
	return this->totalLine;
}

std::vector<Student*> ParseData::getStudents(Validator& validator)
{
	std::vector<Student*> students;
	for (int i = 0; i < files.size(); ++i)
	{
		this->fileName = files[i];

		std::ifstream input;
		input.open(this->fileName);

		if (!input.is_open())
		{
			std::cerr << "Can't open " << fileName << "for reading" << std::endl;
			exit(2);
		}

		validator.setCurrentFile(this->fileName);
		
		input >> this->lineCount;
		input.get();

		if (this->lineCount == 0)
			continue;


		std::string line;
		int beforeErrorsAmount = validator.getErrors().size();
		for (int j = 0; j < this->lineCount; ++j)
		{
			std::getline(input, line);

			validator.setCurrentLine(j + 2);
			validator.validate(line);
		}
		int afterErrorsAmount = validator.getErrors().size();
		input.seekg(0, std::ios::beg);

		if (beforeErrorsAmount == afterErrorsAmount) {
			input >> this->lineCount;
			input.get();

			for (int j = 0; j < this->lineCount; ++j) 
			{
				std::getline(input, line);
				parseLineOfStudent(line, students);
			}

			input.close();
		}
		else {
			this->lineCount = 0;
		}

		this->totalLine += this->lineCount;

	}

	return students;
}

// ----------------------------- Validator ----------------------------- 

void Validator::validate(std::string line)
{
	if (line.empty())
	{
		this->errors.push_back(new ParseError(this->currentFile, this->currentLine, "Name, points and contract status"));
		return;
	}

	std::istringstream is(line);

	std::string word;
	std::getline(is, word, ',');

	if (word.empty() || isConvertibleToNumber(word))
	{
		this->errors.push_back(new ParseError(this->currentFile, this->currentLine, "Name"));
		return;
	}

	int count = 0;
	int sum = 0;
	while (std::getline(is, word, ',') && word != "TRUE" && word != "FALSE" && isConvertibleToNumber(word))
	{
		++count;
	}

	if (count == 0)
	{
		this->errors.push_back(new ParseError(this->currentFile, this->currentLine, "Points"));
		return;
	}

	if (word != "TRUE" && word != "FALSE")
	{
		this->errors.push_back(new ParseError(this->currentFile, this->currentLine, "Contract status"));
		return;
	}
}

std::vector<ParseError*>& Validator::getErrors()
{
	return this->errors;
}

std::string Validator::getCurrentFile()
{
	return this->currentFile;
}

void Validator::setCurrentFile(std::string fileName)
{
	this->currentFile = fileName;
}

int Validator::getCurrentLine()
{
	return this->currentLine;
}

void Validator::setCurrentLine(int val)
{
	this->currentLine = val;
}


// ------------------------------ ParseError ------------------------------
ParseError::ParseError(std::string fileName, int lineIndex, std::string columnName)
{
	this->fileName = fileName;
	this->lineIndex = lineIndex;
	this->columnName = columnName;
}

std::string ParseError::getFileName()
{
	return this->fileName;
}

void ParseError::setFileName(std::string val)
{
	this->fileName = val;
}


int ParseError::getLineIndex()
{
	return this->lineIndex;
}

void ParseError::setlineIndex(int val)
{
	this->lineIndex = val;
}


std::string ParseError::getColumnName()
{
	return this->columnName;
}

void ParseError::setColumnName(std::string val)
{
	this->columnName = val;
}


//Dictionary
// file -> line (row (col1, col2,col3))
// ParseError Validator (string row|string col) 
// Validators for each logic rule (chain of resp)
// Show erors in files 
// Convert to classes 


void ParseData::parseLineOfStudent(std::string line, std::vector<Student*>& students)
{
	students.push_back(new Student());
	int index = students.size();

	int sum = 0;


	std::istringstream is(line);

	std::string word;
	std::getline(is, word, ',');

	students[index - 1]->setName(word);

	int count = 0;
	while (std::getline(is, word, ',') && word != "TRUE" && word != "FALSE" && isConvertibleToNumber(word))
	{
		//std::cout << word << " ";
		sum += std::stoi(word);
		++count;
	}

	students[index - 1]->setAvgScore(sum / (double)count);
	students[index - 1]->setContractPlace(word == "TRUE");
}

