#pragma once

#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:

	// Constructor generates the shader
	Shader()
	{
		// Vertex Shader
		const GLchar* vShaderCode = "#version 330 core\n\
		layout(location = 0) in vec2 in_Position;\n\
		layout(location = 1) in vec2 in_TextureCoord;\n\
		layout(location = 2) in vec2 in_UV;\n\
		layout(location = 3) in vec3 in_Zoom;\n\
		out vec2 out_TextureCoord;\n\
		out vec2 vTextureCoordOffset;\n\
		out vec2 vZoom; \n\
		out float alpha; \n\
		void main()\n\
		{\n\
			alpha = in_Zoom.z;\n\
			vZoom = vec2(in_Zoom.x, in_Zoom.y);\n\
			vTextureCoordOffset = in_UV;\n\
			gl_Position = vec4(in_Position.x, in_Position.y, 0.0f, 1.0f);\n\
			out_TextureCoord = in_TextureCoord;\n\
		}";

		// Fragment Shader
		const GLchar* fShaderCode = "#version 330 core\n\
			uniform sampler2D texture_diffuse;\n\
		in vec2 out_TextureCoord;\n\
		in vec2 vTextureCoordOffset;\n\
		in vec2 vZoom;\n\
		in float alpha;\n\
		out vec4 color;\n\
		void main()\n\
		{\n\
			vec4 tex = texture2D(texture_diffuse, fract(out_TextureCoord) * vZoom + vTextureCoordOffset);\n\
			color = tex * alpha;\n\
		}";

		// Compile Shaders
		GLuint vertex, fragment;

		// Vertex Shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");

		// Fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "FRAGMENT");

		// Shader Program
		this->Program = glCreateProgram();
		glAttachShader(this->Program, vertex);
		glAttachShader(this->Program, fragment);
		glLinkProgram(this->Program);
		checkCompileErrors(this->Program, "PROGRAM");

		// Delete the shaders because they're linked now
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	// Use the current shader
	void Use() { glUseProgram(this->Program); }

private:
	GLuint Program;
	void checkCompileErrors(GLuint shader, std::string type)
	{
		GLint success;
		GLchar infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "| ERROR::::SHADER-COMPILATION-ERROR of type: " << type << "|\n" << infoLog << "\n| -- --------------------------------------------------- -- |" << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "| ERROR::::PROGRAM-LINKING-ERROR of type: " << type << "|\n" << infoLog << "\n| -- --------------------------------------------------- -- |" << std::endl;
			}
		}
	}
};