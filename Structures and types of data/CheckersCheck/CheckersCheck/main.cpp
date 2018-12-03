#include <SFML/graphics.hpp>
#include <iostream>
#include "checkers.h"

int CoordToNumber(double coord)
{
	int a = (int)coord/8 + 40;
	return ((int)coord + a) / 100 - 1;
}

int main()
{
	sf::RenderWindow MainWindow(sf::VideoMode(800, 800), "Checkers Check");
	sf::RenderWindow StartWindow(sf::VideoMode(400, 200), "Controls");

	board MyBoard;

	std::vector<sf::CircleShape> figures;
	
	sf::RectangleShape background(sf::Vector2f(800.f, 800.f));
	background.setFillColor(sf::Color::White);
	
	sf::Font font;
	if (!font.loadFromFile("Roboto-Regular.ttf"))
	{

	}

	sf::Texture desk_texture;
	if (!desk_texture.loadFromFile("desk_texture_file.png"))
	{
		// error...
	}
	background.setTexture(&desk_texture);
	
	sf::Text text;
	text.setFont(font); // font is a sf::Font
	text.setString("LMB - put a white checker \nRMB - put a black checker \nMMB - put a white king \nENTER - check possibility to move");
	text.setCharacterSize(24); // in pixels, not points!
	text.setFillColor(sf::Color::White);

	while (StartWindow.isOpen())
	{
		sf::Event event;
		while (StartWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				StartWindow.close();
		}
		StartWindow.draw(text);
		StartWindow.display();
	}

	while (MainWindow.isOpen())
	{
		sf::Event event;
		while (MainWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				MainWindow.close();
			if (event.type == sf::Event::MouseButtonReleased && figures.size() < 24
				&& event.mouseButton.y > 60 && event.mouseButton.y < 740
				&& event.mouseButton.x > 60 && event.mouseButton.x < 740)
			{
				sf::CircleShape shape(28.f);
				shape.setOutlineThickness(10.f);
				shape.setOutlineColor(sf::Color(250, 150, 100));

				if (event.mouseButton.button == sf::Mouse::Left)
				{
					shape.setFillColor(sf::Color::White);
					MyBoard.field[MyBoard.field.size() - 1 - CoordToNumber(event.mouseButton.y)][CoordToNumber(event.mouseButton.x)].is_white = true;
					MyBoard.field[MyBoard.field.size() - 1 - CoordToNumber(event.mouseButton.y)][CoordToNumber(event.mouseButton.x)].is_buisy = true;
				}
				if (event.mouseButton.button == sf::Mouse::Middle)
				{
					shape.setFillColor(sf::Color::White);
					shape.setOutlineColor(sf::Color(255, 50, 0));
					MyBoard.field[MyBoard.field.size() - 1 - CoordToNumber(event.mouseButton.y)][CoordToNumber(event.mouseButton.x)].is_white = true;
					MyBoard.field[MyBoard.field.size() - 1 - CoordToNumber(event.mouseButton.y)][CoordToNumber(event.mouseButton.x)].is_buisy = true;
					MyBoard.field[MyBoard.field.size() - 1 - CoordToNumber(event.mouseButton.y)][CoordToNumber(event.mouseButton.x)].is_king = true;
				}
				else if (event.mouseButton.button == sf::Mouse::Right)
				{
					shape.setFillColor(sf::Color::Black);
					MyBoard.field[MyBoard.field.size() - 1 - CoordToNumber(event.mouseButton.y)][CoordToNumber(event.mouseButton.x)].is_buisy = true;
				}

				shape.setPosition(event.mouseButton.x - 28, event.mouseButton.y - 28);
				figures.push_back(shape);
			}
			if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Enter))
			{
				sf::RenderWindow ResultWindow(sf::VideoMode(400, 50), "Answer");
				possibilityToMove(&MyBoard) ? text.setString("Whites can make a step") : text.setString("Whites cannot make a step");
				text.setPosition(50, 10);
									
				ResultWindow.draw(text);
				ResultWindow.display();
				while (ResultWindow.isOpen())
				{	sf::Event event;
					while (ResultWindow.pollEvent(event))
					{
						if (event.type == sf::Event::Closed)
							ResultWindow.close();
					}
				}
			}
			MainWindow.clear();
			MainWindow.draw(background);
			for (const auto& r : figures)
				MainWindow.draw(r);
			MainWindow.display();
		}
	}
	return 0;
}