#include "Sandbox2D.h"

#include <Platform/OpenGL/OpenGLShader.h>

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f) {
	//
}

void Sandbox2D::OnAttach() {
	m_VertexArray = Hazel::VertexArray::Create();

	float vertices[4 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
	};

	Hazel::Ref<Hazel::VertexBuffer> vertexBuffer;
	vertexBuffer = Hazel::VertexBuffer::Create(vertices, sizeof(vertices));

	vertexBuffer->SetLayout({
		{ Hazel::ShaderDataType::Float3, "a_Position" }
	});

	m_VertexArray->AddVertexBuffer(vertexBuffer);

	uint32_t indices[6] = {
			0, 1, 2,
			2, 3, 0
	};

	Hazel::Ref<Hazel::IndexBuffer> indexBuffer;
	indexBuffer = Hazel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

	m_VertexArray->SetIndexBuffer(indexBuffer);

	m_Shader = Hazel::Shader::Create("assets/shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach() {
	//
}

void Sandbox2D::OnUpdate(Hazel::Timestep ts) {
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	Hazel::RenderCommand::SetClearColor({ 0.2, 0.2, 0.2, 1.0 });
	Hazel::RenderCommand::Clear();

	Hazel::Renderer::BeginScene(m_CameraController.GetCamera());

	std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_Shader)->Bind();
	std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_Shader)->UploadUniformFloat3("u_Color", m_SquareColor);

	Hazel::Renderer::Submit(m_Shader, m_VertexArray, glm::mat4(1.0f));

	Hazel::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender() {
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Sq Col", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Hazel::Event& e) {
	m_CameraController.OnEvent(e);
}