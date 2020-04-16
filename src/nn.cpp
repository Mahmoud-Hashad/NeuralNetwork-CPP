#include "nn.h"
#include <math.h>
#include "matrix.h"


class sigmoid {
public:
  static double func(double x, unsigned int i, unsigned int j) {
    return 1.0 / (1.0 + exp(-x));
  }
  static double dfunc(double y, unsigned int i, unsigned int j) {
    return y * (1  - y);
  }
};



NeuralNetwork::NeuralNetwork(unsigned int in_nodes,unsigned int hid_nodes, unsigned int out_nodes)
{
  this->input_nodes = in_nodes;
  this->hidden_nodes = hid_nodes;
  this->out_nodes = out_nodes;


  this->weights_ih = new matrix(this->hidden_nodes, this->input_nodes);
  this->weights_ho = new matrix(this->out_nodes, this->hidden_nodes);

  this->weights_ih->randomize();
  this->weights_ho->randomize();

  this->bias_h = new matrix(this->hidden_nodes, 1);
  this->bias_o = new matrix(this->out_nodes, 1);

  this->bias_h->randomize();
  this->bias_o->randomize();

  this->setLearnRate();

}

NeuralNetwork::NeuralNetwork(NeuralNetwork* n) {
  this->input_nodes = n->input_nodes;
  this->hidden_nodes = n->hidden_nodes;
  this->out_nodes = n->out_nodes;
  this->learning_rate = n->learning_rate;

  this->weights_ih = n->weights_ih->copy();
  this->weights_ho = n->weights_ho->copy();

  this->bias_h = n->bias_h->copy();
  this->bias_o = n->bias_o->copy();
}


vector<double>* NeuralNetwork::predict(vector<double>* input_array) {
  // Generating the Hidden Outputs
  matrix* inputs = matrix::fromArray(input_array);
  matrix* hidden = matrix::multiply(this->weights_ih, inputs);
  hidden->add(this->bias_h);

  // activation function!
  hidden->map(sigmoid::func);

  // Generating the output's output!
  matrix* output = matrix::multiply(this->weights_ho, hidden);
  output->add(this->bias_o);
  output->map(sigmoid::func);

  vector<double>* output_array = output->toArray();

  // free allocated memory
  delete inputs;
  delete hidden;
  delete output;

  return output_array;
}


void NeuralNetwork::train(vector<double>* input_array, vector<double>* target_array) {
  // Generating the Hidden Outputs
  matrix* inputs = matrix::fromArray(input_array);
  matrix* hidden = matrix::multiply(this->weights_ih, inputs);
  hidden->add(this->bias_h);

  // activation function!
  hidden->map(sigmoid::func);

  // Generating the output's output!
  matrix* outputs = matrix::multiply(this->weights_ho, hidden);
  outputs->add(this->bias_o);
  outputs->map(sigmoid::func);

  // Convert vector to matrix
  matrix* targets = matrix::fromArray(target_array);

  // Calculate the error
  matrix* output_errors = matrix::subtract(targets, outputs);

  // Calculate gradient
  matrix* gradients = matrix::map(outputs, sigmoid::dfunc);
  gradients->multiply(output_errors);
  gradients->multiply(this->learning_rate);

  // Calculate deltas
  matrix* hidden_T = matrix::transpose(hidden);
  matrix* weight_ho_deltas = matrix::multiply(gradients, hidden_T);

  // Adjust the weights by deltas
  this->weights_ho->add(weight_ho_deltas);
  // Adjust the bias by its deltas (which is just the gradients)
  this->bias_o->add(gradients);

  // Calculate the hidden layer errors
  matrix* who_t = matrix::transpose(this->weights_ho);
  matrix* hidden_errors = matrix::multiply(who_t, output_errors);

  // Calculate hidden gradient
  matrix* hidden_gradient = matrix::map(hidden, sigmoid::dfunc);
  hidden_gradient->multiply(hidden_errors);
  hidden_gradient->multiply(this->learning_rate);

  // Calculate input->hidden deltas
  matrix* inputs_T = matrix::transpose(inputs);
  matrix* weight_ih_deltas = matrix::multiply(hidden_gradient, inputs_T);

  this->weights_ih->add(weight_ih_deltas);

  // Adjust the bias by its deltas (which is just the gradients)
  this->bias_h->add(hidden_gradient);

  // free allocated memory
  delete inputs;
  delete hidden;
  delete outputs;
  delete targets;
  delete output_errors;
  delete gradients;
  delete hidden_T;
  delete weight_ho_deltas;
  delete who_t;
  delete hidden_errors;
  delete hidden_gradient;
  delete inputs_T;
  delete weight_ih_deltas;


}

// Adding function for Neuroevolution
NeuralNetwork* NeuralNetwork::copy() {
  return new NeuralNetwork(this);
}

// Accept an arbitrary function for mutation
void NeuralNetwork::mutate(double (*func)(double, unsigned int, unsigned int)) {
  this->weights_ih->map(func);
  this->weights_ho->map(func);
  this->bias_h->map(func);
  this->bias_o->map(func);
}


void NeuralNetwork::setLearnRate(double rate)
{
  this->learning_rate = rate;
}




NeuralNetwork::~NeuralNetwork() {
  delete weights_ih;
  delete weights_ho;
  delete bias_h;
  delete bias_o;
}
