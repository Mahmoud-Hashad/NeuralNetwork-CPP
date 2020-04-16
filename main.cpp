#include <iostream>
#include "matrix.h"
#include "nn.h"
#include <time.h>

using namespace std;

int main()
{
    NeuralNetwork* test = new NeuralNetwork(8, 14, 3, 0.01);
    vector<vector<double>> inputs = {
      {0, 0, 0, 0, 0, 0, 0, 1},
      {0, 0, 0, 0, 0, 0, 1, 0},
      {0, 0, 0, 0, 0, 1, 0, 0},
      {0, 0, 0, 0, 1, 0, 0, 0},
      {0, 0, 0, 1, 0, 0, 0, 0},
      {0, 0, 1, 0, 0, 0, 0, 0},
      {0, 1, 0, 0, 0, 0, 0, 0},
      {1, 0, 0, 0, 0, 0, 0, 0}
    };
    vector<vector<double>> outputs = {
      {0, 0, 0},
      {0, 0, 1},
      {0, 1, 0},
      {0, 1, 1},
      {1, 0, 0},
      {1, 0, 1},
      {1, 1, 0},
      {1, 1, 1},
    };
    srand(time(0));
    for(unsigned int i = 0; i < 10000; i++) {
      int t_index = i % 8;
      test->train(&inputs[t_index], &outputs[t_index]);
    }

    vector<vector<double>> data = {
      {0, 0, 0, 0, 0, 0, 0, 1},
      {0, 0, 0, 0, 0, 0, 1, 0},
      {0, 0, 0, 0, 0, 1, 0, 0},
      {0, 0, 0, 0, 1, 0, 0, 0},
      {0, 0, 0, 1, 0, 0, 0, 0},
      {0, 0, 1, 0, 0, 0, 0, 0},
      {0, 1, 0, 0, 0, 0, 0, 0},
      {1, 0, 0, 0, 0, 0, 0, 0}
    };

    for(auto d : data) {
      vector<double>* t = test->predict(&d);
      cout << t->at(0) << " " << t->at(1) << " " << t->at(2) << " " << endl;
      delete t;
    }


    return 0;
}
