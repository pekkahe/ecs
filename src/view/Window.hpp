#pragma once

#include <core/Defines.hpp>

struct GLFWwindow;

namespace eng
{
	class Window : public trait::non_copyable_nor_movable
	{
	public:
		class EventListener
		{
		public:
			virtual void onKeyInput(int key, int action, int mods) {}
			virtual void onMouseButton(int button, int action, int mods) {}
			virtual void onMouseCursor(double2 position) {}
			virtual void onMouseScroll(double2 offset) {}
			virtual void onWindowResize(int2 size) {}
		};

	public:
		Window(int width, int height, const std::string& title);
		~Window();

		// The height and width of this window.
		int2 size() const;
		
		// Poll and handle events (input, window resizing, etc.)
		// Returns false if window should be closed.
		bool pollEvents();

		// Swap the front and back buffers of this window.
		void swapBuffers();

		void captureMouseCursor(bool capture);
		double2 cursorPosition() const;

		// Add an input and message event listener to this window.
		void addListener(std::shared_ptr<EventListener> listener);

	private:
		static void onKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void onMouseButton(GLFWwindow* window, int button, int action, int mods);
		static void onMouseCursor(GLFWwindow* window, double xpos, double ypos);
		static void onMouseScroll(GLFWwindow* window, double xoffset, double yoffset);
		static void onFramebufferSizeCallback(GLFWwindow* window, int width, int height);

	private:
		GLFWwindow* m_window = nullptr;
		std::vector<std::shared_ptr<EventListener>> m_eventListeners;
	};
}
