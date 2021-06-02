# Raspberry_arduino_DHT22
 Collect data from 8 DHT22 sensors and send it to raspberry PI

DHT22 sensors need real-time operating system to work properly. By connecting sensors directly to Raspberry PI we have to retry sensor reading multiple times before we get any data from the sensor. Arduino can give digital sensor exactly right length signals for robust operation. 

DHT22 sensors --> Arduino --> serial communication via USB to raspberry PI

I have tested this project using 8 DHT22 sensors, Arduino MEGA, and Raspberry PI 4
