#include <iostream>
#include <fstream>
#include <vector>
#include "DigitRecognition.hpp"
#include "nn.h"
#include "math.h"
#include "time.h"

using namespace std;

int ReverseInt (int i)
{
    unsigned char ch1, ch2, ch3, ch4;
    ch1=i&255;
    ch2=(i>>8)&255;
    ch3=(i>>16)&255;
    ch4=(i>>24)&255;
    return((int)ch1<<24)+((int)ch2<<16)+((int)ch3<<8)+ch4;
}


// read images from mnist and store them in 2d vector
void mnistReadImages(string file_path, long images_count, long image_length, vector<vector<double>> &output_array) {
  // allocate memory
  output_array.resize(images_count, vector<double>(image_length));

  // open images file
  ifstream images_f (file_path, ios::binary);

  if(images_f.is_open()) {
    int magicNumber = 0, totalImages  = 0;
    int rowsCount = 0, colsCount = 0;

    // magic number
    images_f.read((char *) &magicNumber, sizeof(int));
    magicNumber = ReverseInt(magicNumber);

    // total images in the file
    images_f.read((char *) &totalImages, sizeof(int));
    totalImages = ReverseInt(totalImages);

    // rows count
    images_f.read((char *) &rowsCount, sizeof(int));
    rowsCount = ReverseInt(rowsCount);

    // columns
    images_f.read((char *) &colsCount, sizeof(int));
    colsCount = ReverseInt(colsCount);

    // get images data
    for(int image = 0; image < totalImages && image < images_count; image++) {
      for(int row = 0; row < rowsCount; row++) {
        for(int col = 0; col < colsCount; col++) {
            unsigned char temp = 0;
            images_f.read((char*) &temp, sizeof(char));
            if(temp == 0) temp = 1;
            output_array[image][(rowsCount * row) + col] = (double)temp / 255.0;
        }
      }
    }

    images_f.close();
  } else {
    throw runtime_error("can't find the file");
  }

}

// read labels from mnist and store them in 2d vector
void mnistReadLabels(string file_path, long labels_count, vector<vector<double>> &output_array) {
  output_array.resize(labels_count, vector<double>(10));

  // open labels file
  ifstream labels_f (file_path, ios::binary);

  if(labels_f.is_open()) {
    int magicNumber = 0, totalLabels = 0;

    // magic number
    labels_f.read((char *) &magicNumber, sizeof(int));
    magicNumber = ReverseInt(magicNumber);

    // total labels in the file
    labels_f.read((char *) &totalLabels, sizeof(int));
    totalLabels = ReverseInt(totalLabels);

    // get labels
    for(int label = 0; label < totalLabels && label < labels_count; label++) {
            unsigned char temp = 0;
            labels_f.read((char*) &temp, sizeof(char));
            output_array[label][(int)temp] = 1;
    }
    labels_f.close();
  } else {
    throw runtime_error("can't find the file");
  }

}

// find index of max value in two array and compare them
bool correct(vector<double>* p, vector<double>* a) {
  int m1 = 0;
  int m2 = 0;
  for(int j = 0; j < p->size(); j++) {
    if(p->at(j) > p->at(m1)) m1 = j;
    if(a->at(j) > a->at(m2)) m2 = j;
  }
  return m1 == m2;
}


void DigitRecognition() {

  NeuralNetwork* nn = new NeuralNetwork(784, 256, 10);

  vector<vector<double>> trainingImages_array;
  vector<vector<double>> trainingLables_array;
  vector<vector<double>> testingImages_array;
  vector<vector<double>> testingLables_array;

  // load data
  cout << "Load Training Data:";
  mnistReadImages("./training/train-images.idx3-ubyte", 60000, 784, trainingImages_array);
  mnistReadLabels("./training/train-labels.idx1-ubyte", 60000, trainingLables_array);
  cout << " Done\n" << endl;

  cout << "Load Testing Data:";
  mnistReadImages("./training/t10k-images.idx3-ubyte", 10000, 784, testingImages_array);
  mnistReadLabels("./training/t10k-labels.idx1-ubyte", 10000, testingLables_array);
  cout << " Done\n" << endl;


  cout << "Learning:" << endl;
  for(int l = 0; l < 2; l++) {
    cout << "  Epoch " << l + 1 << ":" << endl;

    // train nn
    cout << "    Training: ";
    for(int i = 0; i < trainingImages_array.size(); i++) {
        nn->train(&trainingImages_array[i], &trainingLables_array[i]);
    }
    cout << "Done" << endl;

    // test and calculate accuracy
    cout << "    Testing: ";
    double c = 0;
    for(int i = 0; i < testingImages_array.size(); i++) {
      vector<double>* p = nn->predict(&testingImages_array[i]);
      c += correct(p, &testingLables_array[i]);
      delete p;
    }
    cout << "Done" << endl;
    cout << "    Accuracy: " << (c / testingImages_array.size()) * 100.0 << "%" << endl << endl;
  }


}
