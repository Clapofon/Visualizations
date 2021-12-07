#include "Loader.h"

namespace Engine
{

	Loader::Loader()
	{

	}

	Loader::~Loader()
	{
		cleanUp();
	}

	RawModel* Loader::loadToVao(std::vector<float> positions, std::vector<float> textureCoords, std::vector<float> normals, std::vector<int> indices)
	{
		GLuint vaoID = createVAO();
		bindIndicesBuffer(indices);
		storeDataInAttributeList(0, 3, positions);
		storeDataInAttributeList(1, 2, textureCoords);
		storeDataInAttributeList(2, 3, normals);
		unbindVAO();
		RawModel* rawModel = new RawModel(vaoID, indices.size());
		return rawModel;
	}

	GLuint Loader::createVAO()
	{
		GLuint vaoID;
		glGenVertexArrays(1, &vaoID);
		m_vaos.push_back(vaoID);
		glBindVertexArray(vaoID);
		return vaoID;
	}

	void Loader::storeDataInAttributeList(int numAttributes, int coordinateSize, std::vector<float> data)
	{
		GLuint vboID;
		glGenBuffers(1, &vboID);
		m_vbos.push_back(vboID);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &(data[0]), GL_STATIC_DRAW);
		glVertexAttribPointer(numAttributes, coordinateSize, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Loader::unbindVAO()
	{
		glBindVertexArray(0);
	}

	void Loader::cleanUp()
	{
		/*for (auto vao : m_vaos)
		{
			glDeleteVertexArrays(1, &vao);
		}

		for (auto vbo : m_vbos)
		{
			glDeleteBuffers(1, &vbo);
		}*/

		glDeleteVertexArrays(m_vaos.size(), m_vaos.data());
		glDeleteBuffers(m_vbos.size(), m_vbos.data());
	}
	
	void Loader::bindIndicesBuffer(std::vector<int> indices)
	{
		GLuint vboID;
		glGenBuffers(1, &vboID);
		m_vbos.push_back(vboID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), indices.data(), GL_STATIC_DRAW);
	}
}