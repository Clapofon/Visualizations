#include "GLSLProgram.h"

#include "Error.h"

#include <fstream>
#include <vector>

namespace Engine
{
    GLSLProgram::GLSLProgram() : m_numAttributes(0), m_programID(0), m_vertexShaderID(0), m_fragmentShaderID(0)
    {}

    GLSLProgram::~GLSLProgram()
    {}

    void GLSLProgram::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
    {
        m_programID = glCreateProgram();

        m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        if (m_vertexShaderID == 0)
        {
            fatalError("Couldn't create Vertex Shader");
        }

        m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
        if (m_fragmentShaderID == 0)
        {
            fatalError("Couldn't create Fragment Shader");
        }

        compileShader(vertexShaderFilePath, m_vertexShaderID);
        compileShader(fragmentShaderFilePath, m_fragmentShaderID);
    }

    void GLSLProgram::linkShaders()
    {
        glAttachShader(m_programID, m_vertexShaderID);
        glAttachShader(m_programID, m_fragmentShaderID);

        glLinkProgram(m_programID);

        GLint isLinked = 0;
        glGetProgramiv(m_programID, GL_LINK_STATUS, (int *)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> errorLog(maxLength);
            glGetProgramInfoLog(m_programID, maxLength, &maxLength, &errorLog[0]);

            // We don't need the program anymore.
            glDeleteProgram(m_programID);

            // Don't leak shaders either.
            glDeleteShader(m_vertexShaderID);
            glDeleteShader(m_fragmentShaderID);

            fatalError("Failed to link shaders!");
            std::printf("%s\n" , &(errorLog[0]));

        }

        // Always detach shaders after a successful link.
        glDetachShader(m_programID, m_vertexShaderID);
        glDetachShader(m_programID, m_fragmentShaderID);
        glDeleteShader(m_vertexShaderID);
        glDeleteShader(m_fragmentShaderID);
    }

    void GLSLProgram::compileShader(const std::string& filePath, GLuint ID)
    {
        std::ifstream shaderFile(filePath);
        if (shaderFile.fail())
        {
            fatalError("Couldn't open " + filePath);
            perror(filePath.c_str());
        }

        std::string fileContents = "";
        std::string line;

        while (std::getline(shaderFile, line))
        {
            fileContents += line + "\n";
        }

        shaderFile.close();

        const char* contents = fileContents.c_str();
        glShaderSource(ID, 1, &contents, nullptr);

        glCompileShader(ID);
        GLint success = 0;
        glGetShaderiv(ID, GL_COMPILE_STATUS, &success);

        if (success == 0)
        {
            GLint maxLength = 0;
            glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<char> errorLog(maxLength);
            glGetShaderInfoLog(ID, maxLength, &maxLength, &errorLog[0]);

            std::printf("%s\n" , &(errorLog[0]));
            fatalError(filePath + " failed to compile!");

            glDeleteShader(ID);

        }
    }

    void GLSLProgram::addAttribute(const std::string& attributeName)
    {
        glBindAttribLocation(m_programID, m_numAttributes++, attributeName.c_str());
    }

    GLint GLSLProgram::getUniformLocation(const std::string& uniformName)
    {
        GLuint location = glGetUniformLocation(m_programID, uniformName.c_str());
        if (location == GL_INVALID_INDEX)
        {
            fatalError("Uniform '" + uniformName + "' not found in shader!");
        }
        return location;
    }

    void GLSLProgram::loadFloat(GLuint location, GLfloat a)
    {
        glUniform1f(location, a);
    }

    void GLSLProgram::loadVector3f(GLuint location, glm::vec3 a)
    {
        glUniform3f(location, a.x, a.y, a.z);
    }

    void GLSLProgram::loadInt(GLuint location, GLint a)
    {
        glUniform1f(location, a);
    }

    void GLSLProgram::loadMat4(GLuint location, glm::mat4 mat)
    {
        glUniformMatrix4fv(location, 1, GL_FALSE, &(mat[0][0]));
    }

    void GLSLProgram::start()
    {
        glUseProgram(m_programID);

        for (int i=0; i<m_numAttributes; i++)
        {
            glEnableVertexAttribArray(i);
        }
    }

    void GLSLProgram::stop()
    {
        glUseProgram(0);

        for (int i=0; i<m_numAttributes; i++)
        {
            glDisableVertexAttribArray(i);
        }
    }
}



















