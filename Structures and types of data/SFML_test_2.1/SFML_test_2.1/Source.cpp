#include <SFML/graphics.hpp>
#include <iostream>
int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
	
	sf::CircleShape shape(28.f);
	shape.setFillColor(sf::Color::Red);
	shape.setOutlineThickness(10.f);
	shape.setOutlineColor(sf::Color(250, 150, 100));
	shape.setPosition(350.f, 350.f);

	sf::RectangleShape rectangle(sf::Vector2f(800.f, 800.f));
	rectangle.setFillColor(sf::Color::White);

	sf::Texture desk_texture;
	if (!desk_texture.loadFromFile("desk.png"))
	{
		// error...
	}
	rectangle.setTexture(&desk_texture);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (event.type == sf::Event::MouseMoved)
		{
			std::cout << "new mouse x: " << event.mouseMove.x << std::endl;
			std::cout << "new mouse y: " << event.mouseMove.y << std::endl;
		}
		window.clear();
		window.draw(rectangle);
		window.draw(shape);
		window.display();
	}

	return 0;
}