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

//Ever thermometer has a unique address, this can be found with addressFinder.ino
DeviceAddress thermometer1 = { 0x28, 0xFF, 0xE3, 0x86, 0x66, 0x14, 0x03, 0x4D };
DeviceAddress thermometer2 = { 0x28, 0xFF, 0xD7, 0x76, 0x66, 0x14, 0x03, 0xA7 };

int buttonOne = 7;
int buttonState = 0;
int temperature1;
int temperature2;
int timer = 90;
int seconds = 0;
boolean startCountDown = false;

//Prints all the data to the LCD screen.
void printScreen(){
  display.setCursor(0,0);
  display.println("---BREW-B0Y---");
  display.setCursor(0,10);
  display.println("BOIL:");
  display.setCursor(32,10);
  display.print( temperature1);
  display.print("c");
  display.setCursor(0,20);
  display.println("MASH:");
  display.setCursor(32,20);
  display.print(temperature2);
  display.print("c");
  display.setCursor(0,30);
  display.print("TIME:");
  display.setCursor(32 ,30);
  display.print(timer);
  display.print("m ");
  display.print(seconds);
  display.print("s");
  display.setCursor(0,36);
  display.print("--------------");
  display.display();
  display.clearDisplay();
}

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

//Does what it says.
void getTemperatures(){
  temperature1 = sensors.getTempC(thermometer1);
  temperature2 = sensors.getTempC(thermometer2);
}

//Check to see what state the timer is at.
void checkTimer(){
  if (timer > 0 && startCountDown){
    if (seconds >= 1){
      seconds = seconds -1; 
    }
    if (seconds == 0){
      timer = timer -1;
      seconds = 60;
    }

    if (timer <= 0){
      timer = 0;
      seconds = 0;   
    }
    delay(1000);
  }
}

void checkIfTimerStarted(){
  if (buttonState == HIGH) {
    startCountDown = true; 
  }
}

void loop(void) {
  buttonState = digitalRead(buttonOne);
  printScreen();
  getTemperatures();
  sensors.requestTemperatures();
  checkIfTimerStarted();
  checkTimer();
} 
































