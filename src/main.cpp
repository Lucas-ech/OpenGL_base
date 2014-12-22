// Link statically with GLEW
#define GLEW_STATIC

#include <GL/glew.h>
#include "Core/Headers.h"
#include <iostream>
#include <cmath>

#include "Core/Shader.h"
#include "Core/Shape.h"
#include "Core/ResourceHolder.h"
#include "ResourceIdentifiers.h"

int main()
{
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 3;
    sf::RenderWindow window(sf::VideoMode(800, 600, 32), "OpenGL", (sf::Style::Titlebar | sf::Style::Close), settings);
    window.setFramerateLimit(10);
    #ifndef NDEBUG
        settings = window.getSettings();
        assert(settings.majorVersion == 3 && settings.minorVersion == 3);
    #endif
    // Initialize GLEW
    glewExperimental = GL_TRUE;
    glewInit();
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);

    TextureHolder textureHolder;

    Core::Shader shader("Shaders/texture.vert", "Shaders/texture.frag");
    Core::Shape shape(shader, textureHolder);

    glm::mat4 modelview = glm::lookAt(glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    //glm::mat4 modelview = glm::lookAt(glm::vec3(0,0,2), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glm::mat4 projection = glm::perspective(70.0, 800.0 / 600.0, 1.0, 100.0);

    while (window.isOpen())
    {
        sf::Event windowEvent;
        while (window.pollEvent(windowEvent))
        {
            switch (windowEvent.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                default:
                    break;
            }
        }

        GLenum glErr = glGetError();
        if (glErr != GL_NO_ERROR)
        {
           std::cout << "\033[01;31mErreur " << glErr << ": \"" << gluErrorString(glErr) << "\"" << "\033[00m" << std::endl;
           //assert(glErr == GL_NO_ERROR);
        }

        // Clear the screen to black
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        //modelview = rotate(modelview, 60.0f, glm::vec3(0.0,0.0,1.0));
        shape.draw(projection, modelview);

        // Swap buffers
        window.display();
    }

}

