# Matrix Library
## Table of Contents
1. [Overview](#Overview)
2. [Documentation](#Documentation)
	1. [Initialize](#Init)
	2. [Public Properties](#Properties)
	3. [Public Methods](#Methods)
	4. [Operators](#Operators)  
3. [Build Instructions](#Build)
4. [Testing](#Testing)

<a name="Overview"></a>
## Overview

The Matrix library defines a *Matrix* object with functions, properties, and capabilities.

<a name="Documentation"></a>
## Documentation

<a name="Init"></a>
### *Initialize*
__*Matrix*__ (int n, int m, float* xs)
* int n: integer denoting the Matrix's row count. Raises Exception if &lt;= 0.
* int m: integer denoting the Matrix's column count. Raises Exception if &lt;= 0.
* float* xs: float array containing values to populate Matrix with.Array is expected to have exactly n * m elements.

*Returns*: n x m Matrix object

*example*:

```c++
// create a 2x4 matrix
float values[] = {1, 2, 3, 4, 5, 6, 7, 8};
Matrix A = Matrix(2, 4, values);
```
<a name="Properties"></a>
### *Public Properties*

__*N*__ ()

*Returns*: Number of rows in Matrix

__*M*__ ()

*Returns*: Number of columns in Matrix

<a name="Methods"></a>
### *Public Methods*
__*getValueAt*__ (int n, int m)

Raises exception if n or m are &lt; 0 or are larger than the dimensions of the Matrix.
* int n: row index of the value to return
* int m: column index of the value to return

*Return*: float value from the given indexes

__*setValueAt*__ (int n, int m, float value) Raises exception if n or m are &lt; 0 or are larger than the dimensions of the Matrix.
* int n: row index of the value to set
* int m: column index of the value to set

*Return*: bool true if successful otherwise false

__*transpose*__ ()

*Return*: Matrix * of the transposed matrix

*example*:
```c++
// create a 2x1 matrix and transpose it
float values[] = {1, 2};
/* create a 2x1 matrix
 * A = [1]
 *     [2]
 */
Matrix A = Matrix(2, 1, values);

// *A_transpose = [1, 2]
Matrix * A_transpose = A.transpose();
```

__*toCharArr*__ ()

*Return*: char * of the matrix values. This is used to display the matrix values as a character array.

*example*:

```c++
float values[] = {1, 2, 3, 4};
Matrix A = Matrix(2, 2, values);
printf(A.toCharArr());
```
*outputs*
```
[1, 2]
[3, 4]
```
<a name="Operators"></a>
### *Operators*
__*Multiplication*__ *

Performs matrix multiplication between two matrixes.

This algorithm uses the naive approach with O(n^3) runtime.

Other algorithms that *could have been* used are:
1. Strassens Algorithm O(n^2.807) - Only faster if n &gt; 100 (not applicable for this use case)
2. Coppersmith-Winogrand Algorithm O(n^2.373) - Constant coefficient hidden by Big O is so large that this algorithm is only worthwhile for matrixes too large to handle on present-day computers.

Reference: [Wikipedia - Matrix Multiplication Algorithms](https://en.wikipedia.org/wiki/Matrix_multiplication_algorithm)

*example*
```c++
// create 2 matrixes
float A_values[] = {1, 2, 3, 4};
float B_values[] = {1, 2, 3, 4, 5, 6};
Matrix A = Matrix(2, 2, A_values);
Matrix B = Matrix(2, 3, B_values);

// A * B = C
// C will be 2x3 matrix
Matrix * C = A * B;
```

__*Equality*__ &equals;&equals;

Performs equality check on value, and shape of two matrixes

*example*:

```c++
float values1[] = {1, 2, 3, 4};
float values2[] = {10, 20, 30, 40};
Matrix A = Matrix(2, 2, values1);
Matrix B = Matrix(2, 2, values1);
Matrix C = Matrix(1, 4, values1); // different shape, same values
Matrix D = Matrix(2, 2, values2); // same shape, different values

// prints "true";
printf((A == B) ? "true" : "false");

// prints "false"
printf((A == C) ? "true" : "false");

// prints "false"
printf((A == D) ? "true" : "false");
```

## Build Instructions
### *Requirements*
* g++
* c++11
* makefile

<a name="Build"></a>
### *Build Commands*
__*Matrix Binary Only*__

The matrix binary can be build alone and imported into another project (if desired) with the following command. Note: this will generate a `Matrix.o` file.

`make Matrix`

__*Test Script*__

The test script has a dependency on the Matrix files (.cpp/.h) and as such will build them when needed. Build the test executable with the following command.

`make test`

<a name="Testing"></a>
## Testing
A test script is provided with the solution. See __*Test Script*__ under __*Build Commands*__ for instructions on building the script.

The test script tests the following aspects of the Matrix class:
1. Matrix Multiplication: 4 tests
2. Matrix Transformation: 5 tests

The test script will output &quot; __.__ &quot; for every successful test, and a &quot; __F__ &quot; for every test failure.
