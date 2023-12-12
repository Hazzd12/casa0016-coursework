#include <MQ135.h>

#include <Wire.h>
#include <LiquidCrystal.h>
#include <DHT.h>

#define DHTPIN 7  //Digital Pin 2
#define DHTTYPE DHT22


const int ANALOGPIN = 0;

#define analogLightPin A1
#define Vcc 5.0

#define buzzerPin 9

int temperature, humidity, ppm;
int LightR;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
DHT dht(DHTPIN, DHTTYPE);
MQ135 gasSensor = MQ135(ANALOGPIN);

const String errors[7] = {
  "Too much light",
  "Temperature too low",
  "Temperature too high",
  "Humidity too low",
  "Humidity too high",
  "Too much CO2",
  "Bad airtightness"
};

void setup() {
  Serial.begin(115200);  // set rate at 115200
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

  float voltage = Vcc * analogRead(analogLightPin) / 1024;
  Serial.print("Voltage is: ");
  Serial.println(voltage);

  float humidity = dht.readHumidity(false);
  float temperature = dht.readTemperature(false);

  Serial.print("Temperature: ");
  Serial.println(temperature);
  Serial.print("Humidity: ");
  Serial.println(humidity);

  float ppm = gasSensor.getPPM();
  Serial.print("PPM: ");
  Serial.println(ppm);
  Serial.println(gasSensor.getRZero());

 

  /*
  **results[0]==true->errors[0],
  **results[1]==true->errirs[1],
  **......
  **results[6]==true->errors[6],
  **if there is any error, flag will be true; or flag will be false
  **/
  bool results[7] = { false };
  bool flag = false;
  if (voltage < 3.4) {
    results[0] = true;
    flag = true;
  }

  if (temperature < 15) {
    results[1] = true;
    flag = true;
  } else if (temperature > 25) {
    results[2] = true;
    flag = true;
  }

  if (humidity < 60) {
    results[3] = true;
    flag = true;
  } else if (humidity > 95.0) {
    results[4] = true;
    flag = true;
  }
  //1000ppm ≈ 1.0 g/L, the suitable rang is from 500 to 1000
  //according to https://atlas-scientific.com/blog/co2-in-wine/
  if (ppm > 1000) {
    results[5] = true;
    flag = true;
  } else if (ppm < 400) {
    results[6] = true;
    flag = true;
  }

  if (flag) {
    
    for(int i=0; i<7; i++){
      if(results[i]){
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(errors[i]);
        tone(buzzerPin, 1000, 1000);
        delay(3000);
      }
    }
  } else {  //when there is no error, the lcd will show the detailed data
    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("T:");
    lcd.setCursor(3, 0);
    lcd.print(temperature);

    // display
    lcd.setCursor(0, 1);
    lcd.print("H:");
    lcd.setCursor(3, 1);

    lcd.print(humidity);
    delay(3000);

    // set the cursor to column 0, line 2
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("C:");
    lcd.setCursor(3, 0);
    lcd.print(ppm);

    lcd.setCursor(0, 1);
    lcd.print("L:");
    lcd.setCursor(3, 1);
    lcd.print("Good");
    delay(3000);
  }
  
}
