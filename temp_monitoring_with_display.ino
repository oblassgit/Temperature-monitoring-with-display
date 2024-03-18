#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // Die Breite des Displays in Pixeln
#define SCREEN_HEIGHT 32 // Die Länge des Displays in Pixeln

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#include "DHT.h" //bindet die DHT Bibliothek ein damit der Mikrocontroller mit dem Sensor sprechen kann
#define DHTPIN 14 //legt fest an welchem GPIO Pin der Temperatursensor hängt D1 ist in diesem Fall GPIO 5
#define DHTTYPE DHT11 //Der Sensortyp ist DHT 11 (gibt auch noch DHT 22)

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200); //legt die Geschwindigkeit der USB Leitung fest

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don'temperatur proceed, loop forever
  }

  display.display(); //zeigt den Adafruit Splashscreen
  delay(2000);
  display.clearDisplay(); //löscht alles was vorher auf dem Display angezeigt wurde

  dht.begin(); //startet den Temperatursensor

}


void loop() {
  delay(2000); // 2000ms = 2s warten
  // Variable in der wir die Luftfeuchtigkeit speichern
  float feuchtigkeit = dht.readHumidity();
  // Variable in der wir die Temperatur in Celsius speichern
  float temperatur = dht.readTemperature();

  // Hier wird geprüft, ob die Temperaturmessung fehlgeschlagen ist
  if (isnan(feuchtigkeit) || isnan(temperatur)) {
    Serial.println(F("Lesen der Daten vom DHT Sensor ist fehlgeschlagen!"));
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Read Failure!");
    display.display();
    return; // Hiermit brechen wir die Schleife ab
  }

  Serial.print(F("Humidity: "));
  Serial.print(feuchtigkeit);
  Serial.print(F("%  Temperature: "));
  Serial.print(temperatur);
  Serial.println(F("°C "));


  display.setTextSize(1); // Textgröße wird gesetzt
  display.setTextColor(SSD1306_WHITE); // Textfarbe wird gesetzt
  display.setCursor(0, 0); // Von wo aus angefangen wird zu schreiben (hier von oben links)
  display.cp437(); // legt den Zeichensatz fest, mit dem wir Text ausgeben

  display.clearDisplay(); // Vorherige Anzeige wird gelöscht
  display.print(temperatur);
  display.println(F(" Celsius"));
  display.print(feuchtigkeit);
  display.println(" %");
  display.display(); // Wir zeigen an, was wir angegeben haben
}
