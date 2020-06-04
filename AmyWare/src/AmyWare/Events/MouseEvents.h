#pragma once

#include "Event.h"

namespace AmyWare {
	class AMYWARE_API MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(float x, float y) : m_MouseX(x), m_MouseY(y) {}

		inline float GetX() const {return m_MouseX;}
		inline float GetY() const {return m_MouseY;}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	protected:
		float m_MouseX, m_MouseY;
	};



	class AMYWARE_API MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(float xOffset, float yOffset) : m_XOffset(xOffset), m_YOffset(yOffset) {
		}

		inline float GetXOffset() const {
			return m_XOffset;
		}
		inline float GetYOffset() const {
			return m_YOffset;
		}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	protected:
		float m_XOffset, m_YOffset;
	};



	class AMYWARE_API MouseButtonEvent : public Event {
	public:
		inline int GetMouseButton() const {return m_Button;}
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	protected:
		MouseButtonEvent(int button) : m_Button(button) {}
		int m_Button;
	};



	class AMYWARE_API MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {
		}

		inline int GetButton() const {
			return m_Button;
		}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};


	class AMYWARE_API MouseButtonReleasedEvent : public MouseButtonEvent {
	public:
		MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {
		}

		inline int GetButton() const {
			return m_Button;
		}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}

