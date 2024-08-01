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


std::shared_ptr<hiveWindow::CVertexBuffer> hiveWindow::CPrimitive::createQuad()
{
	std::vector<float> Vertices{
		// positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};
	std::vector<unsigned int> Indices{
		0, 1, 2, // first Triangle
		0, 2, 3, // second Triangle
	};
	return std::make_shared<CVertexBuffer>(Vertices, Indices, std::vector<int>{2, 2});
}

std::shared_ptr<hiveWindow::CVertexBuffer> hiveWindow::CPrimitive::createFloor()
{
	std::vector<float> floorVertices{
		// positions            // normals         // texcoords
		 25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
		-25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
		-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,

		 25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
		-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
		 25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,  25.0f, 25.0f
	};
	std::vector<int> AttributeLayout = { 3, 3, 2 };
	return std::make_shared<CVertexBuffer>(floorVertices, AttributeLayout, GL_STATIC_DRAW, GL_TRIANGLES);
}
