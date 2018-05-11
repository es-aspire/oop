#pragma once

constexpr unsigned int MATRIX_HEIGHT = 3;
constexpr unsigned int  MATRIX_WIDTH = 3;
constexpr unsigned int  INIT_MATRIX_NUMBER = 0;
constexpr unsigned int  COUNT_SIGNIFICANT_DIGIT = 2;
constexpr unsigned int  NON_EXISTENT_DETERMINANT = 0;

typedef double Matrix3x3[MATRIX_HEIGHT][MATRIX_WIDTH];
typedef double Matrix2x2[2][2];

void InitMatrix(Matrix3x3 &matrix);
bool ReadMatrix(std::istream &input, Matrix3x3 &matrix);
void PrintMatrix(const Matrix3x3 &matrix);

double GetDeterminant3x3(const Matrix3x3 &matrix);
double GetDeterminant2x2(const Matrix2x2 &matrix2x2);
double GetMinor(const Matrix3x3 &matrix, unsigned int row, unsigned int column);

void TransponeMatrix(Matrix3x3 &matrix);
bool InvertMatrix(const Matrix3x3 &inputMatrix, Matrix3x3 &invertMatrix);