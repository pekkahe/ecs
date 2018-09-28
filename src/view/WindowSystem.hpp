#pragma once

#include <core/Defines.hpp>
#include <view/Window.hpp>

namespace eng
{
	class Window;
	class WindowSystem
	{
	public:
		WindowSystem();
		~WindowSystem();

		std::shared_ptr<Window> createWindow(int width, int height, const std::string& title);
		std::shared_ptr<Window> mainWindow() const;

	private:
		std::vector<std::shared_ptr<Window>> m_windows;
	};
}

