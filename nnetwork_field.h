#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "nnetwork.h"
#ifndef ANN_V_H
#define ANN_V_H
#define _USE_MATH_DEFINES
using namespace std;
class NNetwork_field
{
	public:
	NNetwork_field(sf::RenderWindow *input_window);
	void init();
	void draw();
	void update();
	void train();
	void set_learn_weight(double input);
	private:
	sf::RenderWindow *screen;
	sf::Font font;
	sf::RectangleShape pixels[NUM_INPUTS];
	sf::CircleShape input_nodes[NUM_INPUTS];
	sf::Text inputs_text[NUM_INPUTS];
	sf::Vertex input_lines_begin[NUM_INPUTS];
	sf::CircleShape hidden_nodes[NUM_HIDDEN];
	sf::Vertex input_lines_end[NUM_HIDDEN];
	sf::CircleShape output_node;
	sf::Text output_text;
	sf::Text status_text;
	sf::Text condition_text;
	sf::Text epochs_text;
	sf::RectangleShape result_box;
	sf::Vertex hidden_lines_end;
	sf::Vertex output_line[2];
	sf::Vertex line_buffer[2];
	NNetwork network;
};
#endif
