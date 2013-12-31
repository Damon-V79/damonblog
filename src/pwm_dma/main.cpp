#include "Factory.h"

auto factory = Factory();

int main() {
	auto pinA1 = factory.PWMPortA().GetPin(1);
	auto pinA3 = factory.PWMPortA().GetPin(3);

	pinA1.SetPulseWidth(0x88);
	pinA1.Set();

	pinA3.SetPulseWidth(0xAA);
	pinA3.Set();

	while (true) {
	}
}
