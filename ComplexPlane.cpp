// header stuff
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <complex>  
#include <ctime>
#include <thread>
#include "ComplexPlane.h"

using namespace sf;
using namespace std;

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight) {
	m_pixel_size = { pixelWidth, pixelHeight };
	m_aspectRatio = pixelWidth / static_cast<float>(pixelHeight);
	m_plane_center = { 0,0 };
	m_plane_size = { BASE_WIDTH, BASE_HEIGHT / m_aspectRatio };
	m_zoomCount = 0;
	m_state = State::CALCULATING;

	m_va.setPrimitiveType(Points);
	m_va.resize(pixelWidth * pixelHeight);
}

void ComplexPlane::draw(RenderTarget& target, RenderStates states) const {
	target.draw(m_va);
}

void ComplexPlane::updateRender() {
	if (m_state == State::CALCULATING) {
		clock_t start = clock();
		thread t1(&ComplexPlane::loops, this, 0, 0, 2, 2);
		thread t2(&ComplexPlane::loops, this, m_pixel_size.x/2, 0, 1, 2);
		thread t3(&ComplexPlane::loops, this, 0, m_pixel_size.y / 2, 1, 1);
		thread t4(&ComplexPlane::loops, this, m_pixel_size.x / 2, m_pixel_size.y / 2, 1, 1);

		t1.join();
		t2.join();
		t3.join();
		t4.join();

		clock_t end = clock();
		cout << "TIME: " << (end - start) << endl;
		m_state = State::DISPLAYING;
	}
}

void ComplexPlane::loops(int xStart, int yStart, int xLimiter, int yLimiter) {
	for (int i = yStart; i < m_pixel_size.y / yLimiter; i++) {
		for (int j = xStart; j < m_pixel_size.x / xLimiter; j++) {
			// set postion
			m_va[j + i * m_pixel_size.x].position = { (float)j, (float)i };

			Vector2i coordToMap(j, i);

			// find vector coord
			Vector2f coord = mapPixelToCoords(coordToMap);

			// store iterations
			size_t iterations = countIterations(coord);

			// RGB values
			Uint8 r, g, b;

			// pass iterations into RGB
			iterationsToRGB(iterations, r, g, b);

			// set color
			m_va[j + i * m_pixel_size.x].color = { r,g,b };
		}
	}
}

void ComplexPlane::zoomIn() {
	m_zoomCount++;
	float xVal = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
	float yVal = BASE_HEIGHT / m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
	m_plane_size = { xVal, yVal };
	m_state = State::CALCULATING;
}

void ComplexPlane::zoomOut() {
	m_zoomCount--;
	float xVal = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
	float yVal = BASE_HEIGHT / m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
	m_plane_size = { xVal, yVal };
	m_state = State::CALCULATING;
}

void ComplexPlane::setCenter(Vector2i mousePixel) {
	Vector2f coord = mapPixelToCoords(mousePixel);
	m_plane_center = coord;
	m_state = State::CALCULATING;
	//cout << "Center: " << m_plane_center.x << " " << m_plane_center.y << endl;
}
void ComplexPlane::setMouseLocation(Vector2i mousePixel) {
	m_mouseLocation = mapPixelToCoords(mousePixel);
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

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
	//float lightness = 0.5;
	//float saturation = 1;
	//float hue = count * (300 / MAX_ITER - 1); // Only get a hue that goes up to 300 degrees to not repeat red
	/*int n = 5;
	float v = (pow((count / MAX_ITER), 2) * n);
	v = pow(v, 1.5);
	v = (int)v % n;

	r = v * 255;
	g = 120;
	b = v * 255;*/



	/*cout << "Hue: " << hue << endl;*/
	if (count >= MAX_ITER)
	{
		/*cout << "max" << endl;*/
		r = 0;
		g = 0;
		b = 0;
	}
	if (count < MAX_ITER)
	{
		/*cout << " > 48" << endl;*/
		r = 255 - ((MAX_ITER - count) * 16) -1;
		g = 0;
		b = 100;
	}
	if (count < MAX_ITER/2)
	{
		/*cout << " > 48" << endl;*/
		r = 255 - ((MAX_ITER - count) * 16) -1;
		g = 0;
		b = 0;
	}
	if (count < MAX_ITER / 4)
	{
		//cout << " > 32" << endl;
		r = 255  - ((MAX_ITER - count) * 16) -1;
		g = 255;
		b = 0;
	}
	if (count < MAX_ITER / 8)
	{
		//cout << " > 16" << endl;
		r = 0;
		g = 255 - ((MAX_ITER - count) * 16) -1;
		b = 0;
	}
	if (count < MAX_ITER / 16)
	{
		//cout << " > 8" << endl;
		r = 0;
		g = 0;
		b = 255 - ((MAX_ITER - count) * 16) -1;
	}
	if (count < MAX_ITER / 32)
	{
		//cout << " > 0" << endl;
		r = 255;
		g = 0;
		b = 255 - ((MAX_ITER - count) * 16) -1;
	}

	//int rPrime = 0,
	//	gPrime = 0,
	//	bPrime = 0;

	//int chroma = saturation;
	//int hPrime = hue / 60;
	//int x = chroma * (1 - abs(hPrime % 2 - 1));
	//int m = lightness - (chroma / 2);

	//cout << "x: " << x << endl;
	//cout << "m: " << m << endl;
	//if (hPrime >= 0 && hPrime < 1)
	//{
	//	rPrime = chroma;
	//	gPrime = x;
	//	bPrime = 0;
	//}
	//else if (hPrime >= 1 && hPrime < 2)
	//{
	//	rPrime = x;
	//	gPrime = chroma;
	//	bPrime = 0;
	//}
	//else if (hPrime >= 2 && hPrime < 3)
	//{
	//	rPrime = 0;
	//	gPrime = chroma;
	//	bPrime = x;
	//}
	//else if (hPrime >= 3 && hPrime < 4)
	//{
	//	rPrime = 0;
	//	gPrime = x;
	//	bPrime = chroma;
	//}
	//else if (hPrime >= 4 && hPrime < 5)
	//{
	//	rPrime = x;
	//	gPrime = 0;
	//	bPrime = chroma;
	//}
	//else if (hPrime >= 5 && hPrime < 6)
	//{
	//	rPrime = chroma;
	//	gPrime = 0;
	//	bPrime = x;
	//}

	//r = rPrime + m;
	//g = gPrime + m;
	//b = bPrime + m;

}

// PRIVATE FUNCTIONS
size_t ComplexPlane::countIterations(Vector2f coord) {
	int iterations = 0;

	complex<double> c(coord.x, coord.y);
	complex<double> z = 0;
	while (abs(z) < 2.0 && iterations < MAX_ITER) {
		z = z * z + c;
		iterations++;
	}

	return iterations;
}

Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel) {
	float x, y;
	x = ((static_cast<float>(mousePixel.x) / (m_pixel_size.x))) * m_plane_size.x + (m_plane_center.x - m_plane_size.x / 2.0f);
	y = ((static_cast<float>(mousePixel.y) - m_pixel_size.y) / -(m_pixel_size.y)) * m_plane_size.y + (m_plane_center.y - m_plane_size.y / 2.0f);


	Vector2f coord(x, y);


	return coord;
}

//void ComplexPlane::microThreading(int limit, Vector2f coord, int iStart) {
//	iterations
//	complex<double> c(coord.x, coord.y);
//	complex<double> z = 0;
//	while (abs(z) < 2.0 && iterations < MAX_ITER / limit) {
//		z = z * z + c;
//		iterations++;
//	}
//}