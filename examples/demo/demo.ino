#include <aht20_sensor.h>

AHT20 aht20;


void setup() {
  Serial.begin(115200);
  Serial.println("AHT20 examples");
  aht20.begin();
}

void loop() {
  aht20.startSingleMeasure();
  delay(100);
  Serial.print("Temperature: ");
  Serial.print(aht20.getTemperature());
  Serial.print(" C        HUmidity: ");
  Serial.print(aht20.getHumidity());
  Serial.println(" RH");
  delay(1000);
}
