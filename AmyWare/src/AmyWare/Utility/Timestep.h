#pragma once


namespace AmyWare {
	class Timestep {
	public:
		Timestep(float time = 0.0f) {
			this->time = time;
		}

		operator float() const { return time; }

		float GetSeconds() const { return time; }
		float GetMilliseconds() const { return time * 1000.0f; }
	private:
		float time;
	};
}
