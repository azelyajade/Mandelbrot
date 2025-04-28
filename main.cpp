// C++ libraries
#include <SFML/Graphics.hpp>
#include "ComplexPlane.h"
#include <iostream>


using namespace sf;
using namespace std;


int main()

{

	int pixelWidth = VideoMode::getDesktopMode().width;
	int pixelHeight = VideoMode::getDesktopMode().height;

	VideoMode vm(pixelWidth, pixelHeight);

	RenderWindow window(vm, "Mandlebrot", Style::Default);

	RenderStates rStates;

	ComplexPlane plane(pixelWidth, pixelHeight);

	// Font
	Font font;

	if (!font.loadFromFile("./Fonts/BLACCS_.ttf"))
	{
		cout << "Uh oh" << endl;
	}

	// Text

	Text text;
	text.setFont(font);
	text.setCharacterSize(10);
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
				Vector2i location(event.mouseButton.x, event.mouseButton.y);
				plane.setCenter(location);

				// Zoom in or out based on what button was clicked
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					std::cout << "the left button was pressed" << std::endl;

					plane.zoomIn();
				}
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					std::cout << "the right button was pressed" << std::endl;

					plane.zoomOut();
				}
			}
			if (event.type == Event::MouseMoved)
			{
				Vector2i location(event.mouseMove.x, event.mouseMove.y);
				plane.setMouseLocation(location);
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		// event::closed
		// event::mouse pressed
		// event::mouse moved

		// END of INPUT


		/*
		****************************************
						UPDATE
		****************************************
		*/
		// updateRender
		plane.updateRender();
		// loadText
		plane.loadText(text);

		// END of UPDATE

		window.clear();


		/*
		****************************************
						DRAW
		****************************************
		*/
		// 
		plane.draw(window, rStates);
		window.draw(text);
		// 
		// END of DRAW


		window.display();

	}




}
