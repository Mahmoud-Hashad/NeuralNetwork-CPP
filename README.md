# Neural Network CPP

A basic neural network for cpp.

### Refrence:
  - [Neural Networks - The Nature of Code](https://www.youtube.com/watch?v=XJ7HLz9VYz0&list=PLRqwX-V7Uu6aCibgK1PTWWu9by6XFdCfh) playlist.
  



### Example to solve this table of Encoder in Digital Logic
![Encoder in Digital Logic 8 input table](https://media.geeksforgeeks.org/wp-content/uploads/truth-table-8x3-encoder.jpg)

main.cpp
``` cpp
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

```

Output
```
0.019268   0.0226517   0.0244565
0.0292944  0.0232308   0.975572
0.0245737  0.977746    0.0232404
0.0206427  0.972657    0.97778
0.977647   0.0316204   0.0252108
0.974451   0.024845    0.974917
0.96751    0.975125    0.0253917
0.98331    0.9786      0.977557
```


