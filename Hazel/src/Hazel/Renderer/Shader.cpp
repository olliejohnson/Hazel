#include "hzpch.h"
#include "Shader.h"

#include "Hazel/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Hazel {

	Shader* Shader::Create(std::string& vertexSrc, std::string& fragmentSrc) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None: HZ_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}