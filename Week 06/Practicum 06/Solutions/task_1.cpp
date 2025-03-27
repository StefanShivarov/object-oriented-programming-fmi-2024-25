#include <iostream>
#include <cstring>
#include <cmath>
//TRQBVA DA SE NAPRAVI S RAZDELNA!!!!!
class GradeReport 
{
private:

	char* nameOfReport = nullptr;
	double* grades = nullptr;
	int countOfGrades = 0;

	void copyFrom(const GradeReport& other) {

		nameOfReport = new char[strlen(other.nameOfReport) + 1];
		strncpy(nameOfReport, other.nameOfReport, strlen(other.nameOfReport));
		nameOfReport[strlen(other.nameOfReport)] = '\0';

		grades = new double[other.countOfGrades];
		countOfGrades = other.countOfGrades;
		for (int i = 0; i < countOfGrades; i++){
			grades[i] = other.grades[i];
		}

	}

	void free() {
		delete[] nameOfReport;
		delete[] grades;
		nameOfReport = nullptr;
		grades = nullptr;
		countOfGrades = 0;
	}

public:

	GradeReport() = default;

	GradeReport(const char* nameOfReport, const double* grades, int countOfGrades) {

		this->nameOfReport = new char[strlen(nameOfReport) + 1];
		strncpy(this->nameOfReport, nameOfReport, strlen(nameOfReport));
		this->nameOfReport[strlen(nameOfReport)] = '\0';

		this->grades = new double[countOfGrades];
		this->countOfGrades =countOfGrades;

		for (int i = 0; i < countOfGrades; i++){
			this->grades[i] = grades[i];
		}

	}

	GradeReport(const GradeReport& other) {
		copyFrom(other);

	}

	GradeReport& operator = (const GradeReport& other) {
		if (this != &other) 
		{
			free();
			copyFrom(other);
		}
		return *this;

	}

	~GradeReport() {
		free();
	}

	int getCountOfGrades() const {
		return countOfGrades;

	}
	
	const char* getReportName() const {
		return nameOfReport;

	}

};

int main()
{

	double* grades = new double[3] {6.00, 4.60, 3.20};

	GradeReport gr("Random text", grades, 3);
	std::cout << gr.getCountOfGrades() << " " << gr.getReportName() << std::endl;

	delete[] grades;

	return 0;

}
