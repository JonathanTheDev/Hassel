#pragma once

#include "Hassel/Layer.h"

#include "Hassel/Events/ApplicationEvent.h"
#include "Hassel/Events/KeyEvent.h"
#include "Hassel/Events/MouseEvent.h"

namespace Hassel
{
	class HASSEL_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;


		void Begin();
		void End();
	
	private:
		float m_Time = 0.0f;
	};
}