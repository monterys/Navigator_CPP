#ifndef CPP_S21_MATRIXPLUS_1_S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

namespace my {

#define ZERO 0.000001

class S21Matrix {
 public:
  S21Matrix() noexcept;
  S21Matrix(int row, int col);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other);
  ~S21Matrix();

  int GetRows() const noexcept;
  int GetCols() const noexcept;
  void SetRows(int rows);
  void SetCols(int cols);

  bool EqMatrix(const S21Matrix &other) noexcept;
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num) noexcept;
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix &operator=(S21Matrix &&other) noexcept;
  S21Matrix operator+(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other);
  S21Matrix operator*(const S21Matrix &other);
  S21Matrix operator*(double num);
  friend S21Matrix operator*(double num, S21Matrix &other);
  bool operator==(const S21Matrix &other) noexcept;
  void operator+=(const S21Matrix &other);
  void operator-=(const S21Matrix &other);
  void operator*=(const S21Matrix &other);
  void operator*=(double num) noexcept;
  double &operator()(int i, int j);
  double operator()(int i, int j) const;

  double GetM(int row, int col) noexcept;
  void SetM(int row, int col, double x) noexcept;

 private:
  int rows_{0}, cols_{0};
  double **matrix_{nullptr};

  void MemoryAlloc();
  void MemoryFree();
  void ValueTransfer(int rows, int cols, const S21Matrix &other) noexcept;
  double TwoSizeMmatrix() noexcept;
  double DeterminantRecurs();
  void MinorMatrix(int i_rows, int i_columns, S21Matrix &other);
};

}  // namespace my

#endif