#include <SFML/Graphics.hpp>
#include <iostream>
#include "ComplexPlane.h"


using namespace sf;
using namespace std;


int main()

{

	int pixelWidth = VideoMode::getDesktopMode().width / 2;
	int pixelHeight = VideoMode::getDesktopMode().height / 2;

	/*int pixelWidth = 1920;
	int pixelHeight = 1080;*/

	VideoMode vm(pixelWidth, pixelHeight);

	RenderWindow window(vm, "Mandlebrot", Style::Default);

	RenderStates rStates;

	ComplexPlane plane(pixelWidth, pixelHeight);

	// Font
	Font font;

	if (!font.loadFromFile("./Fonts/BLACCS__.TTF"))
	{
		return EXIT_FAILURE;
	}

	// Text
	Text text;
	text.setFont(font);
	text.setCharacterSize(50);
	text.setStyle(Text::Regular);

	while (window.isOpen())

	{
		/*
		****************************************
						INPUT
		****************************************
		*/

		Event event;
		while (window.pollEvent(event))
		{
			// Mouse events
			if (event.type == sf::Event::MouseButtonPressed)
			{
				// Gets mouse location and sets the center
				Vector2i location(event.mouseButton.x, event.mouseButton.y); // event::mouse pressed
				plane.setCenter(location);

				// Zoom in or out based on what button was clicked
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					plane.zoomIn();
				}
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					plane.zoomOut();
				}
			}

			if (event.type == Event::MouseMoved) // event::mouse moved
			{
				Vector2i location(event.mouseMove.x, event.mouseMove.y);
				plane.setMouseLocation(location);
			}

			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
			}

			if (event.type == sf::Event::Closed)
				window.close();
		}


		/*
		****************************************
						UPDATE
		****************************************
		*/

		plane.updateRender();
		plane.loadText(text);

		window.clear();

		/*
		****************************************
						DRAW
		****************************************
		*/

		plane.draw(window, rStates);
		window.draw(text);

		window.display();

	}




}
