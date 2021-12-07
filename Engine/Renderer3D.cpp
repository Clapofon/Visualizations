#include "Renderer3D.h"

#include "Math.h"

namespace Engine
{

	Renderer3D::Renderer3D(GLSLProgram shader)
	{
		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_BACK);
	}

	Renderer3D::~Renderer3D()
	{

	}

	void Renderer3D::prepare()
	{
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer3D::render(Entity entity, GLSLProgram shader, Light* light, Camera3D* camera)
	{
		TexturedModel* texturedModel = entity.getModel();
		RawModel* model = texturedModel->getModel();
		glBindVertexArray(model->getVaoID());
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texturedModel->getTexture().id);
		glDrawElements(GL_TRIANGLES, model->getVertexCount(), GL_UNSIGNED_INT, 0);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glBindVertexArray(0);
	}
}