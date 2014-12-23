#ifndef APP_H
#define APP_H

#include <memory>
#include "Core/Shader.h"
#include "Entities/Box.h"
#include "Core/ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "Core/Camera.h"

class App
{

	public:
		App();
		void run();
		~App();

	private:
		std::unique_ptr<sf::Window> m_window;
		TextureHolder m_textureHolder;

};

#endif //APP_H
