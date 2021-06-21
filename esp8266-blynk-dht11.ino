// Include the ESP8266WiFi library for accessing ESP8266 board
#include  <ESP8266WiFi.h>
// Include the BlynkSimpleEsp8266 library for the communication of Blynk and ESP8266 board
#include <BlynkSimpleEsp8266.h>
// Include DHT library to read data from DHT sensor(s)
#include <DHT.h>


// Give name for DHT sensor as DHTPIN on pin 2
#define DHTPIN 2
// Give the type of DHT sensor. (On this case I use DHT11 sensor)
#define DHTTYPE DHT11


// auth[] is the char given by your Blynk app to access your app that you have created
char auth[] = "your auth goes here";
// Store your WiFi SSID name in ssid[] char
char ssid[] = "WiFi SSID";
// Store your WiFi password in pass[] char
char pass[] = "WiFi password";


// Make new DHT named "dht".(You have created DHTPIN and DHTTYPE on the header section above)
DHT dht(DHTPIN, DHTTYPE);
// Make a new BlynkTimer named "timer" to push your sensor data to Blynk app
BlynkTimer timer;
// Make new WIdgetLCD named "lcd" on V0 [Virtual 0 pin (or according to yours)]
// I use LCD on my Blynk app instead of serial monitor
WidgetLCD lcd(V0);


// Make new function named "sendSensor()" to read and push your sensor data to your Blynk app
void sendSensor() {
  // "h" float used to store humidity value from DHT11 sensor
  // dht.readHumidity() is a function to read humidity from your DHT sensor
  float h = dht.readHumidity();
  // "t" float used to store temperature value from DHT11 sensor
  // dht.readTempereture() is a function to read temperature from your DHT sensor
  float t = dht.readTemperature();
  // lcd.clear() is clearing your Blynk app's LCD after read the sensor's values
  lcd.clear();

  // If DHT sensor is unavailable, print some text to Blynk's LCD
  if (isnan(h) || isnan(t)) {
    // Set Blynk's LCD cursor to (3,0) then send "Failed to" text
    lcd.print(3, 0, "Failed to");
    // Set Blynk's LCD cursor to (3,1) then send "Read DHT!" text
    lcd.print(3, 1, "Read DHT!");
    // return the if function if DHT sensor still unavailable
    return;
  }
  // If DHT sensor is available:
  // Send the temperature (t) value to V5 [Virtual 5 pin (or choose yours)]
  Blynk.virtualWrite(V5, t);
  // Send the humidity (h) value to V6 [Virtual 6 pin (or choose yours)]
  Blynk.virtualWrite(V6, h);
}


// setup() function which is only read once
void setup() {
  // Start Blynk using Blynk.begin() function. (auth, ssis, and pass have been made on the header above)
  Blynk.begin(auth, ssid, pass);
  // Start the DHT
  dht.begin();
  // Set interval for 1000L (1000 milisecond) to push sensors data to your Blynk ap
  timer.setInterval(1000L, sendSensor);
}

// loop() function that is read many times
void loop() {
  // Run Blynk
  Blynk.run();
  // Run timer
  timer.run();
}
