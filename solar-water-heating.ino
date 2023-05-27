#include <DallasTemperature.h>
#include <OneWire.h>

#define ONE_WIRE_PIN 3
#define RELAY_PUMP_PIN 10

int sensorCount = 0;
unsigned long SECONDS = 1000UL,
              MINUTES = SECONDS * 60;
float solarPanelTemp = 0,
      boilerTemp = 0;
OneWire oneWire(ONE_WIRE_PIN);
DallasTemperature sensors(&oneWire);
DeviceAddress Thermometer;

uint8_t solarPanelAddr[8] = {0x28, 0x8C, 0x34, 0x47, 0xA1, 0x21, 0x01, 0x72};
uint8_t boilerAddr[8] = {0x28, 0x48, 0x47, 0x3D, 0xA1, 0x21, 0x01, 0xA1};

void setup() {
    // sensors.begin();
    Serial.begin(9600);

    pinMode(ONE_WIRE_PIN, INPUT);
    pinMode(RELAY_PUMP_PIN, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);

    // stop pump
    digitalWrite(RELAY_PUMP_PIN, HIGH);

    // printAddresses(ONE_WIRE_PIN);
}

void loop() {
    sensors.requestTemperatures();
    solarPanelTemp = sensors.getTempC(solarPanelAddr);
    boilerTemp = sensors.getTempC(boilerAddr);
    // Serial.print("Solar panel: ");
    // Serial.println(solarPanelTemp);
    // Serial.print("Boiler: ");
    // Serial.println(boilerTemp);

    if (solarPanelTemp > 45) {
        digitalWrite(RELAY_PUMP_PIN, LOW);
        delay(1.5 * MINUTES);
        digitalWrite(RELAY_PUMP_PIN, HIGH);
    } else {
        digitalWrite(RELAY_PUMP_PIN, HIGH);
    }
    // wait for the water to heat up
    // delay(0.2 * MINUTES);
    delay(10 * MINUTES);
}
