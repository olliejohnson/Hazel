#include <Hazel.h>
#include <Hazel/Core/EntryPoint.h>
#include <imgui/imgui.h>

#include <Platform/OpenGL/OpenGLShader.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"

class ExampleLayer : public Hazel::Layer {
public:
    ExampleLayer()
        : Layer("Example"), m_CameraController(1280.0f / 720.0f) {
        m_VertexArray = Hazel::VertexArray::Create();

        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
        };

        Hazel::Ref<Hazel::VertexBuffer> vertexBuffer;
        vertexBuffer = Hazel::VertexBuffer::Create(vertices, sizeof(vertices));


        Hazel::BufferLayout layout = {
            { Hazel::ShaderDataType::Float3, "a_Position" },
            { Hazel::ShaderDataType::Float4, "a_Color" }
        };

        vertexBuffer->SetLayout(layout);

        m_VertexArray->AddVertexBuffer(vertexBuffer);

        uint32_t indices[6] = {
            0, 1, 2
        };

        Hazel::Ref<Hazel::IndexBuffer> indexBuffer;
        indexBuffer = Hazel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

        m_VertexArray->SetIndexBuffer(indexBuffer);

        m_SquareVertexArray = Hazel::VertexArray::Create();

        float sq_vertices[4 * 5] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
        };

        Hazel::Ref<Hazel::VertexBuffer> SquareVB;
        SquareVB = Hazel::VertexBuffer::Create(sq_vertices, sizeof(sq_vertices));

        SquareVB->SetLayout({
            { Hazel::ShaderDataType::Float3, "a_Position" },
            { Hazel::ShaderDataType::Float2, "a_TexCoord" }
        });

        m_SquareVertexArray->AddVertexBuffer(SquareVB);

        uint32_t sq_indices[6] = {
            0, 1, 2,
            2, 3, 0
        };

        Hazel::Ref<Hazel::IndexBuffer> SquareIB;
        SquareIB = Hazel::IndexBuffer::Create(sq_indices, sizeof(sq_indices) / sizeof(uint32_t));

        m_SquareVertexArray->SetIndexBuffer(SquareIB);

        m_ShaderLibrary.Load("assets/shaders/VertexPosColor.glsl");
        m_ShaderLibrary.Load("assets/shaders/FlatColor.glsl");
        auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

        m_Texture = Hazel::Texture2D::Create("assets/textures/Checkerboard.png");
        m_ChernoLogoTexture = Hazel::Texture2D::Create("assets/textures/ChernoLogo.png");

        std::dynamic_pointer_cast<Hazel::OpenGLShader>(textureShader)->Bind();
        std::dynamic_pointer_cast<Hazel::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
    }

    void OnUpdate(Hazel::Timestep ts) override {
        m_CameraController.OnUpdate(ts);

        Hazel::RenderCommand::SetClearColor({ 0.1, 0.1, 0.1, 1.0 });
        Hazel::RenderCommand::Clear();

        Hazel::Renderer::BeginScene(m_CameraController.GetCamera());
        
        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

        // Material API
        // Hazel::MaterialRef material = new Hazel::Material(m_FlatColorShader);
        // Hazel::MaterialInstanceRef mi = new Hazel::MaterialInstance(material);
        // 
        // mi->SetValue("m_Color", glm::vec4(color1[0], color1[1], color1[2], color1[3]));
        // mi->SetTexture("u_AlbedoMap", texture);
        // squareMesh->SetMaterial(mi);

        auto flatColorShader = m_ShaderLibrary.Get("FlatColor");

        std::dynamic_pointer_cast<Hazel::OpenGLShader>(flatColorShader)->Bind();
        std::dynamic_pointer_cast<Hazel::OpenGLShader>(flatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

        for (int x = 0; x < 20; x++) {
            for (int y = 0; y < 20; y++) {
                glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
                // Material API
                // Hazel::Renderer::Submit(mi, m_SquareVertexArray, transform);
                Hazel::Renderer::Submit(flatColorShader, m_SquareVertexArray, transform);
            }
        }

        auto textureShader = m_ShaderLibrary.Get("Texture");

        m_Texture->Bind();
        Hazel::Renderer::Submit(textureShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
        m_ChernoLogoTexture->Bind();
        Hazel::Renderer::Submit(textureShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

        // Triangle
        // Hazel::Renderer::Submit(m_Shader, m_VertexArray);

        Hazel::Renderer::EndScene();
    }

    void OnEvent(Hazel::Event& event) override {
        m_CameraController.OnEvent(event);
    }

    virtual void OnImGuiRender() override {
        ImGui::Begin("Settings");
        ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
        ImGui::End();
    }
private:
    Hazel::ShaderLibrary m_ShaderLibrary;
    Hazel::Ref<Hazel::VertexArray> m_VertexArray;
    Hazel::Ref<Hazel::VertexArray> m_SquareVertexArray;

    Hazel::Ref<Hazel::Texture2D> m_Texture, m_ChernoLogoTexture;

    Hazel::OrthographicCameraController m_CameraController;

    glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public Hazel::Application {
public:
    Sandbox() {
        // PushLayer(new ExampleLayer());
        PushLayer(new Sandbox2D());
    }
    ~Sandbox() {}
};

Hazel::Application* Hazel::CreateApplication() {
    return new Sandbox();
}