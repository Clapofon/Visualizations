#pragma once

#include "RawModel.h"

#include <vector>


// @TODO: integrate loader class into resourcemanager class

namespace Engine
{
	class Loader
	{
	public:

		Loader();
		~Loader();

		RawModel* loadToVao(std::vector<float> positions, std::vector<float> textureCoords, std::vector<float> normals, std::vector<int> indices);

	private:
		GLuint createVAO();
		void storeDataInAttributeList(int numAttributes, int coordinateSize, std::vector<float> data);
		void unbindVAO();
		void cleanUp();
		void bindIndicesBuffer(std::vector<int> indices);

		std::vector<GLuint> m_vaos;
		std::vector<GLuint> m_vbos;
	};

}