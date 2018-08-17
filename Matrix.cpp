#include "Matrix.h"
#include <exception>
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>

Matrix::Matrix(int n, int m, float* xs) {
	/* Construct matrix
	 * n = number of rows
	 * m = number of columns
	 * float* xs = values to assign in matrix (assumed to be n * m elements long)
	 */

	// check for valid dims
	if (n <= 0 || m <= 0) {
		throw;
	}

	// set vars
	this->n = n;
	this->m = m;
	this->Mat = new float*[n];

	// build and poplate matrix
	int index = 0;
	for (int i = 0; i < n; ++i) {
		this->Mat[i] = new float[m];

		// insert value
		for (int j = 0; j < m; ++j) {
			this->Mat[i][j] = xs[index];
			index++;
		}
	}
}

Matrix::~Matrix() {
	/* Destructor
	 * Need to "free" all the memory used in the matrix 
	 * Clearing up every element in the "rows" and the row array itself
	 */
	for (int i = 0; i < this->n; ++i) {
		delete[] this->Mat[i];
	}
	delete[] this->Mat;
}

bool Matrix::withinBounds(int n, int m) {
	/* Helper function to varify the n & m are within the dims of the matrix
	 * get used in multiple interal functions
	 */
	return !(n >= this->n || m >= this->m || n < 0 || m < 0);
}

float Matrix::getValueAt(int n, int m) {		
	/* n = row index
	 * m = column index
	 * returns value at specified location, or errors if input is bad
	 */

	// validate n & m
	if(!withinBounds(n, m)) { throw; }

	// return deep copy of value
	float x = this->Mat[n][m];
	return x;
}

bool Matrix::setValueAt(int n, int m, float value) {
	/* n = row index
	 * m = column index
	 * returns true if success full (always success full because otherwise will throw error)
	 *
	 * sets value at the specifed location
	 */

	// validate n & m
	if (!withinBounds(n, m)) { throw; }

	// set the value
	this->Mat[n][m] = value;
	return true;
}

int Matrix::M() {
	/* returns  deep copy of the M value */
	int m = this->m;
	return m;
}

int Matrix::N() {
	/* returns a deep copy of the N value */
	int n = this->n;
	return n;
}

Matrix* Matrix::transpose(){
	/* Trasposes the matrix */

	// Make zero'ed out matrix
	float values[this->N() * this->M()] = {};
	Matrix * C = new Matrix(this->M(), this->N(), values);
	
	float value = 0;
	for(int i = 0; i < this->N(); ++i){
		for(int j = 0; j < this->M(); ++j){
			value = this->getValueAt(i, j);
			C->setValueAt(j, i, value);
		}
	}

	return C;
}

// toChar*
char* Matrix::toCharArr(){
	std::ostringstream oss;

	for(int i = 0; i < this->N(); ++i){
		oss << "[";

		// fill values
		for(int j = 0; j < this->M(); ++j){
			oss << this->Mat[i][j];

			if(j < this->M() - 1){
				oss << ", ";
			}
		}
		
		// add closing bracket
		if(i == this->N() - 1) {
			oss << "]";
		}
		else {
			oss << "]" << std::endl;
		}
	}

	// convert to char*
	std::string s = oss.str();
	int n = s.length();
	char * output = new char[n + 1]();
	std::strcpy(output, s.c_str());
	
	return output;
}

Matrix* Matrix::operator * (Matrix &B) {
	/* Overloads the mulitplication operator (*) */

	// validate that the dims allow for multiplication
	if (this->M() != B.N()) {
		throw;
	}

	// create empty matrix
	float zeros[] = {}; 
	Matrix* C = new Matrix(this->N(), B.M(), zeros);

	// declare values that will be used in loop
	float value, a, b;

	/* Perform matrix mutliplication
	 * 
	 * Uses Naive approach with O(n^3) runtime.
	 * Other algorithms that could be used are:
	 *   1. Strassen's Algorithm O(n^2.807) - Only faster if n > 100 (not applicable for this use case)
	 *   2. Coppersmith-Winogrand Algorithm O(n^2.373) - Constant coefficient hidden by Big O is so large that
	 *      this algorithm is only worthwhile for matrixes too large to handle on present-day computers.
	 * Reference:
	 * 	 https://en.wikipedia.org/wiki/Matrix_multiplication_algorithm
	 */
	for (int i = 0; i < this->N(); ++i) {
		for (int j = 0; j < B.M(); ++j) {
			value = 0;
			for (int k = 0; k < B.N(); ++k) {
				a = this->getValueAt(i, k);
				b = B.getValueAt(k, j);
				value += (a * b);
			}
			C->setValueAt(i, j, value);
		}
	}

	return C;
}

bool Matrix::operator == (Matrix &B) {
	/* Operator overload for equality */

	bool is_equal = true;
	// check dim equaity first
	if(B.N() != this->N() || B.M() != this->M()){
		is_equal = false;
	} 
	// check each value's equlity and break early if not-equal found
	else {
		int a, b;

		for(int i = 0; i < this->N(); ++i){
			for(int j = 0; j < this->M(); ++j){
				a = this->getValueAt(i, j);
				b = B.getValueAt(i, j);
 				if(a != b){
					is_equal = false;
					break;
				}		
			}
			if(!is_equal){
				break;
			}
		}
	}

  return is_equal;
}
