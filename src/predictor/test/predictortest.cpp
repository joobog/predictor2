/*
 * =====================================================================================
 *
 *       Filename:  predictor.cpp
 *
 *    Description: 
 *
 *        Version:  1.0
 *        Created:  03/06/2015 09:05:59 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */


#include <iostream>
//#include "src/predictor/NeuralNetwork.hpp"
#include "../CART.hpp"
#include <tuple>

int main(int argc, char** argv) {
	using namespace std;
  using FPredictor = CART<std::vector<double>, double>;
	FPredictor::init();
	FPredictor predictor;	

//	predictor.open("/scratch/pool/CIS/m215026/git/siox_ml_plugin/data/iris/iris.data");
//	predictor.open("/scratch/pool/CIS/m215026/git/siox_ml_plugin/data/input.csv");
	predictor.open("/scratch/pool/CIS/m215026/git/siox_ml_plugin/data/input_clean_data_fill.csv");
	predictor.train();

	std::vector<FPredictor::Features> features{{1, 2, 3, 4}, {2, 3, 4, 3}, {2, 1, 4, 2}, {5.8, 2.7, 5.1, 1.9}};
	cout << "test_main" << endl;

	std::vector<FPredictor::Labels> labels = predictor.predict(features);
	cout << "predicted value: ";
	for (size_t i = 0; i < labels.size(); ++i) {
		cout << labels[i] << " : " ;
	}
	cout << endl;
	predictor.evaluate();

//	cout << labels << endl;
	return 0;
}
