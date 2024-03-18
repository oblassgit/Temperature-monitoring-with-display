#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32 

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#include "DHT.h" 
#define DHTPIN 14 
#define DHTTYPE DHT11 

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  display.display();
  delay(2000);
  display.clearDisplay();

  dht.begin();

}


void loop() {
  delay(2000);
  float hum = dht.readHumidity();
  float temp = dht.readTemperature();

  if (isnan(hum) || isnan(temp)) {
    Serial.println(F("Lesen der Daten vom DHT Sensor ist fehlgeschlagen!"));
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Read Failure!");
    display.display();
    return;
  }

  // Logging the temp and humidity via the serial interface
  Serial.print(F("Humidity: "));
  Serial.print(hum);
  Serial.print(F("%  Temperature: "));
  Serial.print(temp);
  Serial.println(F("°C "));


  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0); 
  display.cp437();

  // Showing the temp and humidity on the display
  display.clearDisplay(); 
  display.print(temp);
  display.println(F(" Celsius")); // cp437 charset doesn't have "°", so "Celsius" is used.
  display.print(hum);
  display.println(" %");
  display.display(); 
}
