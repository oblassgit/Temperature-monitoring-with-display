#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // Die Breite des Displays in Pixeln
#define SCREEN_HEIGHT 32 // Die Länge des Displays in Pixeln

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#include "DHT.h" // bindet die DHT Bibliothek ein damit der Mikrocontroller mit dem Sensor sprechen kann
#define DHTPIN 14 // legt fest an welchem GPIO Pin der Temperatursensor hängt D5 ist in diesem Fall GPIO 14
#define DHTTYPE DHT11 // Der Sensortyp ist DHT 11 (gibt auch noch DHT 22)

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200); // legt die Geschwindigkeit der USB Leitung fest

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); 
  } // Stellt sicher, dass ein Display mit der richtigen Adresse angeschlossen ist

  display.display(); // zeigt den Adafruit Splashscreen
  delay(2000); // wartet 2000 ms bzw. 2 s
  display.clearDisplay();  //löscht alles was vorher auf dem Display angezeigt wurde

  dht.begin(); // startet den Temperatursensor

} // Der setup code wird einmalig ausgeführt

void loop() {
  delay(2000); // 2 Sekunden warten
  // Hier kommt der Code zum Abfragen und Anzeigen der Temperatur und Luftfeuchtigkeit rein

} // Der loop code wird in einer Endlosschleife ausgeführt
