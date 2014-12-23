#ifndef CAMERA_H
#define CAMERA_H

#include "Headers.h"
#include "Mouse.cpp" ////////!!!

namespace Core {
	class Camera {

		public:
			Camera();
			Camera(glm::vec3 position, glm::vec3 target, glm::vec3 verticalAxis);
			~Camera();
			void orient(sf::Vector2i localPosition);
			void move();
			void lookAt(glm::mat4 &view);

		private:
			float m_phi;
			float m_theta;
			glm::vec3 m_orientation;
			glm::vec3 m_verticalAxis;
			glm::vec3 m_sideshift;
			glm::vec3 m_position;
			glm::vec3 m_target;
			Core::Mouse m_mouse;

	};
}

#endif //CAMERA_H