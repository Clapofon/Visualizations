#pragma once

#include <vector>
#include <string>
#include <glm.hpp>

#include "RawModel.h"
#include "Loader.h"

namespace Engine
{

	class OBJLoader 
	{
	public:

		static RawModel* loadObjModel(const std::string& fileName, Loader* loader);

	private:
		static void processVertex(std::vector<std::string> vertexData, std::vector<int> indices, std::vector<glm::vec2> textures, 
									std::vector<glm::vec3> normals, std::vector<float> textureArray, std::vector<float> normalsArray);

	};

}