#include <iostream>
#include <numeric>
#include <vector>
#include <functional>
#include "Matrix.h"

using namespace std;

bool matmul(int n1, int m1, vector<float> xs1, int n2, int m2, vector<float> xs2, int n3, int m3, vector<float> xs3){
	/* test's marix multiplication
	 *
	 * n1, m1 : row,column dimentions of matrix "A" respectively
	 * xs1    : values for matrix "A"
	 * n2, m2 : row,column dimentions of matrix "B" respectively
	 * xs2    : values for matrix "B"
	 * n3, m3 : row,column dimentions of matrix "C_true" respectively
	 * xs3    : values for matrix "C_true"
	 *
	 * returns: true if resulting "C" matrix is equal to C_true
	 */

	// create matrixes
	Matrix A = Matrix(n1, m1, &xs1[0]);
	Matrix B = Matrix(n2, m2, &xs2[0]);
	Matrix C_true = Matrix(n3, m3, &xs3[0]);
		
	// multipl A and B
	Matrix * C = A * B;

	// compare and return result
	bool pass = *C == C_true;
	delete C;
	return pass;
}

bool mattransform(int n1, int m1, vector<float> xs1, int n2, int m2, vector<float> xs2){
	/* test's matrix transformation
	 * 
	 * n1, m1 : row, column dimensions of matrix "A" respectively
	 * xs1    : values for matrix "A"
	 * n2, m2 : row, column dimensions of ground truth matrix "C_true"
	 *
	 * returns: true if resulting "A_transpose" matrix is equal to "C_true" 
	 */

	// create matrixes
	Matrix A = Matrix(n1, m1, &xs1[0]);
	Matrix C_true = Matrix(n2, m2, &xs2[0]);

	Matrix* A_transpose = A.transpose();
	
	// compare and return result
	bool pass = *A_transpose == C_true;
	delete A_transpose;
	return pass;
}

vector<bool> run_matmul_testbench() {
	/* Test format
	 * All tests below validate the equation
	 *   A * B = C
	 * where A is an NxM matrix, B is an MxP matrix, and C is an NxP Matrix
	 *
	 * Passes are denoted with "pass"
	 * Fails are denoted with "fail"
	 */

	// declare variables
	vector<float> as, bs, cs;
	vector<bool> results;
	bool pass = false;



	/* Test basic 1x1 * 1x1 matrix mul
	 *
	 * A = [10]
	 *
	 * B = [7]
	 *
	 * C = [70]
	 */
	as = {10};
	bs = {7};
	cs = {70};

	pass = matmul(1, 1, as, 1, 1, bs, 1, 1, cs);
	results.push_back(pass);



	/* Test basic square matrix
	 * 
	 * A = [1, 2]
	 *     [3, 4]
	 *
	 * B = [1, 2]
	 *     [3, 4]	
	 *
	 * C = [7, 10]
	 *     [15, 22]
	 */
	as = {1, 2, 3, 4};
	bs = {1, 2, 3, 4};
	cs = {7, 10, 15, 22};

	pass = matmul(2, 2, as, 2, 2, bs, 2, 2, cs);
	results.push_back(pass);



	/* Test with floats & negatives and mismatched input size
	 * 
	 * A = [1.1, 2.3]
	 *     [-3.1, -4.4]
	 *     [4.001, 0]
	 *
	 * B = [1.3, 40.2, 22.3]
	 *     [-300, 0.0004, 17.17]
	 *
	 * C = [-688.57, 44.22092, 64.021]
	 *     [1315.97, -124.62176, -144.678]
	 *         [5.2013, 160.8402, 89.2223]
	 */
	as = {1.1, 2.3, -3.1, -4.4, 4.001, 0};
	bs = {1.3, 40.2, 22.3, -300, 0.0004, 17.17};
	cs = {-688.57, 44.22092, 64.021, 1315.97, -124.62176, -144.678, 5.2013, 160.8402, 89.2223};

	pass = matmul(3, 2, as, 2, 3, bs, 3, 3, cs);
	results.push_back(pass);



	/* Test with floats and mismatched input/output sizes 
	 * 
	 * A = [1.4]
	 *     [3.5]
	 *
	 * B = [1.1, 2.2, 3.3, 4.4]	
	 *
	 * C = [ 1.54,  3.08,  4.62,  6.16],
	 *     [ 3.85,  7.7 , 11.55, 15.4 ]
	 */

	as = {1.4, 3.5};
	bs = {1.1, 2.2, 3.3, 4.4};
	cs = {1.54,  3.08,  4.62,  6.16, 3.85,  7.7, 11.55, 15.4};

	pass = matmul(2, 1, as, 1, 4, bs, 2, 4, cs);
	results.push_back(pass);

	return results;
}

vector<bool> run_mattransform_testbench() {
	/* Test format
	 * All tests below validate the equation
	 *   A * B = C
	 * where A is an NxM matrix, B is an MxP matrix, and C is an NxP Matrix
	 *
	 * Passes are denoted with "pass"
	 * Fails are denoted with "fail"
	 */

	// declare variables
	vector<float> as, cs;
	vector<bool> results;
	bool pass = false;



	/* Test basic 1x1 matrix
	 *
	 * A = [10]
	 *
	 * C = [10]
	 */
	as = {10};
	cs = {10};

	pass = mattransform(1, 1, as, 1, 1, cs);
	results.push_back(pass);

	/* Test basic 2x2 (square) matrix
	 *
	 * A = [1, 2]
	 *     [3, 4]	
	 *
	 * C = [1, 3]
	 *     [2, 4]
	 */

	as = {1, 2, 3, 4};
	cs = {1, 3, 2, 4};
	pass = mattransform(2, 2, as, 2, 2, cs);
	results.push_back(pass);

	/* Test large square matrix (10x10)
	 *
	 * A = [0 , 1 , ...        ]
	 *     [10, 11,            ]
	 *     [.      .         . ]
	 *     [.        .       . ]
	 *     [.          .     . ]
	 *     [            ,87, 88]
	 *     [        ... ,98, 99]
	 * 
	 * C = [0 , 10, ...        ]
	 *     [1 , 11,            ]
	 *     [.      .         . ]
	 *     [.        .       . ]
	 *     [.          .     . ]
	 *     [            ,87, 98]
	 *     [        ... ,89, 99]
	 */

	as = {};
	for(int i = 0; i < 100; ++i){
		as.push_back(i);
	}
	cs = {
		0, 10, 20, 30, 40, 50, 60, 70, 80, 90,  1, 11, 21, 31, 41, 51, 61, 
		71, 81, 91,  2, 12, 22, 32, 42, 52, 62, 72, 82, 92,  3, 13, 23, 33,
		43, 53, 63, 73, 83, 93,  4, 14, 24, 34, 44, 54, 64, 74, 84, 94,  5,
		15, 25, 35, 45, 55, 65, 75, 85, 95,  6, 16, 26, 36, 46, 56, 66, 76,
		86, 96,  7, 17, 27, 37, 47, 57, 67, 77, 87, 97,  8, 18, 28, 38, 48,
		58, 68, 78, 88, 98,  9, 19, 29, 39, 49, 59, 69, 79, 89, 99
	};

	pass = mattransform(10, 10, as, 10, 10, cs);
	results.push_back(pass);

	/* Test non-square matrix (4x2)
	 * 
 	 * A = [0, 1]
	 *     [2, 3]
	 *     [4, 5]
	 *     [6, 7]
	 *
	 * C = [0, 2, 4, 6]
	 *     [1, 3, 5, 7]
	 */
	as = {0, 1, 2, 3, 4, 5, 6, 7};
	cs = {0, 2, 4, 6, 1, 3, 5, 7};
	pass = mattransform(4, 2, as, 2, 4, cs);
	results.push_back(pass);

	/* Test non-square matrix (2x4)
	 *
	 * Transforming C back to A from previous test
	 */
	pass = mattransform(2, 4, cs, 4, 2, as);
	results.push_back(pass);

	return results;
}

void execute(const vector<function<vector<bool> ()>>& fs) {
	/* execute
	 * fs     : vector of testbench functions to execute
	 * return : void
	 *
	 * Ouput schema: 
	 *   . : Test passed
	 *   F : Test failed (because results were not equivalent to ground truth)
	 */
	vector<bool> results;
	for(auto & f : fs) {		
		results = f();
		for(const bool &is_pass : results) {
			cout << (is_pass ? "." : "F");
		}
	}
	cout << endl;
}

int main() {
	/* Main test function
	 * 	
	 * "testbench" functions: 
	 *      Performs multiple tests on a specific feature (i.e. multiplication)
	 *      and returns a vector<bool> indicating if each test passed or not. 
	 *
	 * Usage: 
	 *      Add the desired testbench function to the "tests" vector.
	 *
	 * TODO: 
	 *      1. Implement a trinary response for test results (pass, fail, and error). 
	 *         Current implementation does not handle Exceptions. 
	 *      2. Add tests to varify bad arguments are handled correctly 
	 *         (i.e. negative dimensions should throw error)
	 */


	// build vector to store test lambda functions
	vector<function<vector<bool> ()>> tests;

	// load vector with lambda functions to execute
	tests.push_back(run_matmul_testbench);
	tests.push_back(run_mattransform_testbench);
	
	// execute all loaded tests
	execute(tests);
}
