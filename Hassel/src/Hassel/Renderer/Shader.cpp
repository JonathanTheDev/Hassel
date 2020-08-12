#include "hslpch.h"

#include "Shader.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Hassel
{
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:		HSL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
		case RendererAPI::OpenGL:	return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		HSL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}