#include "hslpch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Hassel
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}