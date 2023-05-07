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

class inputData;
class parseData;

class Person
{
private:
	std::string name;

public:
	Person() = default;
	Person(std::string);
	~Person()
	{
		std::cout << "From Person destructor" << std::endl;
	}

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
	~Student()
	{
		std::cout << "From Student destructor" << std::endl;
	}


	double getAvgScore();
	void setAvgScore(double);

	bool getContractPlace();
	void setContractPlace(bool);

	void printStudent();
};

class Table
{
private:
	int budgetAmount;
	int scolarshipAmount;
	double scolarshipRatio;
	double minScolarshipScore;
	std::vector<Student*> scolarshipStudents;

public:
	Table();
	~Table()
	{
		std::cout << "From Table destructor" << std::endl;
	}

	void sortStudents();
	double getMinScolarshipScore();
	
	void calculateMinScolarshipScore();
	void calculateBudgetAmount();
	void calculateScolarshipAmount();

	void fillBudgetStudents(parseData&, std::vector<Student*>);
	void printStudents();
	void outputDataIntoFile();
};


class inputData
{
protected:
	std::vector<std::string> files;
	std::string directory;

public:
	inputData() = default;
	inputData(std::string dirName);
	~inputData()
	{
		std::cout << "From inputData destructor" << std::endl;
	}

	std::string getDirectory();
	void setDirectory(std::string);

	void getFilesFromDirectory();
	void showFiles();
};


class parseData : public inputData
{
	friend class Table;
private:
	int lineCount;
	int totalLine;
	std::string fileName;
	void parseStudentInfo(std::istream&, std::vector<Student*>&);
	void removeRecord();

public:
	parseData();
	parseData(std::string);
	~parseData()
	{
		std::cout << "From parseData destructor" << std::endl;
	}

	int getTotalLine();
	std::vector<Student*> getStudentsInfo();
	void printStudents();  // Видалити з цього класу
	void checkTotalLine();
};
