#include <cmath>
#include <exception>
#include <iostream>

#include "my_matrix_oop.h"

namespace my {

S21Matrix::S21Matrix() noexcept {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows < 0 || cols < 0) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  MemoryAlloc();
}

S21Matrix::S21Matrix(S21Matrix &&other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  MemoryAlloc();
  ValueTransfer(rows_, cols_, other);
}

S21Matrix::~S21Matrix() {
  MemoryFree();
  rows_ = 0;
  cols_ = 0;
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this == &other) return *this;
  rows_ = other.rows_;
  cols_ = other.cols_;
  MemoryFree();
  MemoryAlloc();
  ValueTransfer(rows_, cols_, other);
  return *this;
}

S21Matrix &S21Matrix::operator=(S21Matrix &&other) noexcept {
  if (this == &other) return *this;
  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
  std::swap(matrix_, other.matrix_);
  return *this;
}

void S21Matrix::ValueTransfer(int rows, int cols,
                              const S21Matrix &other) noexcept {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

int S21Matrix::GetRows() const noexcept { return rows_; };

int S21Matrix::GetCols() const noexcept { return cols_; };

void S21Matrix::MemoryFree() {
  if (matrix_) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }
}

void S21Matrix::MemoryAlloc() {
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]{};
  }
}

void S21Matrix::SetRows(int rows) {
  if (rows < 0) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  if (rows_ != rows) {
    S21Matrix tmp(std::move(*this));
    int cycle = tmp.rows_;
    if (tmp.rows_ > rows) cycle = rows;
    cols_ = tmp.cols_;
    rows_ = rows;
    MemoryAlloc();
    ValueTransfer(cycle, cols_, tmp);
  }
}

void S21Matrix::SetCols(int cols) {
  if (cols < 0) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  if (cols_ != cols) {
    S21Matrix tmp(std::move(*this));
    int cycle = tmp.cols_;
    if (tmp.cols_ > cols) cycle = cols;
    rows_ = tmp.rows_;
    cols_ = cols;
    MemoryAlloc();
    ValueTransfer(rows_, cycle, tmp);
  }
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix tmp(cols_, rows_);
  for (int i = 0; i < tmp.rows_; i++) {
    for (int j = 0; j < tmp.cols_; j++) {
      tmp.matrix_[i][j] = matrix_[j][i];
    }
  }
  return tmp;
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_ || other.matrix_ == nullptr) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  S21Matrix temp(rows_, other.cols_);
  for (int i = 0; i < temp.rows_; i++) {
    for (int j = 0; j < temp.cols_; j++) {
      for (int k = 0; k < other.rows_; k++) {
        temp.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  SetCols(other.cols_);
  ValueTransfer(rows_, cols_, temp);
}

void S21Matrix::MulNumber(const double num) noexcept {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] * num;
    }
  }
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_ ||
      other.matrix_ == nullptr) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_ ||
      other.matrix_ == nullptr) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
    }
  }
}

bool S21Matrix::EqMatrix(const S21Matrix &other) noexcept {
  bool res = 1;
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    res = 0;
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) > ZERO) {
          res = 0;
        }
      }
    }
  }
  return res;
}

double S21Matrix::Determinant() {
  double result = 0;
  if (!(rows_ == cols_)) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  };
  if (rows_ == 1) {
    result = matrix_[0][0];
  } else if (rows_ == 2) {
    result = TwoSizeMmatrix();
  } else {
    result = DeterminantRecurs();
  }
  return result;
}

double S21Matrix::DeterminantRecurs() {
  double result = 0;
  S21Matrix tmp(rows_ - 1, cols_ - 1);
  for (int i = 0; i < cols_; i++) {
    MinorMatrix(0, i, tmp);
    if ((rows_ - 1) == 2) {
      if (i % 2) {
        result -= matrix_[0][i] * tmp.TwoSizeMmatrix();
      } else {
        result += matrix_[0][i] * tmp.TwoSizeMmatrix();
      }
    } else {
      if (i % 2) {
        result -= matrix_[0][i] * tmp.DeterminantRecurs();
      } else {
        result += matrix_[0][i] * tmp.DeterminantRecurs();
      }
    }
  }
  return result;
}

void S21Matrix::MinorMatrix(int i_rows, int i_columns, S21Matrix &other) {
  int res_rows = 0, res_column = 0;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (i != i_rows && j != i_columns) {
        other.matrix_[res_rows][res_column] = matrix_[i][j];
        res_column++;
        if (res_column == other.cols_) {
          res_rows++;
          res_column = 0;
        }
      }
    }
  }
}

double S21Matrix::TwoSizeMmatrix() noexcept {
  return (matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0]);
}

S21Matrix S21Matrix::CalcComplements() {
  if (!(rows_ == cols_)) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  S21Matrix result(rows_, cols_);
  if (rows_ == 1) {
    result.matrix_[0][0] = 1;
  } else {
    for (int i = 0; i < result.rows_; i++) {
      for (int j = 0; j < result.cols_; j++) {
        S21Matrix minor(rows_ - 1, cols_ - 1);
        MinorMatrix(i, j, minor);
        result.matrix_[i][j] = pow(-1, (i + 1 + j + 1)) * minor.Determinant();
      }
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  double determinant = Determinant();
  if (fabs(determinant) < ZERO) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  S21Matrix calc = CalcComplements();
  S21Matrix result = calc.Transpose();
  result.MulNumber(1 / determinant);
  return result;
}

double &S21Matrix::operator()(int row, int col) {
  if (row >= rows_ || col >= cols_) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return matrix_[row][col];
}

double S21Matrix::operator()(int row, int col) const {
  if (row >= rows_ || col >= cols_) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return matrix_[row][col];
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix tmp(rows_, cols_);
  tmp.ValueTransfer(rows_, cols_, *this);
  tmp.SumMatrix(other);
  return tmp;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix tmp(rows_, cols_);
  tmp.ValueTransfer(rows_, cols_, *this);
  tmp.SubMatrix(other);
  return tmp;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix tmp(rows_, cols_);
  tmp.ValueTransfer(rows_, cols_, *this);
  tmp.MulMatrix(other);
  return tmp;
}

S21Matrix S21Matrix::operator*(double num) {
  S21Matrix tmp(rows_, cols_);
  tmp.ValueTransfer(rows_, cols_, *this);
  tmp.MulNumber(num);
  return tmp;
}

bool S21Matrix::operator==(const S21Matrix &other) noexcept {
  return EqMatrix(other);
}

void S21Matrix::operator+=(const S21Matrix &other) { SumMatrix(other); }

void S21Matrix::operator-=(const S21Matrix &other) { SubMatrix(other); }

void S21Matrix::operator*=(const S21Matrix &other) { MulMatrix(other); }

void S21Matrix::operator*=(double num) noexcept { MulNumber(num); }

S21Matrix operator*(double num, S21Matrix &other) {
  S21Matrix tmp(other.GetRows(), other.GetCols());
  tmp.ValueTransfer(other.rows_, other.cols_, other);
  tmp.MulNumber(num);
  return tmp;
}

double S21Matrix::GetM(int row, int col) noexcept { return matrix_[row][col]; };

void S21Matrix::SetM(int row, int col, double x) noexcept {
  matrix_[row][col] = x;
};

}  // namespace my