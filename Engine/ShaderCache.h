#pragma once

#include "GLSLProgram.h"
#include <map>

namespace Engine
{
	class ShaderCache
	{
	public:
		ShaderCache();
		~ShaderCache();

		GLSLProgram getShader(const std::string& vertexShader, const std::string& fragmentShader);

		void unloadShader(const std::string& vertexShader, const std::string& fragmentShader);

	private:

		std::map<std::pair<std::string, std::string>, GLSLProgram> m_shaderMap;
	};

}

