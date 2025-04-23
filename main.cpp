// C++ libraries
#include <SFML/Graphics.hpp>
#include <iostream>


using namespace sf;
using namespace std;


int main()

{

	int pixelWidth = VideoMode::getDesktopMode().width;
	int pixelHeight = VideoMode::getDesktopMode().height;

	VideoMode vm(pixelWidth, pixelHeight);

	RenderWindow window(vm, "Rainbow Screen", Style::Default);



	while (window.isOpen())

	{

		/*
		****************************************
						INPUT
		****************************************
		*/

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
		// loadText

		// END of UPDATE

		window.clear();


		/*
		****************************************
						DRAW
		****************************************
		*/
		// 
		// 
		// END of DRAW


		window.display();

	}




}
