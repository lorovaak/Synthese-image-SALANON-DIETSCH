#pragma once

#include <string>
#include <unordered_map>

#include "glm/glm.hpp"

class Shader {
public:
	Shader(const std::string& filepathVertex, const std::string& filepathFragment);
	~Shader();

	void bind() const;
	void unbind() const;

	void setUniform1i(const std::string& name, int value);
	void setUniform1f(const std::string& name, float v0);
	void setUniform2f(const std::string& name, float v0, float v1);
	void setUniform3f(const std::string& name, float v0, float v1, float v2);
	void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void setUniform4f(const std::string& name, glm::vec4 v);
	void setUniformMat4f(const std::string& name, const glm::mat4 matrix);

private:
	std::string parseShader(const std::string& filepath);
	unsigned int compileShader(unsigned int type, const std::string& source);
	unsigned int createPipeline(const std::string& vertexShader, const std::string& fragmentShader);
	int getUniformLocation(const std::string& name);

private:
	std::string m_filePathVertex;
	std::string m_filePathFragment;
	unsigned int m_rendererID;
	std::unordered_map<std::string, int> m_uniformLocationCache;
};
