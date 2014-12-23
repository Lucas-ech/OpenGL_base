#include "Camera.h"

namespace Core
{
	Camera::Camera()
	: m_phi(0.0f), m_theta(0.0f), m_orientation(), m_verticalAxis(0, 0, 1), m_sideshift(), m_position(), m_target(), m_mouse()
	{
	}


	Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 verticalAxis)
	: m_phi(-35.26f), m_theta(-135.0f), m_orientation(), m_verticalAxis(verticalAxis), m_sideshift(), m_position(position), m_target(target)
	{
	}


	Camera::~Camera()
	{
	}


	void Camera::orient(sf::Vector2i position)
	{
		// Récupération des angles
		m_phi -= static_cast<float>(position.y) * 0.5f;
		m_theta -= static_cast<float>(position.x) * 0.5f;

		// Limitation de l'angle phi
	    if(m_phi > 89.0f) {
	        m_phi = 89.0f;
	    } else if(m_phi < -89.0f) {
	        m_phi = -89.0f;
	    }

	    // Conversion des angles en radian
	    float phiRadian = m_phi * static_cast<float>(M_PI) / 180.0f;
		float thetaRadian = m_theta * static_cast<float>(M_PI) / 180.0f;

	    // Calcul des coordonnées sphériques
		if(m_verticalAxis.x == 1.0f) { // Si l'axe vertical est l'axe X
		    m_orientation.x = sinf(phiRadian);
		    m_orientation.y = cosf(phiRadian) * cosf(thetaRadian);
		    m_orientation.z = cosf(phiRadian) * sinf(thetaRadian);
		} else if(m_verticalAxis.y == 1.0f) { // Si c'est l'axe Y
		    m_orientation.x = cosf(phiRadian) * sinf(thetaRadian);
		    m_orientation.y = sinf(phiRadian);
		    m_orientation.z = cosf(phiRadian) * cosf(thetaRadian);
		} else { // Sinon c'est l'axe Z
		    m_orientation.x = cosf(phiRadian) * cosf(thetaRadian);
		    m_orientation.y = cosf(phiRadian) * sinf(thetaRadian);
		    m_orientation.z = sinf(phiRadian);
		}

		// Calcul de la normale
		m_sideshift = cross(m_verticalAxis, m_orientation);
		m_sideshift = normalize(m_sideshift);
		m_target = m_position + m_orientation;
	}


	void Camera::move()
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			m_position = m_position + m_orientation * 0.5f;
			m_target = m_position + m_orientation;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			m_position = m_position - m_orientation * 0.5f;
			m_target = m_position + m_orientation;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			m_position = m_position + m_sideshift * 0.5f;
			m_target = m_position + m_orientation;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			m_position = m_position - m_sideshift * 0.5f;
			m_target = m_position + m_orientation;
		}
		orient(m_mouse.getRelativePosition());
	}


	void Camera::lookAt(glm::mat4 &view)
	{
		// Actualisation de la vue dans la matrice
	    view = glm::lookAt(m_position, m_target, m_verticalAxis);
	}
}
