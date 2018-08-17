#pragma once

class Matrix {
private:
	// This is the Matrix (using double pointers)
	float ** Mat = 0;
	int n = 0;
	int m = 0;

	bool withinBounds(int n, int m);

public:
	// constructor
	Matrix(int n, int m, float* xs);

	// distructor (will be using "new" pointers to store matrix)
	~Matrix();

	// Functions to get dimensions of matrix
	int M(); // column
	int N(); // row

	// Functions to get/set values in matrix (given indexes)
	float getValueAt(int n, int m);
	bool setValueAt(int n, int m, float value);

	// Transpose function
	Matrix* transpose();

	// toChar*
	char* toCharArr();
	
	// operator overloading
	Matrix* operator * (Matrix &B);

	bool operator == (Matrix &B);
};
