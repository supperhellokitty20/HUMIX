/* 
  Put DHTxx sensor info through HD44780 output 
*/
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystalIO.h>
#include <IoAbstractionWire.h>
#include <Wire.h>

#define DHTPIN 2     // Digital pin connected to the DHT sensor 
#define DHTTYPE    DHT11     // Define your dht_sensor  type  here  
DHT_Unified dht(DHTPIN, DHTTYPE);
LiquidCrystalI2C_RS_EN(lcd,0x27,false) ;
uint32_t delayMS;
float dht_temp = 0 ; 
float dht_humid= 0 ; 
byte degree_symbol[8] = 
              {
                0b00111,
                0b00101,
                0b00111,
                0b00000,
                0b00000,
                0b00000,
                0b00000,
                0b00000
              };
byte heart_symbol[8] = { 
    0b00000,
    0b01010,
    0b11111,
    0b11111,
    0b11111,
    0b01110,
    0b00100,
    0b00000
}; 
void dht_info() {

  // Delay between measurements.
  delay(delayMS);
  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));

  }
  else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
    dht_temp = event.temperature;
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    Serial.print(F("Humidity:"));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
    dht_humid = event.relative_humidity; 
  }

} 

void setup() {
  Serial.begin(9600);
  //BEGIN lcd set up  
  Wire.begin();
  lcd.begin(16,2);
  // Set up some decoration 
  String name = "HUMIX V0" ;
  lcd.print(name) ; 
  lcd.createChar(2,heart_symbol) ;
  lcd.setCursor(name.length()+1,0) ;
  lcd.write(2); 
  lcd.blink(); 
  delay(3000);
  lcd.clear() ;
  //Sum marketing for myself cuz im unemployed for so long  
  String author = "author:bunbo_tai" ;
  lcd.print(author) ;
  delay(2000) ;
  lcd.clear() ;
  //Task manager allow the value to update constantly    
  taskManager.scheduleFixedRate(250, [] {
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.noBlink();
    lcd.setCursor(0,0) ;
    
    lcd.print(F("Temp:")); 
    lcd.print(dht_temp);
    lcd.createChar(1,degree_symbol) ;
    lcd.setCursor(9,0) ;
    lcd.write(1);
    lcd.print(("C"));
    lcd.setCursor(0, 1);
    // print the number of seconds since reset:
    //float secondsFraction =  millis() / 1000.0F;
    lcd.print(F("Humid:")); 
    lcd.print(dht_humid);
    lcd.print(F("%"));
  });
  //END of lcd setup

  // Initialize humid sensor.
  dht.begin();
  Serial.println(F("HUMIX"));
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;
}

void loop() {
  //dht_info will set the 2 globals values dht_temp and dht_humid 
  // and logging more info to the serial monitor 
  dht_info() ;
  taskManager.runLoop();
}



