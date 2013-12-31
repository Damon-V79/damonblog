/*
 * PWMDMAOut.h
 *
 *  Created on: 21.11.2013
 *      Author: damon
 */

#ifndef PWMDMAOUT_H_
#define PWMDMAOUT_H_

template<class STREAM, class PORT, int LENGTH>
class PWMDMAPortOut;

template<class PORTOUT>
class PWMDMAPinOut {
	friend class PWMDMAPortOut<typename PORTOUT::Stream_t,
			typename PORTOUT::Port_t, PORTOUT::Length> ;
public:
	typedef typename PORTOUT::WordLen_t WordLen_t;
	enum {
		Length = PORTOUT::Length
	};

	PWMDMAPinOut(unsigned char pinNum, PORTOUT &portOut) :
			_portOut(portOut), _pinNum(pinNum), _pulseWidth(0), _isSet(false) {
	}

	void Clear() {
		_portOut._data[_pinNum] = 0;
		_portOut.Apply();
	}

	void Set() {
		_portOut._data[_pinNum] = _pulseWidth;
		_portOut.Apply();
	}

	void Toggle() {
		if (_isSet)
			Clear();
		else
			Set();
		_isSet = !_isSet;
	}

	WordLen_t GetPulseWidth() {
		return _pulseWidth;
	}

	void SetPulseWidth(WordLen_t pulseWidth) {
		_pulseWidth = pulseWidth;
		Set();
	}

private:
	PORTOUT &_portOut;
	unsigned char _pinNum;
	WordLen_t _pulseWidth;
	bool _isSet;

};

template<class STREAM, class PORT, int LENGTH>
class PWMDMAPortOut {
public:
	friend class PWMDMAPinOut<PWMDMAPortOut<STREAM, PORT, LENGTH> > ;

	typedef STREAM Stream_t;
	typedef PORT Port_t;
	typedef unsigned int WordLen_t;
	typedef PWMDMAPinOut<PWMDMAPortOut<STREAM, PORT, LENGTH> > Pin_t;

	enum {
		Pins = 16, Length = LENGTH
	};

	PWMDMAPortOut(STREAM &stream, PORT &port) :
			_stream(stream), _port(port), _busyPorts(), _data(), _outBuf() {
	}

	Pin_t GetPin(unsigned char pinNum) {
		_busyPorts[pinNum] = true;
		return Pin_t(pinNum, *this);
	}

	void Disable() {
		_stream.Disable();
	}

	void Enable() {
		_stream.SetDir(STREAM::MemToPeripheral);
		_stream.SetCircularMode(true);
		_stream.SetMemoryAddr(_outBuf);
		_stream.SetMemorySize(Length);
		_stream.MemoryIncrement(true);
		_stream.SetPeripheralAddr(_port.GetBitSetResetReg());
		_stream.SetPeripheralSize(1);
		_stream.PeripheralIncrement(false);
		_stream.Enable();
	}

	bool isEnable() {
		return _stream.isEnable();
	}

private:
	STREAM &_stream;
	PORT &_port;
	bool _busyPorts[Pins];
	unsigned int _data[Pins];
	unsigned int _outBuf[Length];

	void Apply() {
		for (int bitIndex = 0; bitIndex < Length; ++bitIndex) {
			unsigned int bit = 0;
			unsigned int bits = 0;
			for (int pinIndex = 0; pinIndex < Pins; ++pinIndex) {
				if (!_busyPorts[pinIndex])
					continue;
				bit = (_data[pinIndex] & (1 << (Length - 1 - bitIndex)));
				bits |= (1 << (pinIndex + ((bit == 0) ? 16 : 0)));
			}
			_outBuf[bitIndex] = bits;
		}
	}

};

template<class STREAM, class PORT, int LENGTH = 5>
class PWMDMAPortOut<STREAM, PORT, LENGTH> MakeSTM32F4DMAPortOut5Bit(
		STREAM &stream, PORT &port) {
	return PWMDMAPortOut<STREAM, PORT, LENGTH>(stream, port);
}

template<class STREAM, class PORT, int LENGTH = 7>
class PWMDMAPortOut<STREAM, PORT, LENGTH> MakeSTM32F4DMAPortOut7Bit(
		STREAM &stream, PORT &port) {
	return PWMDMAPortOut<STREAM, PORT, LENGTH>(stream, port);
}

template<class STREAM, class PORT, int LENGTH = 8>
class PWMDMAPortOut<STREAM, PORT, LENGTH> MakeSTM32F4DMAPortOut8Bit(
		STREAM &stream, PORT &port) {
	return PWMDMAPortOut<STREAM, PORT, LENGTH>(stream, port);
}

template<class STREAM, class PORT, int LENGTH = 10>
class PWMDMAPortOut<STREAM, PORT, LENGTH> MakeSTM32F4DMAPortOut10Bit(
		STREAM &stream, PORT &port) {
	return PWMDMAPortOut<STREAM, PORT, LENGTH>(stream, port);
}

template<class STREAM, class PORT, int LENGTH = 12>
class PWMDMAPortOut<STREAM, PORT, LENGTH> MakeSTM32F4DMAPortOut12Bit(
		STREAM &stream, PORT &port) {
	return PWMDMAPortOut<STREAM, PORT, LENGTH>(stream, port);
}

#endif /* PWMDMAOUT_H_ */
