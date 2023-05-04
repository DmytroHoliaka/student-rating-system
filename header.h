#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <cassert>
#include <iomanip>



class Person
{
private: // private
	std::string name;

public:
	std::string getName();
	void setName(std::string);
};


class Student : public Person
{
private:
	double avgScore;
	bool budgetPlace;

public:
	double getAvgScore();
	void setAvgScore(double);

	bool getBudgetPlace();
	void setBudgetPlace(bool);

	void printStudent();
};

class Table
{
private:
	int budgetAmount;
	int scolarshipAmount;
	double scolarshipRatio = 0.4;
	int minScolarshipScore;

public:
	void calculateBudgetAmount();
	void sortStudents();
	void calculateScolarshipAmount();
	void calculateMinScolarshipScore();
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
private:
	std::string fileName;
	int lineCount;
	int totalLine;
	std::vector<Student*> students;
	void parseStudentInfo(std::istream&);

public:
	parseData() = default;
	parseData(std::string);

	void getStudentsInfo();
};
