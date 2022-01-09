#include <Hassel.h>

#include "ImGui/imgui.h"

class ExampleLayer : public Hassel::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Hassel::VertexArray::Create());

		float verticies[3 * 7] = {
			-0.5f,	-0.5f,	0.0f,	1.0f,	0.0f,	1.0f,	1.0f,
			0.5f,	-0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	1.0f,
			0.0f,	0.5f,	0.0f,	0.0f,	1.0f,	0.0f,	1.0f
		};

		std::shared_ptr<Hassel::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Hassel::VertexBuffer::Create(verticies, sizeof(verticies)));

		Hassel::BufferLayout layout = {
			{ Hassel::ShaderDataType::Float3, "a_Position" },
			{ Hassel::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indicies[3] = { 0, 1, 2 };
		std::shared_ptr<Hassel::IndexBuffer> indexBuffer;
		indexBuffer.reset(Hassel::IndexBuffer::Create(indicies, sizeof(indicies) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);


		float squareVerticies[3 * 4] = {
			-0.75f,	-0.75f,	0.0f,
			0.75f,	-0.75f,	0.0f,
			0.75f,	0.75f,	0.0f,
			-0.75f,	0.75f,	0.0f,
		};

		m_SquareVA.reset(Hassel::VertexArray::Create());
		std::shared_ptr<Hassel::VertexBuffer> squareVB;
		squareVB.reset(Hassel::VertexBuffer::Create(squareVerticies, sizeof(squareVerticies)));
		squareVB->SetLayout({
			{ Hassel::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndicies[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Hassel::IndexBuffer> squareIB;
		squareIB.reset(Hassel::IndexBuffer::Create(squareIndicies, sizeof(squareIndicies) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 460 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);

				v_Color = a_Color;
			}
		)";

		std::string fragmentSrc = R"(
			#version 460 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(Hassel::Shader::Create(vertexSrc, fragmentSrc));

		std::string blueShaderVertexSrc = R"(
			#version 460 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 460 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1);
			}
		)";

		m_BlueShader.reset(Hassel::Shader::Create(blueShaderVertexSrc, blueShaderFragmentSrc));
	}

	void OnUpdate(Hassel::Timestep ts) override
	{
		if (Hassel::Input::IsKeyPressed(HSL_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Hassel::Input::IsKeyPressed(HSL_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;
		if (Hassel::Input::IsKeyPressed(HSL_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (Hassel::Input::IsKeyPressed(HSL_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (Hassel::Input::IsKeyPressed(HSL_KEY_RIGHT_CONTROL))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		else if (Hassel::Input::IsKeyPressed(HSL_KEY_KP_0))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);


		Hassel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Hassel::RenderCommand::Clear();

		Hassel::Renderer::BeginScene(m_Camera);

		Hassel::Renderer::Submit(m_BlueShader, m_SquareVA);
		Hassel::Renderer::Submit(m_Shader, m_VertexArray);

		Hassel::Renderer::EndScene();
	}

	void OnEvent(Hassel::Event& event) override
	{
	}

	virtual void OnImGuiRender() override
	{

	}

private:
	std::shared_ptr<Hassel::Shader> m_Shader;
	std::shared_ptr<Hassel::VertexArray> m_VertexArray;

	std::shared_ptr<Hassel::Shader> m_BlueShader;
	std::shared_ptr<Hassel::VertexArray> m_SquareVA;

	Hassel::OrthographicCamera m_Camera;

	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 1.0f;
	float m_CameraRotation = 0;
	float m_CameraRotationSpeed = 25.0f;
};

class Sandbox : public Hassel::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {

	}
};

Hassel::Application* Hassel::CreateApplication()
{
	return new Sandbox();
}
