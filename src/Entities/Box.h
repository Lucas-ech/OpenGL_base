#ifndef BOX_H
#define BOX_H

#include "../Core/Shape.h"
#include "../Core/Headers.h"
#include "../Core/Shader.h"
#include "../Core/ResourceHolder.h"
#include "../ResourceIdentifiers.h"

class Box: public Core::Shape {

	public:
		Box(Core::Shader shader, TextureHolder &textureHolder);
		~Box();

	private:

};

#endif //BOX_H