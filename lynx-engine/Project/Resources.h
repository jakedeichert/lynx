#pragma once
#include <string>
#include "Texture.h"
#include "Mesh.h"
#include "Shader.h"

namespace lynx {
	/**
	 * Resources...
	 *
	 * This is a special global + anonymous namespace. This is better than a static class layout
	 * apparently. Basically, the first anonymous namespace holds global variables that no one can
	 * access except the Log namespace below. This is safer than having private variables in a class
	 * full of static methods I guess.
	 * http://stackoverflow.com/questions/9321/how-do-you-create-a-static-class-in-c
	 */
	namespace Resources {

		/**
		 * Initialize Resources. Should be initialized as soon as possible.
		 */
		void init();


		/**
		 * Gets a texture from the specified filepath. Loads it if it hasn't already been loaded.
		 * @param filepath The path to the texture file
		 * @return Returns a pointer to the texture
		 */
		Texture* getTexture(std::string filepath);


		Mesh* getMesh(std::string filepath);


		Shader* getShader(std::string shaderName);


		void createMesh(std::string meshName, std::vector<GLfloat> vertices, std::vector<GLuint> elements);


		void loadShader(std::string shaderName, std::string vertexFilepath, std::string fragmentFilepath);


	}
}
