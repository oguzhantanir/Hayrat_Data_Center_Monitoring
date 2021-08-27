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

Arduino Libraries
- EthernetENC (https://github.com/jandrassy/EthernetENC) We used this library because it uses less memory.

Alternative ENC28J60 Library
- UIPEthernet (https://github.com/UIPEthernet/UIPEthernet)
