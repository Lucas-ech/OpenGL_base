#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include <exception>
#include "Headers.h"
#include "Shader.h"
#include "ResourceHolder.h"
#include "../ResourceIdentifiers.h"

namespace Core {
	class Shape {

		public:
			Shape(Shader shader);
			~Shape();
			void draw(glm::mat4 &projection, glm::mat4 &view);

		protected:
			void sendVertex();
			std::vector<GLfloat> m_vertices;
			std::vector<GLfloat> m_coords;
			sf::Texture *m_texture;

		private:
			void genVBO();
			void genVAO();
			bool m_vertexSent;
			Shader m_shader;
			GLuint m_vaoID;
			GLuint m_vboID;
			unsigned long int m_sizeofVertices;
			unsigned long int m_sizeofCoords;

	};
}

#endif //SHAPE_H