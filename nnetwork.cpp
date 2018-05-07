#include "nnetwork.h"
//Constructor
NNetwork::NNetwork()
{
	input_layer = new Node[NUM_INPUTS];
	hidden_layer = new Node[NUM_HIDDEN];
	for(int i = 0; i < NUM_INPUTS; i++)
		input_layer[i] = Node(NUM_HIDDEN);
	for(int i = 0; i < NUM_HIDDEN; i++)
		hidden_layer[i] = Node(NUM_OUTPUTS);
	tick = 0;
	epochs = 0;
}

//Deconstructor
NNetwork::~NNetwork()
{
	for(int i = 0; i < 16; i++)
		delete[] training_data[i];
	delete[] training_data;
	delete[] input_layer;
	delete[] hidden_layer;
	tick = 0;
	epochs = 0;
}

//Forward input and calculation
void NNetwork::step(double *input, double target)
{
	//Iterate ticks and epochs
	tick++;
	if(tick%16 == 0)
		epochs++;
	//Initial status
	status = "bright";
	//Push inputs and transmit to hidden layer
	for(int i = 0; i < NUM_INPUTS; i++)
	{
		input_layer[i].value = 0;
		input_layer[i].input(input[i]);
		input_layer[i].transmit(hidden_layer[0], 0);
		input_layer[i].transmit(hidden_layer[1], 1);
	}
	//Calculate hidden outputs and transmit to output node
	for(int i = 0; i < NUM_HIDDEN; i++)
	{
		hidden_layer[i].squash();
		hidden_layer[i].transmit_hidden(output_node);
	}
	//Calculate final output of output node
	output_node.squash();
	//Record final output value
	output = output_node.value;
	result = output;
	//Change status to dark
	if(output < 0.1)
		status = "dark";
	//Backpropagation
	learn(target);
}

//Backpropagation
void NNetwork::learn(double target)
{
	//Calculate error
 	double error = target - result;
	//Output error calculation
	output_node.error_learn(error);
	double error_buffer;
	//Hidden layer error calculation and weight adjustment
	for(int i = 0; i < NUM_HIDDEN; i++)
	{
		error_buffer = output_node.error * hidden_layer[i].weights[0];
		hidden_layer[i].error_learn(error_buffer);
		hidden_layer[i].hidden_weight_learn(output_node.error);
	}
	//Input layer weight adjustment
	for(int i = 0; i < NUM_INPUTS; i++)
	{
		for(int j = 0; j < NUM_HIDDEN; j++)
		{
			input_layer[i].weight_learn(hidden_layer[j].error, j);
			cout << "Input Node " << i << " weight " << j << ": " << input_layer[i].weights[j] << endl;
		}
		input_layer[i].value = 0.0;
	}
	//Reset values to zero
	hidden_layer[0].value = 0.0;
	hidden_layer[1].value = 0.0;
	output_node.value = 0.0;
}

//Training function
void NNetwork::train()
{
	//Declare 2D array of training data
	training_data = new double*[16];
	for(int i = 0; i < 16; i++)
		training_data[i] = new double[4];
	//Initialize 2D array of training data
	int data_index = 0;
	double data_string[] = {-1,-1,-1,-1,
							-1,-1,-1, 1,
							-1,-1, 1,-1,
							-1,-1, 1, 1,
							-1, 1,-1,-1,
							-1, 1,-1, 1,
							-1, 1, 1,-1,
							-1, 1, 1, 1,
							 1,-1,-1,-1,
							 1,-1,-1, 1,
							 1,-1, 1,-1,
							 1,-1, 1, 1,
							 1, 1,-1,-1,
							 1, 1,-1, 1,
							 1, 1, 1,-1,
							 1, 1, 1, 1};
	double targets[] = {-0.5, -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, 0.5, -0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5};
	//Train ANN with data
	for(int row = 0; row < 16; row++)
	{
		for(int col = 0; col < 4; col++)
		{
			training_data[row][col] = data_string[data_index];
			data_index++;
		}
		step(training_data[row], targets[row]);
	}
}

//Setter function for learn weights
void NNetwork::set_learn_weight(double input)
{
	for(int i = 0; i < NUM_INPUTS; i++)
	{
		input_layer[i].learn_weight = input;
		hidden_layer[i].learn_weight = input;
	}
}
