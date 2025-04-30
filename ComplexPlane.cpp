// header stuff
#include "ComplexPlane.h"

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight) {
	m_pixel_size = { pixelWidth, pixelHeight };
	m_aspectRatio = // CALCULATE;
	m_plane_center = { 0,0 };
	m_plane_size = { BASE_WIDTH, BASE_HEIGHT * m_aspectRatio };
	m_zoomCount = 0;

	VertexArray m_va; // IS VertexArray NEEDED?
	m_va.setPrimitiveType(Points);
	m_va.resize(pixelWidth * pixelHeight);
	m_state = State::DISPLAYING;
}

void ComplexPlane::draw(RenderTarget& target, RenderStates states) const {
	target.draw(m_va);
}

void ComplexPlane::updateRender() {
	if (m_state == State::CALCULATING) {
		for (int i = 0; i < pixelHeight; i++) {
			for (int j = 0; j < pixelWidth; j++) { // double loop

				// set postion
				m_va[j + i * pixelWidth].position = { (float)j,(float)i };
				
				// find vector coord
				Vector2f coord = mapPixelToCoords(j, i);

				// store iterations
				size_t iterations = countIterations(coord);

				// RGB values
				Uint8 r, g, b;

				// pass iterations into RGB
				iterationsToRGB(iterations, r, g, b);

				// set color
				m_va[j + i * pixelWidth].color = { r,g,b };

			}
		}
		m_state = State::DISPLAYING;
	}
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
	Vector2f coord = mapPixelToCoords(mousePixel);
	m_plane_center = coord;
	m_state = State::CALCULATING;
}
void ComplexPlane::setMouseLocation(Vector2i mousePixel) {
	m_mouseLocation = mapPixelToCoords(mousePixel);
}
void ComplexPlane::loadText(Text& text); // TO DO

// PRIVATE FUNCTIONS
size_t ComplexPlane::countIterations(Vector2f coord) {
	size_t iterations = 0;

	complex<double> z = 0;
	complex<double> c(coord.x, coord.y);

	while(abs(z) < 2.0 && iterations < MAX_ITER) {
		z = z * z + c;
		iterations++;
	}

	return iterations;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)

Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel) {
	// !!! TO DO
}
