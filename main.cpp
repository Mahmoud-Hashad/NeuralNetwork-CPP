#include <iostream>
#include "nn.h"


using namespace std;

int main()
{
    NeuralNetwork* nn = new NeuralNetwork(8, 14, 3);
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


    for(unsigned int i = 0; i < 10000; i++) {
      int t_index = i % 8;
      nn->train(&inputs[t_index], &outputs[t_index]);
    }

    vector<vector<double>> test_array = {
      {0, 0, 0, 0, 0, 0, 0, 1},
      {0, 0, 0, 0, 0, 0, 1, 0},
      {0, 0, 0, 0, 0, 1, 0, 0},
      {0, 0, 0, 0, 1, 0, 0, 0},
      {0, 0, 0, 1, 0, 0, 0, 0},
      {0, 0, 1, 0, 0, 0, 0, 0},
      {0, 1, 0, 0, 0, 0, 0, 0},
      {1, 0, 0, 0, 0, 0, 0, 0}
    };

    for(auto test : test_array) {
      vector<double>* t = nn->predict(&test);
      for(int i = 0; i < t->size(); i++) {
        cout << t->at(i) << " ";
      }
      cout << endl;
      delete t;
    }


    return 0;
}
