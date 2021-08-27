# Hayrat_Data_Center_Monitoring
Data Center Temperature, Humidity, DewPoint, Cabinet Door Access, Voice, Light and Water Sensor Monitoring on Grafana Dashboard.

Software Requirements
- InfluxDB
- Grafana

Components And Supplies
- Arduino Mega 2560
- ENC28J60 Network Module
- DHT11 Sensor
- HC-SR501 Motion Sensor
- Lever Switch
- LDR Light Sensor
- Sound Sensor
- Water Sensor

Optional
- LCD I2C 16x2

##############

Arduino Libraries
- EthernetENC (https://github.com/jandrassy/EthernetENC) We used this library because it uses less memory. Alternatively you can use UIPEthernet library.
- LiquidCrystal_I2C (https://github.com/johnrickman/LiquidCrystal_I2C) If you use the LCD should be used this library. (Not required)
- DHT11 (https://github.com/oguzhantanir/Hayrat_Data_Center_Monitoring/tree/main/DHT11)

Alternative ENC28J60 Library
- UIPEthernet (https://github.com/UIPEthernet/UIPEthernet)
