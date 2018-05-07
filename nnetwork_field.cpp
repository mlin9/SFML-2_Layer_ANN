#include "nnetwork_field.h"
//Constructor
NNetwork_field::NNetwork_field(sf::RenderWindow *input_window)
{
	screen = input_window;
	if (!font.loadFromFile("TNR.ttf"))
		exit(EXIT_FAILURE);
}

//Initializer
void NNetwork_field::init()
{
	//Initialize size variables
	sf::Vector2u dim = screen->getSize();
	float width = dim.x;
	float height = dim.y;
	int rect_length = 50;
	int char_length = rect_length/2;
	float pos_x, pos_y;
	//Initialize input pixels, nodes and text
	for(int i = 0; i < NUM_INPUTS; i++)
	{
		pos_x = (width/6) + ((rect_length) * cos((i * M_PI/2) + M_PI/4));
		pos_y = (height/2) + ((rect_length) * sin((i * M_PI/2) + M_PI/4));
		pixels[i].setSize(sf::Vector2f(rect_length, rect_length));
		pixels[i].setOrigin(rect_length/2, rect_length/2);
		pixels[i].setPosition(pos_x, pos_y);
		pixels[i].setFillColor(sf::Color::White);
		pos_x = 2*(width/6);
		pos_y = i*(height/5) + (height/5);
		input_nodes[i].setRadius(rect_length/2);
		input_nodes[i].setOrigin(rect_length/2, rect_length/2);
		input_nodes[i].setPosition(pos_x, pos_y);
		input_nodes[i].setFillColor(sf::Color::White);
		inputs_text[i].setFont(font);
		inputs_text[i].setCharacterSize(char_length);
		inputs_text[i].setOrigin(char_length/4,char_length*0.625);
		inputs_text[i].setPosition(pos_x-50, pos_y);
		inputs_text[i].setColor(sf::Color::White);
		inputs_text[i].setString("0");
		input_lines_begin[i] = sf::Vector2f(pos_x, pos_y);
		input_lines_begin[i].color = sf::Color::White;
	}
	//Initialize hidden nodes and text
	for(int i = 0; i < NUM_HIDDEN; i++)
	{
		pos_x = width/2;
		pos_y = i*(height/3) + (height/3);
		hidden_nodes[i].setRadius(rect_length/2);
		hidden_nodes[i].setOrigin(rect_length/2, rect_length/2);
		hidden_nodes[i].setPosition(pos_x, pos_y);
		hidden_nodes[i].setFillColor(sf::Color::Yellow);
		input_lines_end[i] = sf::Vector2f(pos_x, pos_y);
		input_lines_end[i].color = sf::Color::Yellow;
	}
	//Initialize output node and text
	pos_x = 4*(width/6);
	pos_y = height/2;
	output_node.setRadius(rect_length/2);
	output_node.setOrigin(rect_length/2, rect_length/2);
	output_node.setPosition(pos_x, pos_y);
	output_node.setFillColor(sf::Color::Red);
	hidden_lines_end = sf::Vector2f(pos_x, pos_y);
	hidden_lines_end.color = sf::Color::Red;
	output_line[0] = sf::Vector2f(4*width/6, height/2);
	output_line[0].color = sf::Color::Red;
	output_line[1] = sf::Vector2f(5*width/6, height/2);
	output_line[1].color = sf::Color::White;
	result_box.setSize(sf::Vector2f(rect_length*4, rect_length));
	result_box.setOrigin(rect_length/2, rect_length/2);
	result_box.setPosition(5*width/6, height/2);
	result_box.setFillColor(sf::Color::White);
	output_text.setFont(font);
	output_text.setCharacterSize(char_length);
	output_text.setOrigin(char_length/4,char_length*0.625);
	output_text.setPosition(5*width/6, height/2);
	output_text.setColor(sf::Color::Black);
	output_text.setString("0");
	status_text.setFont(font);
	status_text.setCharacterSize(char_length);
	status_text.setPosition(5*width/6, height/3);
	status_text.setColor(sf::Color::White);
	status_text.setString("0");
	condition_text.setFont(font);
	condition_text.setCharacterSize(char_length);
	condition_text.setPosition(5*width/6, 2*height/3);
	condition_text.setColor(sf::Color::White);
	condition_text.setString("0");
	epochs_text.setFont(font);
	epochs_text.setCharacterSize(char_length);
	epochs_text.setPosition(50,50);
	epochs_text.setColor(sf::Color::Red);
	epochs_text.setString("0");
}

//Drawing function
void NNetwork_field::draw()
{
	for(int i = 0; i < NUM_INPUTS; i++)
	{
		line_buffer[0] = input_lines_begin[i];
		for(int j = 0; j < NUM_HIDDEN; j++)
		{
			line_buffer[1] = input_lines_end[j];
			screen->draw(line_buffer, 2, sf::Lines);
		}
		screen->draw(pixels[i]);
		screen->draw(inputs_text[i]);
		screen->draw(input_nodes[i]);
	}
	line_buffer[1] = hidden_lines_end;
	for(int i = 0; i < NUM_HIDDEN; i++)
	{
		line_buffer[0] = input_lines_end[i];
		screen->draw(line_buffer, 2, sf::Lines);
		screen->draw(hidden_nodes[i]);
	}
	screen->draw(output_line, 2, sf::Lines);
	screen->draw(output_node);
	screen->draw(result_box);
	screen->draw(output_text);
	screen->draw(condition_text);
	screen->draw(status_text);
	screen->draw(epochs_text);
}

//Update function
void NNetwork_field::update()
{
	//Input variables
	string text_buffer;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 1);
	double input[4];
	int target = 0;
	//Generate random inputs
	for(int i = 0; i < NUM_INPUTS; i++)
	{
		if(dis(gen))
		{
			input[i] = 1;
			inputs_text[i].setString("1");
			pixels[i].setFillColor(sf::Color::White);
			target += 1;
		}
		else
		{
			input[i] = -1;
			inputs_text[i].setString("-1");
			pixels[i].setFillColor(sf::Color::Black);
			target += -1;
		}
	}
	//Call step function for ANN
	if(target < 0)
		network.step(input, -0.5);
	else
		network.step(input, 0.5);
	//Update output strings
	output_text.setString(std::to_string(network.result));
	status_text.setString(network.status);
	condition_text.setString(network.condition);
	epochs_text.setString("Epoch #: " + std::to_string(network.epochs));
}
//Training function
void NNetwork_field::train(){ network.train(); }
//Set learn weight function
void NNetwork_field::set_learn_weight(double input){ network.set_learn_weight(input); }
