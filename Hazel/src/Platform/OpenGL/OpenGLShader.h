#pragma once

#include <string>

#include "Hazel/Renderer/Shader.h"

namespace Hazel {

	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void UploadUniformInt(const std::string& name, const int& value);

		virtual void UploadUniformFloat(const std::string& name, const float& value);
		virtual void UploadUniformFloat2(const std::string& name, const glm::vec2& values);
		virtual void UploadUniformFloat3(const std::string& name, const glm::vec3& values);
		virtual void UploadUniformFloat4(const std::string& name, const glm::vec4& values);

		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
		virtual void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		virtual void UploadUniformMat2(const std::string& name, const glm::mat2& matrix);
	private:
		uint32_t m_RendererID;
	};

}