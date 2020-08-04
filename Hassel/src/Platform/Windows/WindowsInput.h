#pragma once

#include "Hassel/Input.h"

namespace Hassel
{

	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;
		
		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
		virtual std::tuple<float, float> GetMousePositionImpl() override;

	};

}