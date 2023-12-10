#include <MQ135.h>

#include <Wire.h>
#include <LiquidCrystal.h>
#include <DHT.h>

#define DHTPIN 7  //Digital Pin 2
#define DHTTYPE DHT22


const int ANALOGPIN=0;

#define analogLightPin A1
#define Vcc 5.0

#define buzzerPin 9

int temperature, humidity, ppm;
int LightR; 

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
DHT dht(DHTPIN, DHTTYPE);
MQ135 gasSensor = MQ135(ANALOGPIN);

void setup() {
  Serial.begin(115200); // set rate at 115200
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2); 
  // Print a message to the LCD.
  lcd.print("hello, world!");

  // Wait a maximum of 10s for Serial Monitor
  while (!Serial && millis() < 10000)
    ;

  //Initialise the DHT sensor
  dht.begin();
  

}

void loop() {

  float voltage = Vcc*analogRead(analogLightPin)/1024;
  Serial.print("Voltage is: ");
  Serial.println(voltage);


  // display z
  float humidity = dht.readHumidity(false);

  // false: Celsius (default)
  float temperature = dht.readTemperature(false);

  Serial.print("Temperature: ");
  Serial.println(temperature);
  Serial.print("Humidity: ");
  Serial.println(humidity);

  float ppm = gasSensor.getPPM();
  Serial.println(ppm);

  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.setCursor(3, 0);
  lcd.print(temperature);
  // display x

  // set the cursor to column 8, line 1
  lcd.setCursor(8, 0);
  lcd.print("H:");
  lcd.setCursor(11, 0);
  lcd.print(humidity);
  // display y

  // set the cursor to column 0, line 2
  lcd.setCursor(0, 1);
  lcd.print("C:");
  lcd.setCursor(3, 1);
  lcd.print(ppm);


  tone(buzzerPin, 1000, 1000);
  
  delay(3000);
}
