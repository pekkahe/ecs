#pragma once

#include <core/Defines.hpp>

struct GLFWwindow;

namespace eng
{
	class Window
	{
	public:
		class EventListener
		{
		public:
			virtual void onKeyPress(int keyCode) {}
			virtual void onMouseCursor(double2 position) {}
			virtual void onMouseScroll(double2 offset) {}
			virtual void onWindowResize(int2 size) {}
		};

	public:
		Window(GLFWwindow* glfwWindow);
		~Window();
		
		// Always held by pointer.
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;
		Window(Window&&) = delete;
		Window& operator=(Window&&) = delete;

		// The height and width of this window.
		int2 size() const;
		// Check the close flag of this window.
		bool shouldClose() const;

		// Polls and processes window and input events.
		void pollEvents();
		// Swap the front and back buffers of this window.
		void swapBuffers();

		// Add an input and message event listener to this window.
		void addListener(std::shared_ptr<EventListener> listener);

	private:
		static void onKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void onMouseCursor(GLFWwindow* window, double xpos, double ypos);
		static void onMouseScroll(GLFWwindow* window, double xoffset, double yoffset);
		static void onFramebufferSizeCallback(GLFWwindow* window, int width, int height);

	private:
		GLFWwindow* m_glfwWindow = nullptr;
		std::vector<std::shared_ptr<EventListener>> m_eventListeners;
	};
}
