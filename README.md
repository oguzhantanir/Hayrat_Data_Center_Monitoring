# Hayrat_Data_Center_Monitoring
Data Center Temperature, Humidity, DewPoint, Cabinet Door Access, Voice, Light and Water Sensor Monitoring on Grafana Dashboard.
This project is the cheapest monitoring solution in the world. :) It can be scalable using multiple base units and aggregate in a central database. Different sensors can be added and Thousands of sensors can be tracked. Have a good time!

# Requirements
Software Requirement
- InfluxDB (Time Series Database)
- Grafana (Dashboard)

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

# Arduino Libraries
- EthernetENC (https://github.com/jandrassy/EthernetENC) We used this library because it uses less memory. Alternatively you can use UIPEthernet library.
- LiquidCrystal_I2C (https://github.com/johnrickman/LiquidCrystal_I2C) If you use the LCD should be used this library. (Not required)
- DHT11 (https://github.com/oguzhantanir/Hayrat_Data_Center_Monitoring/tree/main/DHT11)

 Alternative ENC28J60 Library
- UIPEthernet (https://github.com/UIPEthernet/UIPEthernet)

# Installation
Ubuntu 20.04 & InfluxDB & Grafana

- Ubuntu Installation
- InfluxDB Installation

According to the performance needs, InfluxDB can be installed on separate servers in an scalable cluster structure. We are running on the same server in a simple structure.

Ubuntu users can install the latest stable version of InfluxDB using the apt-get package manager.

Add the InfluxData repository with the following commands:
```
wget -qO- https://repos.influxdata.com/influxdb.key | sudo apt-key add -
source /etc/lsb-release
echo "deb https://repos.influxdata.com/${DISTRIB_ID,,} ${DISTRIB_CODENAME} stable" | sudo tee /etc/apt/sources.list.d/influxdb.list
```
Then, install and start the InfluxDB service:
```
sudo apt-get update && sudo apt-get install influxdb
sudo systemctl enable influxdb
sudo systemctl start influxdb
```
