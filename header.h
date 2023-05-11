#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <cassert>
#include <iomanip>
#include <stdexcept>

class InputData;
class ParseData;
class Person;
class Student;
class Table;
class ParseError;
class Validator;

std::ostream& operator<<(std::ostream&, std::vector<Student*>&);
std::ostream& operator<<(std::ostream&, std::vector<std::string>&);
std::ostream& operator<<(std::ostream&, Validator&);
std::ostream& operator<<(std::ostream&, Student*);
std::ostream& operator<<(std::ostream&, Table&);
void checkTotalLine(ParseData&);

class Person
{
private:
	std::string name;

public:
	Person() = default;
	Person(std::string);

	std::string getName();
	void setName(std::string);
};


class Student : public Person
{
private:
	double avgScore;
	bool contractPlace;

public:
	Student();
	Student(std::string, double, bool);

	double getAvgScore();
	void setAvgScore(double);

	bool getContractPlace();
	void setContractPlace(bool);
};

class Table
{
	friend std::ostream& operator<<(std::ostream&, Table&);
private:
	int budgetAmount;
	int scolarshipAmount;
	double scolarshipRatio;
	double minScolarshipScore;
	std::vector<Student*> scolarshipStudents;

public:
	Table();
	Table(ParseData&, std::vector<Student*>);

	void sortStudents();

	double getMinScolarshipScore();
	std::vector<Student*>& getScolarshipStudents();

	double calculateMinScolarshipScore();
	int calculateBudgetAmount();
	int calculateScolarshipAmount();

	void fillBudgetStudents(ParseData&, std::vector<Student*>);
};


class InputData
{
protected:
	std::vector<std::string> files;
	std::string directory;

public:
	InputData() = default;
	InputData(std::string dirName);

	std::vector<std::string>& getFiles();
	std::string getDirectory();
	void setDirectory(std::string);

	void processFilesFromDirectory();
};

class Validator
{
private:
	int currentLine;
	std::string currentFile;
	std::vector<ParseError*> errors;

public:
	std::vector<ParseError*>& getErrors();

	int getCurrentLine();
	void setCurrentLine(int);

	std::string getCurrentFile();
	void setCurrentFile(std::string);

	void validate(std::string);
};

class ParseError {
private:
	std::string fileName;
	int lineIndex;
	std::string columnName;

public:
	ParseError(std::string, int, std::string);

	std::string getFileName();
	void setFileName(std::string);

	int getLineIndex();
	void setlineIndex(int);

	std::string getColumnName();
	void setColumnName(std::string);
};

class ParseData : public InputData
{
	friend class Table;
	friend void checkTotalLine(ParseData&);


private:
	int lineCount;
	int errorsCount;
	int totalLine;
	std::string fileName;
	void parseLineOfStudent(std::string, std::vector<Student*>&);
	void removeRecord();	 // Дороби метод, зараз він не працює

public:
	ParseData();
	ParseData(std::string);

	int getTotalLine();
	std::vector<Student*> getStudents(Validator&);
};
