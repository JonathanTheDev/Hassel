#include <Hassel.h>

#include "ImGui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>

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
			-0.5f,	-0.5f,	0.0f,
			0.5f,	-0.5f,	0.0f,
			0.5f,	0.5f,	0.0f,
			-0.5f,	0.5f,	0.0f,
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
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform  * vec4(a_Position, 1.0);

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

		std::string flatColorShaderVertexSrc = R"(
			#version 460 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 460 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			
			uniform vec4 u_Color;

			void main()
			{
				color = u_Color;
			}
		)";

		m_FlatColorShader.reset(Hassel::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));
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

		glm::mat4 squareScale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		Hassel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Hassel::RenderCommand::Clear();

		Hassel::Renderer::BeginScene(m_Camera);

		glm::vec4 blueColor = { 0.2f, 0.3f, 0.8f, 1.0f };
		glm::vec4 redColor = { 0.8f, 0.2f, 0.3f, 1.0f};

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 position(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 squareTransform = glm::translate(glm::mat4(1.0f), position) * squareScale;
				if (x % 2 == 0)
					m_FlatColorShader->UploadUniformFloat4("u_Color", redColor);
				else
					m_FlatColorShader->UploadUniformFloat4("u_Color", blueColor);

				Hassel::Renderer::Submit(m_FlatColorShader, m_SquareVA, squareTransform);
			}
		}

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

	std::shared_ptr<Hassel::Shader> m_FlatColorShader;
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
