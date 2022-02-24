#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <stb_image.h>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace graphics
{
	class Shader
	{
	private:
		void checkCompileErrors(unsigned int shader, std::string type);
	public:
		// The program ID
		unsigned int ID;
		unsigned int m_Texture;
		// Constructor reads and builds the shader
		Shader(const char* vertexPath, const char* fragmentPath);
		~Shader() {  }
		// use/activate shader
		void use();
		void bind();
		// utility to load textures
		unsigned int loadAndGenerateTexture(const char* filePath);
		// utility uniform functions
		void setBool(const std::string& name, bool value) const;
		void setInt(const std::string& name, int value) const;
		void setFloat(const std::string& name, float value) const;

		void setVec2(const std::string& name, const glm::vec2& value) const;
		void setVec2(const std::string& name, float x, float y) const;
		void setVec3(const std::string& name, const glm::vec3& value) const;
		void setVec3(const std::string& name, float x, float y, float z) const;
		void setVec4(const std::string& name, const glm::vec4& value) const;
		void setVec4(const std::string& name, float x, float y, float z, float w) const;

		void setMat2(const std::string& name, glm::mat2& mat) const;
		void setMat3(const std::string& name, glm::mat3& mat) const;
		void setMat4(const std::string& name, glm::mat4& mat) const;
	};

}
#endif
