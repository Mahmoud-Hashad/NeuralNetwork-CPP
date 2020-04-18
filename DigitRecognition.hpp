#ifndef DIGITRECOGNITION_HPP_INCLUDED
#define DIGITRECOGNITION_HPP_INCLUDED

using namespace std;

int ReverseInt (int i);
void mnistReadImages(string file_path, long images_count, long image_length, vector<vector<double>> &output_array);
void mnistReadLabels(string file_path, long labels_count, vector<vector<double>> &output_array);
bool correct(vector<double>* p, vector<double>* a);
void DigitRecognition();

#endif // DIGITRECOGNITION_HPP_INCLUDED
