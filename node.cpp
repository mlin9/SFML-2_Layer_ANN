#include "node.h"
//Constructors
Node::Node(int num_weights)
{
	learn_weight = 0.3;
	weights = new double[num_weights];
	this->num_weights = num_weights;
	value = 0.0;
	init();
}
Node::Node(){}
//Deconstructor
Node::~Node(){ delete[] weights; }
//Initializer
void Node::init()
{
	//Generate random weights between -1.0 and 1.0
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(-1.0, 0.0);
	//Set weights
	for(int i = 0; i < num_weights; i++)
		weights[i] = dis(gen);
}
//Input function
void Node::input(double input){ value += input; }
//Transmit function
void Node::transmit(Node &output_node, int index){ output_node.input(value * weights[index]); }
//Hidden node transmit function
void Node::transmit_hidden(Node &output_node){ output_node.input(value * weights[0]); }
//Weight learning function
void Node::weight_learn(double input_error, int index){ weights[index] += learn_weight * input_error * value; }
//Hidden node learning function
void Node::hidden_weight_learn(double input_error){ weights[0] += learn_weight * input_error * value; }
//Error learning function
void Node::error_learn(double input_error){ error = (value*(1 - value)) * input_error; }
//Squashing function
void Node::squash(){ value = 1/(1 + pow(M_E, -1*value)); }
