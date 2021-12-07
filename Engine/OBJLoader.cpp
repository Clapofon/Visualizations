#include "OBJLoader.h"

#include "StringUtil.h"
#include <fstream>

namespace Engine
{
	 RawModel* OBJLoader::loadObjModel(const std::string& fileName, Loader* loader) {

		std::ifstream objFile(fileName);
		if (objFile.fail())
		{
			printf("Couldn't open: %s", fileName.c_str());
			perror(fileName.c_str());
		}

		std::string line;
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec2> textures;
		std::vector<glm::vec3> normals;
		std::vector<int> indices;
		std::vector<float> verticesArray;
		std::vector<float> normalsArray;
		std::vector<float> textureArray;
		std::vector<int> indicesArray;

		while (true) 
		{
			std::getline(objFile, line);
			std::vector<std::string> currentLine(4);
			currentLine = String::split(line, ' ');
			if (line.find("v ", 0) == 0) 
			{
				glm::vec3 vertex = glm::vec3((float)std::stof(currentLine[1]), (float)std::stof(currentLine[2]), (float)std::stof(currentLine[3]));
				vertices.push_back(vertex);
			}
			else if (line.find("vt ") == 0) 
			{
				glm::vec2 texture = glm::vec2((float)std::stof(currentLine[1]), (float)std::stof(currentLine[2]));
				textures.push_back(texture);
			}
			else if (line.find("vn ") == 0) 
			{
				glm::vec3 normal = glm::vec3((float)std::stof(currentLine[1]), (float)std::stof(currentLine[2]), (float)std::stof(currentLine[3]));
				normals.push_back(normal);
			}
			else if (line.find("f ") == 0) 
			{
				textureArray.resize(vertices.size() * 2); // = new float[vertices.size() * 2];
				normalsArray.resize(vertices.size() * 3); // = new float[vertices.size() * 3];
				break;
			}
		}
		
		while (line != "") 
		{
			if (!line.find("f ") == 0) 
			{
				std::getline(objFile, line);
				continue;
			}
			std::vector<std::string> currentLine = String::split(line, ' ');
			std::vector<std::string> vertex1 = String::split(currentLine[1], '/');
			std::vector<std::string> vertex2 = String::split(currentLine[2], '/');
			std::vector<std::string> vertex3 = String::split(currentLine[3], '/');

			processVertex(vertex1, indices, textures, normals, textureArray, normalsArray);
			processVertex(vertex2, indices, textures, normals, textureArray, normalsArray);
			processVertex(vertex3, indices, textures, normals, textureArray, normalsArray);
			std::getline(objFile, line);
		}
		objFile.close();

		verticesArray.resize(vertices.size() * 3); // [vertices.size() * 3] ;
		indicesArray.resize(indices.size()); //[indices.size()];

		int vertexPointer = 0;
		for (glm::vec3 vertex : vertices) {
			verticesArray[vertexPointer++] = vertex.x;
			verticesArray[vertexPointer++] = vertex.y;
			verticesArray[vertexPointer++] = vertex.z;
		}

		for (int i = 0; i < indices.size(); i++) {
			indicesArray[i] = indices[i];
		}
		printf("Loaded mesh: %s\n", fileName.c_str());
		return loader->loadToVao(verticesArray, textureArray, normalsArray, indicesArray);
	}

	 void OBJLoader::processVertex(std::vector<std::string> vertexData, std::vector<int> indices, std::vector<glm::vec2> textures, std::vector<glm::vec3> normals, 
										std::vector<float> textureArray, std::vector<float> normalsArray) 
	 {
		int currentVertexPointer = std::stoi(vertexData[0]) - 1;
		indices.push_back(currentVertexPointer);
		glm::vec2 currentTex = textures[std::stoi(vertexData[1]) - 1];
		textureArray[currentVertexPointer * 2] = currentTex.x;
		textureArray[currentVertexPointer * 2 + 1] = 1 - currentTex.y;
		glm::vec3 currentNorm = normals[stoi(vertexData[2]) - 1];
		normalsArray[currentVertexPointer * 3] = currentNorm.x;
		normalsArray[currentVertexPointer * 3 + 1] = currentNorm.y;
		normalsArray[currentVertexPointer * 3 + 2] = currentNorm.z;
	}
}