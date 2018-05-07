#include <random>
#include <iostream>
#ifndef NODE_H
#define NODE_H
#define NUM_HIDDEN 2
using namespace std;
class Node
{
	public:
		Node(int num_weights);
		Node();
		~Node();
		void input(double input);
		void transmit(Node &output_node, int index);
		void transmit_hidden(Node &output_node);
		void weight_learn(double input_error, int index);
		void hidden_weight_learn(double input_error);
		void error_learn(double input_error);
		void squash();
		double *weights;
		double value;
		double learn_weight;
		double error;
	private:
		void init();
		int num_weights;
};
#endif
