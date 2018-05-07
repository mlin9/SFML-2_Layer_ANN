#include "node.h"
#include <iostream>
#include <string>
#ifndef ANN_H
#define ANN_H
#define NUM_INPUTS 4
#define NUM_HIDDEN 2
#define NUM_OUTPUTS 1
using namespace std;
class NNetwork
{
	public:
	NNetwork();
	~NNetwork();
	void step(double *input, double target);
	void learn(double target);
	void train();
	void set_learn_weight(double input);
	double **training_data;
	//double **input_weights;
	//double **hidden_weights;
	double output;
	double result;
	string status;
	string condition;
	int tick;
	int epochs;
	private:
	Node *input_layer;
	Node *hidden_layer;
	Node output_node;
};
#endif
