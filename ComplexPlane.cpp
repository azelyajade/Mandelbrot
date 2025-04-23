// header stuff
#include "ComplexPlane.h"

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight) {
	m_pixel_size = { pixelWidth, pixelHeight };
	m_aspectRatio = // CALCULATE;
	m_plane_center = { 0,0 };
	m_plane_size = { BASE_WIDTH, BASE_HEIGHT * m_aspectRatio };
	m_zoomCount = 0;

	VertexArray m_va;
	m_va.setPrimitiveType(Points);
	m_va.resize(pixelWidth * pixelHeight);
}

void ComplexPlane::draw(RenderTarget& target, RenderStates states) const {

}
void ComplexPlane::updateRender();
void ComplexPlane::zoomIn();
void ComplexPlane::zoomOut();
void ComplexPlane::setCenter(Vector2i mousePixel);
void ComplexPlane::setMouseLocation(Vector2i mousPixel);
void ComplexPlane::loadText(Text& text);

size_t ComplexPlane::countIterations(Vector2f coord);
void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b);
Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel);
