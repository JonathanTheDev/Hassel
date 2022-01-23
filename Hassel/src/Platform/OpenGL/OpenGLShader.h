#pragma once

#include "Hassel/Renderer/Shader.h"

namespace Hassel
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader() override;

		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual void UploadUniformMat4(const std::string&, const glm::mat4& matrix) override;
		virtual void UploadUniformFloat4(const std::string& name, const glm::vec4& value) override;

	private:
		uint32_t m_RendererID = 0;

	};
}