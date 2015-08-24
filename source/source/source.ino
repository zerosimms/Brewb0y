#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

//New display object.
Adafruit_PCD8544 display = Adafruit_PCD8544(12, 11, 10, 9, 8);
//Temperature Pins.
#define ONE_WIRE_BUS 3

//LCD Pins.
#define PIN_RESET 8
#define PIN_SCE   9
#define PIN_DC 10
#define PIN_SDIN  11
#define PIN_SCLK  12

//Onewire object.
OneWire oneWire(ONE_WIRE_BUS);

//Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

//Each thermometer has a unique address, this can be found with addressFinder.ino
DeviceAddress thermometer1 = { 0x28, 0xFF, 0xE3, 0x86, 0x66, 0x14, 0x03, 0x4D };
DeviceAddress thermometer2 = { 0x28, 0xFF, 0xD7, 0x76, 0x66, 0x14, 0x03, 0xA7 };

int buttonOne = 7;
int buttonState = 0;
int temperature1;
int temperature2;
int timer = 90;
int seconds = 0;
double originalGravity;
double endGravity;
boolean startCountingDown = false;

void setup(void) {
  Serial.begin(9600); 
  pinMode(buttonOne, INPUT);
  display.clearDisplay();  
  display.begin();
  display.setContrast(45);
  display.setTextSize(1);
  display.setTextColor(BLACK);

  sensors.begin();
  sensors.setResolution(thermometer1, 10);
  sensors.setResolution(thermometer2, 10);
}

void loop(void) {
  buttonState = digitalRead(buttonOne);
  printScreen();
  getTemperatures();
  sensors.requestTemperatures();
  startCounter();
  checkTimer();
} 




