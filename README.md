# aht20_sensor
Arduino and ESP library for the AHT20 temprature and humidity sensor

I needed a library that works like this:

1)  Trigger the sensor to measure

2)  Get your results

3)  Let the sensor sleep and use minimal power only


The library works with fixed settings only. They are changable in the header file.

So the use of this library is as easy as:

Include this library and open an Instanz of this:
```
 #include <aht20_sensor.h>

 AHT20 aht20;
```
inside "setup" call the begin function:
```
  aht20.begin();
```
inside loop() do the following steps:
```
  // Tell the sensor to collect the measurements
  aht20.startSingleMeasure();
  // Make sure to wait at least 10 milliseconds
  delay(100);
  // Use the results as needed
  Serial.print("Temperature: ");
  Serial.print(aht20.getTemperature());
  Serial.print(" C        HUmidity: ");
  Serial.print(aht20.getHumidity());
  Serial.println(" RH");
```
State of this library: Testing!

