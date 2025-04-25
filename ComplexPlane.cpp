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
void ComplexPlane::setMouseLocation(Vector2i mousPixel) {
	// !!! TO DO
}
void ComplexPlane::loadText(Text& text);
// PRIVATE FUNCTIONS
size_t ComplexPlane::countIterations(Vector2f coord);
void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b);

Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel) {
	// !!! TO DO
}
