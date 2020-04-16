#include "matrix.h"
#include <iostream>
#include<time.h>
using namespace std;



matrix::matrix(unsigned int rows, unsigned int cols)
{
  this->rows = rows;
  this->cols = cols;
  this->data.resize(rows, vector<double>(cols, 0));
}

matrix* matrix::copy() {
  matrix *temp = new matrix(this->rows, this->cols);
  for(unsigned int i = 0; i < this->rows; i++) {
    for(unsigned int j = 0; j < this->cols; j++) {
        temp->data[i][j] = this->data[i][j];
    }
  }
  return temp;
}

matrix* matrix::fromArray(vector<double> *arr) {
  matrix *temp = new matrix(arr->size(), 1);
  for(unsigned int i = 0; i < arr->size(); i++) {
    temp->data[i][0] = arr->at(i);
  }
  return temp;
}


// Return a new Matrix a-b
matrix* matrix::subtract(matrix *a, matrix *b) {
  if(a->rows != b->rows || a->cols != b->cols) {
     throw std::invalid_argument( "Columns and Rows of A must match Columns and Rows of B.");
  }

  matrix *temp = new matrix(a->rows, a->cols);

  for(unsigned int i = 0; i < a->rows; i++) {
    for(unsigned int j = 0; j < a->cols; j++) {
      temp->data[i][j] = a->data[i][j] - b->data[i][j];
    }
  }

  return temp;
}


vector<double>* matrix::toArray() {
  vector<double> * temp = new vector<double>(this->rows * this->cols);
  unsigned int index = 0;
  for(unsigned int i = 0; i < this->rows; i++) {
    for(unsigned int j = 0; j < this->cols; j++) {
      temp->at(index++) = this->data[i][j];
    }
  }
  return temp;
}


matrix* matrix::randomize() {
  srand(time(NULL));

  for(unsigned int i = 0; i < this->rows; i++) {
    for(unsigned int j = 0; j < this->cols; j++) {
      this->data[i][j] = ((double) rand() / (RAND_MAX)) * 2 - 1;
    }
  }

  return this;
}


matrix* matrix::add(double n) {
  for(unsigned int i = 0; i < this->rows; i++) {
    for(unsigned int j = 0; j < this->cols; j++) {
      this->data[i][j] += n;
    }
  }

  return this;
}

matrix* matrix::add(matrix* m) {
{
  if(this->rows != m->rows || this->cols != m->cols) {
     throw std::invalid_argument( "Columns and Rows of A must match Columns and Rows of B.");
  }

  for(unsigned int i = 0; i < this->rows; i++) {
    for(unsigned int j = 0; j < this->cols; j++) {
      this->data[i][j] += m->data[i][j];
    }
  }

  return this;
}}



matrix* matrix::transpose(matrix *m) {
  matrix* temp = new matrix(m->cols, m->rows);
  for(unsigned int i = 0; i < temp->rows; i++) {
    for(unsigned int j = 0; j < temp->cols; j++) {
      temp->data[i][j] = m->data[j][i];
    }
  }

  return temp;
}



matrix* matrix::multiply(matrix *a, matrix *b) {
  if(a->cols != b->rows) {
     throw std::invalid_argument("Columns of A must match rows of B.");
  }

  matrix* temp = new matrix(a->rows, b->cols);
  for(unsigned int i = 0; i < a->rows; i++) {
    for(unsigned int j = 0; j < b->cols; j++) {
      double sum = 0;
      for(unsigned int k = 0; k < a->cols; k++) {
        sum += a->data[i][k] * b->data[k][j];
      }
      temp->data[i][j] = sum;
    }
  }

  return temp;
}



matrix* matrix::multiply(matrix *m) {
  if (this->rows != m->rows || this->cols != m->cols) {
    throw std::invalid_argument("Columns and Rows of A must match Columns and Rows of B.");
  }

  for(unsigned int i = 0; i < this->rows; i++) {
    for(unsigned int j = 0; j < this->cols; j++) {
      this->data[i][j] *= m->data[i][j];
    }
  }

  return this;
}

matrix* matrix::multiply(double m) {
  for(unsigned int i = 0; i < this->rows; i++) {
    for(unsigned int j = 0; j < this->cols; j++) {
      this->data[i][j] *= m;
    }
  }

  return this;
}





// Apply a function to every element of matrix
matrix* matrix::map(double (*fun)(double, unsigned int, unsigned int)) {
  for(unsigned int i = 0; i < this->rows; i++) {
    for(unsigned int j = 0; j < this->cols; j++) {
      double val = this->data[i][j];
      this->data[i][j] = fun(val, i, j);
    }
  }

  return this;
}

// Return new matrix after apply a function to every element of matrix "m"
matrix* matrix::map(matrix* m, double (*fun)(double, unsigned int, unsigned int)) {
  matrix* temp = new matrix(m->rows, m->cols);
  for(unsigned int i = 0; i < temp->rows; i++) {
    for(unsigned int j = 0; j < temp->cols; j++) {
      double val = m->data[i][j];
      temp->data[i][j] = fun(val, i, j);
    }
  }

  return temp;
}



matrix::~matrix() {
  vector<vector<double> >().swap(this->data);
}



void matrix::print() {
  for(unsigned int i = 0; i < rows; i++) {
    for(unsigned int j = 0; j < cols; j++) {
      cout << this->data[i][j] << " ";
    }
    cout << endl;
  }
}
