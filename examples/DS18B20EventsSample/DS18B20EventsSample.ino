#include "DS18B20Events.h"

// Pin for DS18B20
#define ONE_WIRE_BUS 53

/********************************************************************/
// Setup a oneWire instance to communicate with any OneWire devices  
// (not just Maxim/Dallas temperature ICs) 
OneWire oneWire(ONE_WIRE_BUS);

// Init DallasTemperature
DallasTemperature dallasTemperature(&oneWire);

//Init thermometer with index 0 (default)
DS18B20Events thermometer(0);

// the setup function runs once when you press reset or power the board
void setup() {	
	Serial.begin(115200);
	DS18B20Events::setup(&dallasTemperature); // Link DS18B20Events to DallasTemperature object
	DS18B20Events::setInterval(5000); // Set min interval in milliseconds between 2 measurements. Default 10000 set in setup() method.
	
	// subscribe to temperature changed event
	thermometer.onChange = temperatureChanged;
}

// the loop function runs over and over again until power down or reset
void loop() {
	thermometer.loop(); // Mandatory to measure temperature and fire an event if needed

	Serial.print(thermometer.getTempC()); // Get last measured tempC if needed.
	Serial.print(" measured ");
	Serial.print((millis() - thermometer.getMillis()) / 1000);
	Serial.println(" seconds ago.");

	delay(1000);
}

void temperatureChanged(uint8_t index, float tempC)
{
	Serial.print(tempC);
	Serial.print(" new tempC at index ");
	Serial.println(index);
}
