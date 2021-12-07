#pragma once

#include <glew.h>
#include <glm.hpp>

#include <string>
namespace Engine
{
    class GLSLProgram
    {
    public:
        GLSLProgram();
        ~GLSLProgram();

        void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
        void linkShaders();
        void addAttribute(const std::string& attributeName);

        GLint getUniformLocation(const std::string& uniformName);

        void loadFloat(GLuint location, GLfloat a);
        void loadVector3f(GLuint location, glm::vec3 a);
        void loadInt(GLuint location, GLint a);
        void loadMat4(GLuint location, glm::mat4 mat);

        void start();
        void stop();

    protected:
        void compileShader(const std::string& filePath, GLuint ID);

        int m_numAttributes;

        GLuint m_programID;
        GLuint m_vertexShaderID;
        GLuint m_fragmentShaderID;
    };
}
