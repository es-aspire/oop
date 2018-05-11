#include "stdafx.h"
#include "InvertMatrix.h"

void InitMatrix(Matrix3x3 &matrix)
{
	for (unsigned int i = 0; i < MATRIX_HEIGHT; ++i)
	{
		for (unsigned int j = 0; j < MATRIX_WIDTH; ++j)
		{
			matrix[i][j] = INIT_MATRIX_NUMBER;
		}
	}
}

bool ReadMatrix(std::istream &input, Matrix3x3 &matrix)
{
	for (unsigned int i = 0; i < MATRIX_HEIGHT; ++i)
	{
		for (unsigned int j = 0; j < MATRIX_WIDTH; ++j)
		{
			if (!(input >> matrix[i][j]))
			{
				return false;
			}
		}
	}
	return true;
}

void PrintMatrix(const Matrix3x3 &matrix)
{
	for (unsigned int i = 0; i < MATRIX_HEIGHT; ++i)
	{
		for (unsigned int j = 0; j < MATRIX_WIDTH; ++j)
		{
			std::cout << std::setprecision(COUNT_SIGNIFICANT_DIGIT) << matrix[i][j];
			if (j != MATRIX_WIDTH - 1)
			{
				std::cout << " ";
			}
		}
		std::cout << "\n";
	}
}

double GetDeterminant3x3(const Matrix3x3 &matrix)
{
	return matrix[0][0] * matrix[1][1] * matrix[2][2] +
		matrix[2][0] * matrix[0][1] * matrix[1][2] +
		matrix[1][0] * matrix[2][1] * matrix[0][2] -
		matrix[2][0] * matrix[1][1] * matrix[0][2] -
		matrix[0][0] * matrix[2][1] * matrix[1][2] -
		matrix[1][0] * matrix[0][1] * matrix[2][2];
}

double GetDeterminant2x2(const Matrix2x2 &matrix2x2)
{
	return matrix2x2[0][0] * matrix2x2[1][1] - matrix2x2[1][0] * matrix2x2[0][1];
}

double GetMinor(const Matrix3x3 &matrix, unsigned int row, unsigned int column)
{
	Matrix2x2 matrix2x2;
	unsigned int minorColumn = 0;
	for (unsigned int i = 0; i < MATRIX_HEIGHT; ++i)
	{
		unsigned int minorRow = i;
		if (i > row)
		{
			minorRow--;
		}
		for (unsigned int j = 0; j < MATRIX_WIDTH; ++j)
		{
			minorColumn = j;
			if (j > column)
			{
				minorColumn--;
			}
			if (i != row && j != column)
			{
				matrix2x2[minorRow][minorColumn] = matrix[i][j];
			}
		}
	}
	return GetDeterminant2x2(matrix2x2);
}

void TransponeMatrix(Matrix3x3 &matrix)
{
	for (unsigned int i = 0; i < MATRIX_HEIGHT; ++i)
	{
		for (unsigned int j = 0; j < i; ++j)
		{
			std::swap(matrix[i][j], matrix[j][i]);
		}
	}
}

bool InvertMatrix(const Matrix3x3 &inputMatrix, Matrix3x3 &invertMatrix)
{
	const double DETERMINANT = GetDeterminant3x3(inputMatrix);

	if (abs(DETERMINANT - NON_EXISTENT_DETERMINANT) < 0.000000000000001)
	{
		std::cout << "The inverse matrix cannot be found because the matrix determinant is zero.\n";
		return false;
	}

	int numberSign = -1;
	for (unsigned int i = 0; i < MATRIX_HEIGHT; ++i)
	{
		for (unsigned int j = 0; j < MATRIX_WIDTH; ++j)
		{
			double minor = GetMinor(inputMatrix, i, j);
			
			numberSign = 0 - numberSign;
			invertMatrix[i][j] = numberSign * minor / DETERMINANT;
		}
	}

	TransponeMatrix(invertMatrix);

	return true;
}