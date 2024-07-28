#include "Primitive.h"
#include "../base/VertexBuffer.h"

std::shared_ptr<hiveWindow::CVertexBuffer> hiveWindow::CPrimitive::createSquare()
{
    std::vector<float> vertices = {
     -0.5f, -0.5f, 0.0f,   0.0f,  0.0f,  1.0f,  1.0f, 0.0f, 0.0f,// left  bottom
      0.5f, -0.5f, 0.0f,   0.0f,  0.0f,  1.0f,   0.0f, 1.0f, 0.0f,// right bottom
     -0.5f, 0.5f, 0.0f,    0.0f,  0.0f,  1.0f,   0.0f, 0.0f, 1.0f,// left top
     -0.5f, 0.5f, 0.0f,    0.0f,  0.0f,  1.0f,   0.0f, 0.0f, 1.0f,// left top
      0.5f, 0.5f, 0.0f,    0.0f,  0.0f,  1.0f,   1.0f, 0.0f, 0.0f,// right top
      0.5f, -0.5f, 0.0f,   0.0f,  0.0f,  1.0f,   0.0f, 1.0f, 0.0f,// right bottom
    };
    std::vector<int> AttributeLayout = { 3, 3, 3 };

	return std::make_shared<CVertexBuffer>(vertices, AttributeLayout, GL_STATIC_DRAW, GL_TRIANGLES);
}
