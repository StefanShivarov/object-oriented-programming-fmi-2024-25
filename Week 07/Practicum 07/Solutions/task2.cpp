#include <iostream>
#include <cstring>

class Matrix
{
private:

	int** matrix = nullptr;
	int rows = 0;
	int cols = 0;

	void free() {
		for (int i = 0; i < rows; i++){
			delete[] matrix[i];
			matrix[i] = nullptr;
		}
		delete[] matrix;
		matrix = nullptr;
		rows = 0;
		cols = 0;
	}

	void copyFrom(const Matrix& other) {
		rows = other.rows;
		cols = other.cols;
		this->matrix = new int* [other.rows];
		for (int i = 0; i < other.rows; i++){
			this->matrix[i] = new int[other.cols];
			for (int j = 0; j < other.cols; j++){
				matrix[i][j] = other.matrix[i][j];
			}
		}
	}

public:
	Matrix(){

		rows = 4;
		cols = 4;
		matrix = new int* [rows];
		for (int i = 0; i < rows; i++)	{
			matrix[i] = new int[cols] {0};
		}
	}
	Matrix(int** matrix, int rows, int cols) 	{

		this->matrix = new int* [rows];
		for (int i = 0; i < rows; i++){
			this->matrix[i] = new int[cols];
		}

		this->rows = rows;
		this->cols = cols;
		for (int i = 0; i < rows; i++){
			for (int j = 0; j < cols; j++){
				this->matrix[i][j] = matrix[i][j];
			}

		}

	}
	Matrix(const Matrix& other) {
		copyFrom(other);
	}

	Matrix& operator = (const Matrix& other) {
		if (this != &other) 
		{
			free();
			copyFrom(other);
		}
		return *this;
	}

	~Matrix() {
		free();
	}

	Matrix& operator += (const Matrix& other) {

		if (rows != other.rows || cols != other.cols) throw std::logic_error("Error");
		for (int i = 0; i < rows; i++){
			for (int j = 0; j < cols; j++){
				matrix[i][j] += other.matrix[i][j];
			}

		}
		return *this;

	}
	
	Matrix& operator -= (const Matrix& other){

		if (rows != other.rows || cols != other.cols) throw std::logic_error("Error");

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++){
				matrix[i][j] -= other.matrix[i][j];
			}

		}
		return *this;

	}

	Matrix& operator *= (const Matrix& other) {
		if (cols != other.rows) throw std::logic_error("Error");

		int newRows = rows;
		int newCols = other.cols;
		int** newMatrix = new int* [newRows];

		for (int i = 0; i < newRows; i++){
			newMatrix[i] = new int[newCols] {0};
		}
		for (int i = 0; i < rows; i++){
			for (int j = 0; j < other.cols; j++){
				for (int k = 0; k < cols; k++){
					newMatrix[i][j] += matrix[i][k] * other.matrix[k][j];
				}
			}
		}
		Matrix result(newMatrix, newRows, newCols);
		*this = result;
		for (int i = 0; i < newRows; i++){
			delete[] newMatrix[i];
			newMatrix[i] = nullptr;
		}
		delete[] newMatrix;
		newMatrix = nullptr;

		return *this;
	}

	int getRows() const {
		return rows;
	}

	int getCols() const{
		return cols;
	}
	friend std::ostream& operator << (std::ostream& os, const Matrix& matrix) 
	{

		os << matrix.rows << " " << matrix.cols << std::endl;
		for (int i = 0; i < matrix.rows; i++){

			for (int j = 0; j < matrix.cols; j++){
				os << matrix.matrix[i][j] << " ";

			}
			os << std::endl;
		}
		return os;
	}
	friend std::istream& operator >> (std::istream& is, Matrix& matrix) {
		int newRows = 0;
		int newCols = 0;

		is >> newRows;
		is >> newCols;
		is.ignore(1);

		int** newMatrix = new int* [newRows];
		for (int i = 0; i < newRows; i++){
			newMatrix[i] = new int[newCols] {0};
		}
		for (int i = 0; i < newRows; i++){
			for (int j = 0; j < newCols; j++){
				is >> newMatrix[i][j];
			}
			is.ignore(1);
		}

		Matrix result(newMatrix, newRows, newCols);
		matrix = result;
		for (int i = 0; i < newRows; i++){
			delete[] newMatrix[i];
			newMatrix[i] = nullptr;

		}
		delete[] newMatrix;
		newMatrix = nullptr;
		return is;

	}

};

Matrix operator * (const Matrix& m1, const Matrix& m2) {
	Matrix result(m1);
	result *= m2;
	return result;

}

Matrix operator + (const Matrix& m1, const Matrix& m2){
	Matrix result(m1);
	result += m2;
	return result;
}

Matrix operator - (const Matrix& m1, const Matrix& m2){
	Matrix result(m1);
	result -= m2;
	return result;
}

int main(){

	Matrix matrix1;
	Matrix matrix2;
	std::cin >> matrix1;
	std::cout << std::endl;
	std::cin >> matrix2;
	
	if (matrix1.getRows() == matrix2.getRows() && matrix1.getCols() == matrix2.getCols()) {

		Matrix addRes = matrix1 + matrix2;
		Matrix subRes = matrix1 - matrix2;

		std::cout << std::endl << addRes << std::endl << subRes;

	}
	try{
		Matrix multRes = matrix1 * matrix2;
		std::cout << std::endl << multRes;
	}
	catch (const std::logic_error& e){
		std::cout << ";D" << std::endl;
	}
	return 0;

}

