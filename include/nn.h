#ifndef NN_H
#define NN_H

#include "matrix.h"


class NeuralNetwork
{
private:
  unsigned int input_nodes = 0;
  unsigned int hidden_nodes = 0;
  unsigned int out_nodes = 0;
  double learning_rate = 0;
  matrix* weights_ih = nullptr;
  matrix* weights_ho = nullptr;
  matrix* bias_h = nullptr;
  matrix* bias_o = nullptr;
public:
  NeuralNetwork(unsigned int in_nodes,unsigned int hid_nodes, unsigned int out_nodes);
  NeuralNetwork(NeuralNetwork* n);
  vector<double>* predict(vector<double>* input_array);
  void train(vector<double>* input_array, vector<double>* target_array);
  NeuralNetwork* copy();
  void mutate(double (*func)(double, unsigned int, unsigned int));
  void setLearnRate(double rate = 0.1);

  ~NeuralNetwork();
};

#endif // NN_H
