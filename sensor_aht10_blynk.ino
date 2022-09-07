#define BLYNK_TEMPLATE_ID "TMPLuXkIBfLg"
#define BLYNK_DEVICE_NAME "Suhu dan Kelembaban"
#define BLYNK_AUTH_TOKEN "lcMo_kbBHlvVKy2gT211gWg_rWxWzZ6Q"
#define BLYNK_PRINT Serial

#include <Adafruit_AHT10.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

Adafruit_AHT10 aht;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "KMTek";
char pass[] = "KMTek123";

Adafruit_Sensor *aht_humidity, *aht_temp;

void setup(void) {
  Blynk.begin(auth, ssid, pass);
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Wire.begin();
  Serial.println("Adafruit AHT10 test!");

  if (!aht.begin()) {
    Serial.println("Failed to find AHT10 chip");
    while (1) {
      delay(10);
    }
  }

  Serial.println("AHT10 Found!");
  aht_temp = aht.getTemperatureSensor();
  aht_temp->printSensorDetails();

  aht_humidity = aht.getHumiditySensor();
  aht_humidity->printSensorDetails();
}

void loop() {


sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
  Serial.print("Temperature: "); 
  Serial.println(temp.temperature); //Serial.println(" degrees C");
  Serial.print("Humidity: "); 
  Serial.println(humidity.relative_humidity); //Serial.println("% rH");
  
  Blynk.virtualWrite(V1,temp.temperature);
  Blynk.virtualWrite(V2,humidity.relative_humidity);
  Blynk.run();
  delay(1000);

}
