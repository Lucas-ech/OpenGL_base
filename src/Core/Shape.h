#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include "Headers.h"
#include "Shader.h"
#include "ResourceHolder.h"
#include "../ResourceIdentifiers.h"

namespace Core {
	class Shape {

		public:
			Shape(Shader shader, TextureHolder &textureHolder);
			~Shape();
			void draw(glm::mat4 &projection, glm::mat4 &view);

		private:
			void genVBO();
			void genVAO();
			Shader m_shader;
			GLuint m_vaoID;
			GLuint m_vboID;
			std::vector<GLfloat> m_vertices;
			std::vector<GLfloat> m_coord;
			sf::Texture *m_tempTexture;
			unsigned long int m_sizeofVertices;
			unsigned long int m_sizeofCoord;

	};
}

#endif //SHAPE_H