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
class Person;
class Student;
class Table;

std::ostream& operator<<(std::ostream&, std::vector<Student*>&);
std::ostream& operator<<(std::ostream&, std::vector<std::string>&);
std::ostream& operator<<(std::ostream&, Student*);
std::ostream& operator<<(std::ostream&, Table&);


// ToDo: Прибери всі assert під час перевірки відкритості файлу на щось адекватніше - шизофринія 

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
	//friend std::ostream& operator<<(std::ostream&, Student*);

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

	void sortStudents();
	
	double getMinScolarshipScore();
	std::vector<Student*>& getScolarshipStudents();

	double calculateMinScolarshipScore();
	int calculateBudgetAmount();
	int calculateScolarshipAmount();

	void fillBudgetStudents(parseData&, std::vector<Student*>);  // Перероби через конструктор
};


class inputData
{
	//friend std::ostream& operator<<(std::ostream&, std::vector<std::string>);
protected:
	std::vector<std::string> files;
	std::string directory;

public:
	inputData() = default;
	inputData(std::string dirName);

	std::vector<std::string>& getFiles();
	std::string getDirectory();
	void setDirectory(std::string);

	void processFilesFromDirectory();
};


class parseData : public inputData
{
	friend class Table;
	//friend std::ostream& operator<<(std::ostream&, std::vector<Student*>&);

private:
	int lineCount;
	int totalLine;
	std::string fileName;
	void parseLineOfStudent(std::istream&, std::vector<Student*>&);
	void removeRecord();	 // Дороби методо, зараз він не плацює

public:
	parseData();
	parseData(std::string);

	int getTotalLine();
	std::vector<Student*> getStudents();
	void checkTotalLine();  // Кудись перенеси, це не відповідальність парсингу
};
