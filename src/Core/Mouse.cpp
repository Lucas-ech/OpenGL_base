#ifndef MOUSE_H
#define MOUSE_H

#include "Headers.h"
#include <iostream>

namespace Core {
	class Mouse: sf::Mouse {

		public:
			Mouse(): m_lastPosition(getPosition()){}
			sf::Vector2i getRelativePosition() {
				m_relativePosition = getPosition() - m_lastPosition;
				m_lastPosition = getPosition();
				return m_relativePosition;
			}

			sf::Vector2i m_lastPosition;
			sf::Vector2i m_relativePosition;

	};

}

#endif //MOUSE_H