#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <cassert>
#include <iomanip>

class inputData;
class parseData;

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

	void sortStudents();
	void calculateMinScolarshipScore();
	double getMinScolarshipScore();

	void fillScolarshipStudents(parseData&);
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
	std::vector<Student*> students;
	void parseStudentInfo(std::istream&);

public:
	parseData();
	parseData(std::string);

	int getTotalLine();
	void getStudentsInfo();
	void printStudents();
};
