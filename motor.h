#ifndef MOTOR_H
#define MOTOR_H
#include <arduino.h>

class motor {
	private:
		int relay1, relay2;
	public:
		motor(int pin1, int pin2);
		bool toggle(bool state, bool SS);
};
#endif
