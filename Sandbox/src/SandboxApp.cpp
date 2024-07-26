#include <Hazel.h>
#include <imgui/imgui.h>

class ExampleLayer : public Hazel::Layer {
public:
    ExampleLayer()
        : Layer("Example") {}

    void OnUpdate() override {

        if (Hazel::Input::IsKeyPressed(HZ_KEY_TAB))
            HZ_TRACE("Key: [HZ_KEY_TAB] pressed (poll)");
    }

    void OnEvent(Hazel::Event& event) override {
        if (event.GetEventType() == Hazel::EventType::KeyPressed) {
            Hazel::KeyPressedEvent& e = (Hazel::KeyPressedEvent&)event;
            if (e.GetKeyCode() == HZ_KEY_TAB)
                HZ_TRACE("Key: [HZ_KEY_TAB] pressed (event)");
            HZ_TRACE("{0}", (char)e.GetKeyCode());
        }
    }

    virtual void OnImGuiRender() override {
        ImGui::Begin("Test");
        ImGui::Text("Hello World");
        ImGui::End();
    }
};

class Sandbox : public Hazel::Application {
public:
    Sandbox() {
        PushLayer(new ExampleLayer());
    }
    ~Sandbox() {}
};

Hazel::Application* Hazel::CreateApplication() {
    return new Sandbox();
}