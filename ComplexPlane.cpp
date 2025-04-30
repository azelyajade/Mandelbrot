// header stuff
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <complex>  
#include "ComplexPlane.h"

using namespace sf;
using namespace std;

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight) {
	m_pixel_size = { pixelWidth, pixelHeight };
	//m_aspectRatio = // CALCULATE
	m_plane_center = { 0,0 };
	m_plane_size = { BASE_WIDTH, BASE_HEIGHT * m_aspectRatio };
	m_zoomCount = 0;

	VertexArray m_va; // IS VertexArray NEEDED?
	m_va.setPrimitiveType(Points);
	m_va.resize(pixelWidth * pixelHeight);
}

void ComplexPlane::draw(RenderTarget& target, RenderStates states) const {
	target.draw(m_va);
}

void ComplexPlane::updateRender() {
	// TO DO
}

void ComplexPlane::zoomIn() {
	m_zoomCount++;
	float xVal = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
	float yVal = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
	m_plane_size = { xVal, yVal };
	m_state = State::CALCULATING;
}

void ComplexPlane::zoomOut() {
	m_zoomCount--;
	float xVal = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
	float yVal = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
	m_plane_size = { xVal, yVal };
	m_state = State::CALCULATING;
}

void ComplexPlane::setCenter(Vector2i mousePixel) {

}
void ComplexPlane::setMouseLocation(Vector2i mousePixel) {
	// !!! TO DO
}
void ComplexPlane::loadText(Text& text)
{
	stringstream windowInfo("Mandlebrot Set\n");
	windowInfo << "Center: (" << m_plane_center.x << "," << m_plane_center.y << ")\n"
		<< "Cursor: (" << m_mouseLocation.x << "," << m_mouseLocation.y << ")\n"
		<< "Left-click to Zoom in\n"
		<< "Right-click to Zoom out\n";
	text.setString(windowInfo.str());
};
// PRIVATE FUNCTIONS
size_t ComplexPlane::countIterations(Vector2f coord)
{
	complex<double> c(coord.x, coord.y);
	complex<double> z = c;

	int i = 0;
	while (abs(z) < 2.0 && i < MAX_ITER)
	{
		z = z * z + c;
		i++;
	}

	return i;

};

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
	int lightness = 0.5;
	int saturation = 1;
	int hue = count * (300/MAX_ITER - 1); // Only get a hue that goes up to 300 degrees to not repeat red
	if (count == MAX_ITER) 
	{
		r = 0;
		g = 0;
		b = 0;
	}

	int rPrime = 0, 
		gPrime = 0, 
		bPrime = 0;

	int chroma = (1 - (abs(2 * lightness - 1)) * saturation);
	int hPrime = hue / 60;
	int x = chroma * (1 - abs(hPrime % 2 - 1));
	int m = lightness - (chroma / 2);


	if (hPrime >= 0 && hPrime < 1)
	{
		rPrime = chroma;
		gPrime = x;
		bPrime = 0;
	}
	else if(hPrime >= 1 && hPrime < 2)
	{
		rPrime = x;
		gPrime = chroma;
		bPrime = 0;
	}
	else if (hPrime >= 2 && hPrime < 3)
	{
		rPrime = 0;
		gPrime = chroma;
		bPrime = x;
	}
	else if (hPrime >= 3 && hPrime < 4)
	{
		rPrime = 0;
		gPrime = x;
		bPrime = chroma;
	}
	else if (hPrime >= 4 && hPrime < 5)
	{
		rPrime = x;
		gPrime = 0;
		bPrime = chroma;
	}
	else if (hPrime >= 5 && hPrime < 6)
	{
		rPrime = chroma;
		gPrime = 0;
		bPrime = x;
	}

	r = rPrime + m;
	g = gPrime + m;
	b = bPrime + m;

};

Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel) {
	// !!! TO DO
}