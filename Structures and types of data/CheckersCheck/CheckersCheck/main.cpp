#include <SFML/graphics.hpp>
#include <iostream>
#include "checkers.h"

int CoordToNumber(double coord)
{
	int a = 40;
	return ((int)coord + a) / 100 - 1;
}

int main()
{

	sf::RenderWindow window(sf::VideoMode(800, 800), "Checkers Check");

	std::vector<sf::CircleShape> figures;


	sf::RectangleShape background(sf::Vector2f(800.f, 800.f));
	background.setFillColor(sf::Color::White);

	sf::Texture desk_texture;
	if (!desk_texture.loadFromFile("desk_texture_file.png"))
	{
		// error...
	}
	background.setTexture(&desk_texture);

	board MyBoard;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonReleased && figures.size() < 24 
				&& event.mouseButton.y > 60 && event.mouseButton.y < 740
				&& event.mouseButton.x > 60 && event.mouseButton.x < 740)
			{
				sf::CircleShape shape(28.f);
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					shape.setFillColor(sf::Color::White);
					MyBoard.field[MyBoard.field.size() - 1 - CoordToNumber(event.mouseButton.y)][CoordToNumber(event.mouseButton.x)].is_white = true;
					MyBoard.field[MyBoard.field.size() - 1 - CoordToNumber(event.mouseButton.y)][CoordToNumber(event.mouseButton.x)].is_buisy = true;
				}
				else if (event.mouseButton.button == sf::Mouse::Right)
				{
					shape.setFillColor(sf::Color::Black);
					MyBoard.field[MyBoard.field.size() - 1 - CoordToNumber(event.mouseButton.y)][CoordToNumber(event.mouseButton.x)].is_buisy = true;
				}
				shape.setOutlineThickness(10.f);
				shape.setOutlineColor(sf::Color(250, 150, 100));
				shape.setPosition(event.mouseButton.x - 28, event.mouseButton.y - 28);
				figures.push_back(shape);
				
				std::cout << "button was pressed" << std::endl;
				std::cout << "mouse x: " << event.mouseButton.x << std::endl;
				std::cout << "mouse y: " << event.mouseButton.y << std::endl;
				
			}
			if (event.type == sf::Event::KeyReleased)
			{
				std::cout << "The answer is:" << std::endl;
				if (event.key.code == sf::Keyboard::Enter)
				{
					possibilityToMove(&MyBoard) ? std::cout << "true" << std::endl : std::cout << "false" << std::endl;

				}
			}
		}
		window.clear();
		window.draw(background);
		for (const auto& r : figures)
			window.draw(r);
		window.display();
	}
	
	bool res = possibilityToMove(&MyBoard);

	return 0;
}