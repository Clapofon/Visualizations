#include "ShaderCache.h"


namespace Engine
{
	ShaderCache::ShaderCache()
	{}

	ShaderCache::~ShaderCache()
	{
		for (std::map<std::pair<std::string, std::string>, GLSLProgram>::iterator mit = m_shaderMap.begin(); mit != m_shaderMap.end();)
		{
			m_shaderMap.erase(mit++);
		}
		printf("Unloaded all shaders\n");
	}

	GLSLProgram ShaderCache::getShader(const std::string& vertexShader, const std::string& fragmentShader)
	{
		std::map<std::pair<std::string, std::string>, GLSLProgram>::iterator mit;

		mit = m_shaderMap.find(make_pair(vertexShader, fragmentShader));

		if (mit == m_shaderMap.end())
		{
			printf("Loading shader: %s, %s ... ", vertexShader.c_str(), fragmentShader.c_str());
			GLSLProgram shader;
			shader.compileShaders(vertexShader, fragmentShader);
			shader.addAttribute("vertexPosition");
			shader.addAttribute("vertexColor");
			shader.addAttribute("vertexUV");
			shader.linkShaders();

			m_shaderMap.insert(make_pair(make_pair(vertexShader, vertexShader), shader));
			printf("  Loaded.\n");
			return shader;
		}
		return mit->second;
	}

	void ShaderCache::unloadShader(const std::string& vertexShader, const std::string& fragmentShader)
	{
		std::map<std::pair<std::string, std::string>, GLSLProgram>::iterator mit;
		mit = m_shaderMap.find(make_pair(vertexShader, fragmentShader));

		if (mit != m_shaderMap.end())
		{
			m_shaderMap.erase(mit);
		}
	}
}