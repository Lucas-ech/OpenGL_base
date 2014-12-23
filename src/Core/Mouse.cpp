#include "Mouse.h"

namespace Core
{
	Mouse::Mouse(): m_lastPosition(getPosition())
	{
	}


	sf::Vector2i Mouse::getRelativePosition() {
		m_relativePosition = getPosition() - m_lastPosition;
		m_lastPosition = getPosition();
		return m_relativePosition;
	}
}
