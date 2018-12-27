#ifndef _DS18B20Events_h
#define _DS18B20Events_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <DallasTemperature.h>

typedef void(*changeHandler)(uint8_t, float);

class DS18B20Events
{
public:
	DS18B20Events(uint8_t index = 0);
	~DS18B20Events();
	float getTempC(void);
	unsigned long getMillis();
	uint8_t getIndex();
	changeHandler onChange = nullptr;
	void loop(void);

	static void setInterval(unsigned long value);
	static  void setup(DallasTemperature* sensors);

private:
	static const unsigned long minInterval = 1000;

	uint8_t _index;
	float currentTempC = -127.0f;
	float lastTempC = -127.0f;
	unsigned long lastMillisGet;
	unsigned long currentMillis;
};

#endif

