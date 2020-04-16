#ifndef MATRIX_H
#define MATRIX_H
#include <vector>

using namespace std;

class matrix
{
private:
  unsigned int rows;
  unsigned int cols;

public:
  vector<vector<double>> data;
  matrix(unsigned int rows, unsigned int cols);
  matrix * copy();
  static matrix* fromArray(vector<double> *arr);
  static matrix* subtract(matrix* a, matrix *b);
  vector<double>* toArray();
  matrix* randomize();
  matrix* add(double n);
  matrix* add(matrix *m);
  static matrix* transpose(matrix *m);
  static matrix* multiply(matrix *a, matrix *b);
  matrix* multiply(matrix *m);
  matrix* multiply(double m);


  matrix* map(double (*fun)(double, unsigned int, unsigned int));
  static matrix* map(matrix* m, double (*fun)(double, unsigned int, unsigned int));


  ~matrix();

  void print();
};

#endif // MATRIX_H-
