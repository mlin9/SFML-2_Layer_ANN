#include "environment.h"
int main() {
	sf::RenderWindow window( sf::VideoMode( 960, 600 ), "Neural Network");
	Environment environment(&window);
	environment.start();
	return 0;
}
