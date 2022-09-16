#include <aht20_sensor.h>

AHT20 aht20;


void setup() {
  Serial.begin(115200);
  Serial.println("AHT20 Sensor Demo");
  aht20.begin();
  delay(2000);
}

void loop() {
  aht20.startSingleMeasure();
  Serial.print("Temperature: ");
  Serial.print(aht20.getTemperature());
  Serial.print(" C        Humidity: ");
  Serial.print(aht20.getHumidity());
  Serial.println(" RH");
  delay(2000);
}
