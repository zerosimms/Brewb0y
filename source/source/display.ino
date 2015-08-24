//Prints all the data to the LCD screen in a nice format.

void printScreen() {
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
