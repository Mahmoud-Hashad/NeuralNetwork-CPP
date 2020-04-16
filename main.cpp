#include <iostream>
#include <matrix.h>

using namespace std;

int main()
{
    matrix* t = new matrix(3, 3);
    t->data[0] = {1, 2, 3};
    t->data[1] = {4, 5, 6};
    t->data[2] = {7, 8, 9};

    matrix* x = t->copy();
    x->print();

    return 0;
}
