# Hayrat Data Center Monitoring
Data Center Temperature, Humidity, DewPoint, Cabinet Door Access, Voice, Light and Water Sensor Monitoring on Grafana Dashboard.
This project is the cheapest monitoring solution in the world. :) It can be scalable using multiple base units and aggregate in a central database. Different sensors can be added and Thousands of sensors can be tracked. Have a good time!

## Requirements
**Software Requirements**
- InfluxDB (Time Series Database)
- Grafana (Dashboard)

**Components And Supplies**
- Arduino Mega 2560
- ENC28J60 Network Module
- DHT11 Sensor
- HC-SR501 Motion Sensor
- Lever Switch
- LDR Light Sensor
- Sound Sensor
- Water Sensor

If you want to choose  more better professional sensor.

Optional
- LCD I2C 16x2

## Arduino Libraries
- EthernetENC (https://github.com/jandrassy/EthernetENC) We used this library because it uses less memory. Alternatively you can use UIPEthernet library.
- LiquidCrystal_I2C (https://github.com/johnrickman/LiquidCrystal_I2C) If you use the LCD should be used this library. (Not required)
- DHT11 (https://github.com/oguzhantanir/Hayrat_Data_Center_Monitoring/tree/main/DHT11)

 **Alternative ENC28J60 Library**
- UIPEthernet (https://github.com/UIPEthernet/UIPEthernet)

## Installation
Ubuntu 20.04 & InfluxDB & Grafana

- **Ubuntu Installation**

Standart Ubuntu server installation (https://ubuntu.com/tutorials/install-ubuntu-server)
- **InfluxDB Installation**

According to the performance needs, InfluxDB can be installed on separate servers in a scalable cluster structure. Now we are running on the same server in a simple structure.

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
InfluxDB provides the CLI tool named 'influx' for interacting with an InfluxDB server.
Run the 'influx' command below.
```
influx
```
Create an InfluxDB user and database.
```
create database HayratDB
create user hayrat with password 'blablabla'
grant all on HayratDB to hayrat
```
Now check the database and user.
```
show databases
show users
```
Create a retention policy.
```
CREATE RETENTION POLICY thirty_days ON HayratDB DURATION 30d REPLICATION 1 DEFAULT
SHOW RETENTION POLICIES ON HayratDB
```
Done. Next step;

By default InfluxDB using TCP 8086 port but we will use UDP 8089. For this, we will edit the InfluxDB configuration file.

Edit: /etc/influxdb/influxdb.conf
```
[[udp]]
  enabled = true
  bind-address = ":8089" # the bind address
  database = "HayratDB" # Name of the database that will be written to
  precision = "s"
  batch-size = 5000 # will flush if this many points get buffered
  batch-timeout = "1s" # will flush at least this often even if the batch-size is not reached
  batch-pending = 10 # number of batches that may be pending in memory
  read-buffer = 0
```
Restart InfluxDB service
```
sudo systemctl restart influxdb
```
And check status running
```
sudo systemctl status influxdb
```
**PS:** Don't forget to define the required ubuntu OS firewall (ufw) permissions.
- **Grafana Installation**

Install the latest OSS release:
```
sudo apt-get install -y apt-transport-https
sudo apt-get install -y software-properties-common wget
wget -q -O - https://packages.grafana.com/gpg.key | sudo apt-key add -
```
Add this repository for stable releases:
```
echo "deb https://packages.grafana.com/oss/deb stable main" | sudo tee -a /etc/apt/sources.list.d/grafana.list
```
Then install Grafana:
```
sudo apt-get update
sudo apt-get install grafana
sudo systemctl start grafana-server
sudo systemctl enable grafana-server
```
And check status running
```
systemctl status grafana-server
```
You can access the Grafana Dashboard using the URL http://your-server-ip:3000/

Add data source InfluxDB on Grafana and import to json dasboard file "Grafana_Hayrat_Data_Center_Monitoring_V1.json".
- **Arduino Installation**

Next step: Replace your own ip address and data center names in "Arduino_Mega_Code.ino" code. Connect all sensors as shown in the "Hayrat_Components_Connettions" diagram and upload code to Arduino Mega. Then, ENC28J60 module connect to the network.

**PS:** Make sure Arduino is network communicating with the InfluxDB server. Lever switch sensor and water sensor must be connected to "pull down".

## Finally

If everything is ok, you should be see the data in InfluxDB.
Run the below commands on Linux CLI.
```
influx
use HayratDB
SELECT * FROM DC_Istanbul_Cabinet WHERE time > now() - 1m LIMIT 20
```
The result should be as belows.
```
name: DC_Istanbul_Cabinet
time                FrontDewpoint FrontDoor FrontHumidity FrontTemperature Hall_1   RearDewpoint RearDoor RearHumidity RearTemperature
----                ------------- --------- ------------- ---------------- ------   ------------ -------- ------------ ---------------
1630593921000000000 0             0         0             0                Cabinet3 0            0        0            0
1630593922000000000 0             0         0             0                Cabinet4 0            0        0            0
1630593925000000000 14.15         1         38            30               Cabinet1 13.32        0        36           30
1630593926000000000 0             0         0             0                Cabinet2 0            0        0            0
1630593928000000000 0             0         0             0                Cabinet3 0            0        0            0
1630593929000000000 0             0         0             0                Cabinet4 0            0        0            0
1630593932000000000 14.15         1         38            30               Cabinet1 13.32        0        36           30
1630593933000000000 0             0         0             0                Cabinet2 0            0        0            0
1630593934000000000 0             0         0             0                Cabinet3 0            0        0            0
1630593936000000000 0             0         0             0                Cabinet4 0            0        0            0
1630593938000000000 14.15         1         38            30               Cabinet1 13.32        0        36           30
1630593940000000000 0             0         0             0                Cabinet2 0            0        0            0
1630593941000000000 0             0         0             0                Cabinet3 0            0        0            0
1630593942000000000 0             0         0             0                Cabinet4 0            0        0            0
1630593945000000000 14.15         1         38            30               Cabinet1 13.32        0        36           30
1630593946000000000 0             0         0             0                Cabinet2 0            0        0            0
1630593948000000000 0             0         0             0                Cabinet3 0            0        0            0
1630593949000000000 0             0         0             0                Cabinet4 0            0        0            0
1630593952000000000 14.15         1         38            30               Cabinet1 13.32        0        36           30
1630593953000000000 0             0         0             0                Cabinet2 0            0        0            0
```
**PS:** Result name "Measurements" will be your changed DC name in Arduino code. In this case, you will need to fix it in the dashboard template.

Yes, monitoring dashboard is working!
#### Congratulations! 
### Great job :)
