#include "App.h"

App::App() {
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 3;

    m_window = std::unique_ptr<sf::Window>(
    	new sf::Window(sf::VideoMode(800, 600, 32), "OpenGL", (sf::Style::Titlebar | sf::Style::Close), settings)
    );

    m_window->setFramerateLimit(10);
    m_window->setMouseCursorVisible(false);

    #ifndef NDEBUG
        settings = m_window->getSettings();
        assert(settings.majorVersion == 3 && settings.minorVersion == 3);
    #endif

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    glewInit();
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
}

void App::run() {

	Core::Camera camera(glm::vec3(3, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

    Core::Shader shader("Shaders/texture.vert", "Shaders/texture.frag");
    Box box(shader, m_textureHolder);

    glm::mat4 view;
    glm::mat4 projection = glm::perspective(70.0, 800.0 / 600.0, 1.0, 100.0);

    while (m_window->isOpen())
    {
        sf::Event windowEvent;
        while (m_window->pollEvent(windowEvent))
        {
            switch (windowEvent.type)
            {
                case sf::Event::Closed:
                    m_window->close();
                    break;
                case sf::Event::KeyPressed:
                	if(windowEvent.key.code == sf::Keyboard::Escape) {
                		m_window->close();
                	}
                default:
                    break;
            }
        }

        GLenum glErr = glGetError();
        if (glErr != GL_NO_ERROR)
        {
           std::cout << "\033[01;31mErreur " << glErr << ": \"" << gluErrorString(glErr) << "\"" << "\033[00m" << std::endl;
        }

        camera.move();
    	camera.lookAt(view);

        // Clear the screen to black
        glClearColor(0.0f, 0.6f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        box.draw(projection, view);

        // Swap buffers
        m_window->display();
    }
}

App::~App() {
}