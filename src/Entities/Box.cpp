#include "Box.h"

Box::Box(Core::Shader shader, TextureHolder &textureHolder) : Shape(shader) {
	m_vertices = {
	 	-0.5f, -0.5f, -0.5f,   0.5f, -0.5f, -0.5f,   0.5f, 0.5f, -0.5f,
	 	-0.5f, -0.5f, -0.5f,   -0.5f, 0.5f, -0.5f,   0.5f, 0.5f, -0.5f,

	 	-0.5f, -0.5f, -0.5f,   -0.5f, -0.5f, 0.5f,   -0.5f, 0.5f, 0.5f,
	 	-0.5f, -0.5f, -0.5f,   -0.5f, 0.5f, -0.5f,   -0.5f, 0.5f, 0.5f,

	 	-0.5f, -0.5f, 0.5f,   0.5f, -0.5f, 0.5f,   0.5f, 0.5f, 0.5f,
	 	-0.5f, -0.5f, 0.5f,   -0.5f, 0.5f, 0.5f,   0.5f, 0.5f, 0.5f,

	 	0.5f, -0.5f, -0.5f,   0.5f, -0.5f, 0.5f,   0.5f, 0.5f, 0.5f,
	 	0.5f, -0.5f, -0.5f,   0.5f, 0.5f, -0.5f,   0.5f, 0.5f, 0.5f,

	 	-0.5f, -0.5f, -0.5f,   -0.5f, -0.5f, 0.5f,   0.5f, -0.5f, 0.5f,
	 	-0.5f, -0.5f, -0.5f,   0.5f, -0.5f, -0.5f,   0.5f, -0.5f, 0.5f,

	 	-0.5f, 0.5f, -0.5f,   -0.5f, 0.5f, 0.5f,   0.5f, 0.5f, 0.5f,
	 	-0.5f, 0.5f, -0.5f,   0.5f, 0.5f, -0.5f,   0.5f, 0.5f, 0.5f,
    };

    m_coords = {
    	0, 0,   1, 0,   1, 1,
       	0, 0,   0, 1,   1, 1,
       	0, 0,   1, 0,   1, 1,     // Face 2
		0, 0,   0, 1,   1, 1,     // Face 2
		0, 0,   1, 0,   1, 1,     // Face 3
		0, 0,   0, 1,   1, 1,     // Face 3
		0, 0,   1, 0,   1, 1,     // Face 4
		0, 0,   0, 1,   1, 1,     // Face 4
		0, 0,   1, 0,   1, 1,     // Face 5
		0, 0,   0, 1,   1, 1,     // Face 5
		0, 0,   1, 0,   1, 1,     // Face 6
		0, 0,   0, 1,   1, 1
	};
	sendVertex();
	textureHolder.load(Textures::TextureTest, "Images/Caisse.jpg");
	m_texture = &textureHolder.get(Textures::TextureTest);
	sf::Image image = m_texture->copyToImage();
	image.flipVertically();
	m_texture->update(image);
}

Box::~Box() {

}