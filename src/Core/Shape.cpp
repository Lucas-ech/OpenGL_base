#include "Shape.h"

namespace Core {
	Shape::Shape(Shader shader, TextureHolder &textureHolder) : m_shader(shader), m_vaoID(0), m_vboID(0), m_sizeofVertices(0), m_sizeofCoord(0) {
	    glBindTexture(GL_TEXTURE_2D, 0);
	    glUseProgram(0);
	    glBindVertexArray(0);
	    glBindBuffer(GL_ARRAY_BUFFER, 0);
		m_vertices ={-2, -2, -2,   2, -2, -2,   2, 2, -2,   // Triangle 1
                    -2, -2, -2,   -2, 2, -2,   2, 2, -2};  // Triangle 2
		/*{
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
	    };*/

	    m_coord = {
	    	0, 0,   1, 0,   1, 1,
           	0, 0,   0, 1,   1, 1
        };

	    genVBO();
	    genVAO();
	    textureHolder.load(Textures::TextureTest, "Images/test.png");
		m_tempTexture = &textureHolder.get(Textures::TextureTest);
	}

	Shape::~Shape() {
		// Destruction d'un éventuel ancien VBO
		if(glIsBuffer(m_vboID) == GL_TRUE) {
	        glDeleteBuffers(1, &m_vboID);
	    }

	    // Destruction d'un éventuel ancien VAO
	    if(glIsVertexArray(m_vaoID) == GL_TRUE) {
	        glDeleteVertexArrays(1, &m_vaoID);
	    }
	}

	void Shape::draw(glm::mat4 &projection, glm::mat4 &view) {

		assert(m_vboID != 0);
		assert(m_vaoID != 0);

		// Activation du shader
		glUseProgram(m_shader.getProgramID());

			// Verrouillage du VAO
        	glBindVertexArray(m_vaoID);

        		// On envoie les matrices au shader
			    glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"), 1, GL_FALSE, glm::value_ptr(view));
			    glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

			    sf::Texture::bind(m_tempTexture);

        		glDrawArrays(GL_TRIANGLES, 0, 6);

        		sf::Texture::bind(NULL);

        	// Déverrouillage du VAO
        	glBindVertexArray(0);

		// Désactivation du shader
   		glUseProgram(0);
	}

	/*
	TODO: Prendre en charge la frequence de changement:
	 - GL_STATIC_DRAW : pour les données très peu mises à jour
	 - GL_DYNAMIC_DRAW : pour les données mises à jour fréquemment (plusieurs fois par seconde mais pas à chaque frame)
	 - GL_STREAM_DRAW : pour les données mises à jour tout le temps
	*/
	void Shape::genVBO() {
		// Destruction d'un éventuel ancien VBO
	    if(glIsBuffer(m_vboID) == GL_TRUE) {
	        glDeleteBuffers(1, &m_vboID);
	    }

    	m_sizeofVertices = m_vertices.size() * sizeof(float);
    	m_sizeofCoord = m_coord.size() * sizeof(float);

    	// Creation du Vertex Buffer Object
    	glGenBuffers(1, &m_vboID);

    	// Verrouillage du VBO
    	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

	    	// Allocation de la mémoire de la carte graphique
	        glBufferData(GL_ARRAY_BUFFER, m_sizeofVertices + m_sizeofCoord, 0, GL_STATIC_DRAW);

		        //Transfert
		        glBufferSubData(GL_ARRAY_BUFFER, 0, m_sizeofVertices, &m_vertices[0]);
		        glBufferSubData(GL_ARRAY_BUFFER, m_sizeofVertices, m_sizeofCoord, &m_coord[0]);

		// Déverrouillage du VBO
	    glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Shape::genVAO() {
		// Destruction d'un éventuel ancien VAO
	    if(glIsVertexArray(m_vaoID) == GL_TRUE) {
	        glDeleteVertexArrays(1, &m_vaoID);
	    }

		// Creation du Vertex Array Object
	    glGenVertexArrays(1, &m_vaoID);

	    // Verrouillage du VAO
    	glBindVertexArray(m_vaoID);

		    // Verrouillage du VBO
			glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

			    // Accès aux vertices dans la mémoire vidéo
			    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
			    glEnableVertexAttribArray(0);

			    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_sizeofVertices));
    			glEnableVertexAttribArray(2);

			// Déverrouillage du VBO
			glBindBuffer(GL_ARRAY_BUFFER, 0);

	    // Déverrouillage du VAO
    	glBindVertexArray(0);
	}


}