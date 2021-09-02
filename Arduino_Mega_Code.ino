#include <EthernetENC.h>
#include <LiquidCrystal_I2C.h>
#include <dht11.h>
dht11 DHT11;
EthernetUDP udp;
#define DHT_Sensor1_PIN 22
#define DHT_Sensor2_PIN 23
#define DHT_Sensor3_PIN 24
#define DHT_Sensor4_PIN 25
#define DHT_Sensor5_PIN 26
#define DHT_Sensor6_PIN 27
#define DHT_Sensor7_PIN 28
#define DHT_Sensor8_PIN 29
#define Door_Switch1_PIN 30
#define Door_Switch2_PIN 31
#define Door_Switch3_PIN 32
#define Door_Switch4_PIN 33
#define Door_Switch5_PIN 34
#define Door_Switch6_PIN 35
#define Door_Switch7_PIN 36
#define Door_Switch8_PIN 37
#define PIR_Sensor1_PIN 38
#define PIR_Sensor2_PIN 39
#define PIR_Sensor3_PIN 40
#define PIR_Sensor4_PIN 41
#define PIR_Sensor5_PIN 42
#define PIR_Sensor6_PIN 43
#define Voice_Sensor1_PIN 44
#define Voice_Sensor2_PIN 45
#define Voice_Sensor3_PIN 46
#define Voice_Sensor4_PIN 47
#define Voice_Sensor5_PIN 48
#define Voice_Sensor6_PIN 49
#define Water_Sensor1_PIN 2
#define Water_Sensor2_PIN 3
#define Water_Sensor3_PIN 4
#define Water_Sensor4_PIN 5
#define Water_Sensor5_PIN 6
#define Water_Sensor6_PIN 7
#define Light_Sensor1_PIN 8
#define Light_Sensor2_PIN 9
#define Light_Sensor3_PIN 10
#define Light_Sensor4_PIN 11
#define Light_Sensor5_PIN 12
#define Light_Sensor6_PIN 13

dht11 DHT_1(DHT_Sensor1_PIN);
dht11 DHT_2(DHT_Sensor2_PIN);
dht11 DHT_3(DHT_Sensor3_PIN);
dht11 DHT_4(DHT_Sensor4_PIN);
dht11 DHT_5(DHT_Sensor5_PIN);
dht11 DHT_6(DHT_Sensor6_PIN);
dht11 DHT_7(DHT_Sensor7_PIN);
dht11 DHT_8(DHT_Sensor8_PIN);

EthernetServer server = EthernetServer(8);
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {

  Serial.begin(9600);

  uint8_t mac[6] = {0x74,0x69,0x69,0x2D,0x30,0x61};
  IPAddress ip(192,168,0,166);  //Arduino IP adress, change IP to our network IP address
  IPAddress gateway(192, 168, 0, 1);  //Change gateway to our network gateway address
  IPAddress subnet(255, 255, 255, 0);  ////Change subnet to our network subnet address
  IPAddress dnsServer(8, 8, 8, 8);

  Ethernet.begin(mac, ip, dnsServer, gateway, subnet);

  Serial.print(F("localIP: "));
  Serial.println(Ethernet.localIP());
  Serial.print(F("subnetMask: "));
  Serial.println(Ethernet.subnetMask());
  Serial.print(F("gatewayIP: "));
  Serial.println(Ethernet.gatewayIP());
  Serial.print(F("dnsServerIP: "));
  Serial.println(Ethernet.dnsServerIP());

  pinMode(Door_Switch1_PIN, INPUT); 
  pinMode(Door_Switch2_PIN, INPUT);
  pinMode(Door_Switch3_PIN, INPUT); 
  pinMode(Door_Switch4_PIN, INPUT);
  pinMode(Door_Switch5_PIN, INPUT); 
  pinMode(Door_Switch6_PIN, INPUT);
  pinMode(Door_Switch7_PIN, INPUT); 
  pinMode(Door_Switch8_PIN, INPUT);
  pinMode(PIR_Sensor1_PIN, INPUT);
  pinMode(PIR_Sensor2_PIN, INPUT);
  pinMode(PIR_Sensor3_PIN, INPUT);
  pinMode(PIR_Sensor4_PIN, INPUT);
  pinMode(PIR_Sensor5_PIN, INPUT);
  pinMode(PIR_Sensor6_PIN, INPUT);
  pinMode(Voice_Sensor1_PIN, INPUT);
  pinMode(Voice_Sensor2_PIN, INPUT);
  pinMode(Voice_Sensor3_PIN, INPUT);
  pinMode(Voice_Sensor4_PIN, INPUT);
  pinMode(Voice_Sensor5_PIN, INPUT);
  pinMode(Voice_Sensor6_PIN, INPUT);
  pinMode(Water_Sensor1_PIN, INPUT);
  pinMode(Water_Sensor2_PIN, INPUT);
  pinMode(Water_Sensor3_PIN, INPUT);
  pinMode(Water_Sensor4_PIN, INPUT);
  pinMode(Water_Sensor5_PIN, INPUT);
  pinMode(Water_Sensor6_PIN, INPUT);
  pinMode(Light_Sensor1_PIN, INPUT);
  pinMode(Light_Sensor2_PIN, INPUT);
  pinMode(Light_Sensor3_PIN, INPUT);
  pinMode(Light_Sensor4_PIN, INPUT);
  pinMode(Light_Sensor5_PIN, INPUT);
  pinMode(Light_Sensor6_PIN, INPUT);

//LCD Setup
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(F("Hayrat Monitoring v1"));
  lcd.setCursor(0,1);
  lcd.print("IP:");
  lcd.print(Ethernet.localIP());
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(F("System"));
  lcd.setCursor(6,1);
  lcd.print(F("Starting.."));
  delay(2000);
}

void loop() {

  int success;
  String Cabinet1,Cabinet2,Cabinet3,Cabinet4,Cabinet5,Cabinet6,Cabinet7,Cabinet8;
  String Cabinet9,Cabinet10,Cabinet11,Cabinet12,Cabinet13,Cabinet14,Cabinet15,Cabinet16;
  String Hall_1,Hall_2,Hall_3,Hall_4;
  String s1temp,s1nem,s1cig;
  String s2temp,s2nem,s2cig;
  String Door_Switch1,Door_Switch2,Door_Switch3,Door_Switch4,Door_Switch5,Door_Switch6,Door_Switch7,Door_Switch8;
  String PIR_Sensor1,PIR_Sensor2,PIR_Sensor3,PIR_Sensor4,PIR_Sensor5,PIR_Sensor6;
  String Voice_Sensor1,Voice_Sensor2,Voice_Sensor3,Voice_Sensor4,Voice_Sensor5,Voice_Sensor6;
  String Water_Sensor1,Water_Sensor2,Water_Sensor3,Water_Sensor4,Water_Sensor5,Water_Sensor6;
  String Light_Sensor1,Light_Sensor2,Light_Sensor3,Light_Sensor4,Light_Sensor5,Light_Sensor6;

//Ping Echo Response -Start 
  size_t size;  
  if (EthernetClient client = server.available())
    {
      if (client)
        {
          while((size = client.available()) > 0)
            {
              uint8_t* msg = (uint8_t*)malloc(size);
              size = client.read(msg,size);
              Serial.write(msg,size);
              client.write(msg,size);
              free(msg);
            }
        }
    }
//Ping Echo Response -End
//Hall_1 Data Sending InfluxDB -CodeStart
    {
      PIR_Sensor1 = digitalRead(PIR_Sensor1_PIN);
      PIR_Sensor2 = digitalRead(PIR_Sensor2_PIN);
      PIR_Sensor3 = digitalRead(PIR_Sensor3_PIN);
      PIR_Sensor4 = digitalRead(PIR_Sensor4_PIN);
      PIR_Sensor5 = digitalRead(PIR_Sensor5_PIN);
      PIR_Sensor6 = digitalRead(PIR_Sensor6_PIN);
      Voice_Sensor1 = digitalRead(Voice_Sensor1_PIN);
      Voice_Sensor2 = digitalRead(Voice_Sensor2_PIN);
      Voice_Sensor3 = digitalRead(Voice_Sensor3_PIN);
      Voice_Sensor4 = digitalRead(Voice_Sensor4_PIN);
      Voice_Sensor5 = digitalRead(Voice_Sensor5_PIN);
      Voice_Sensor6 = digitalRead(Voice_Sensor6_PIN);
      Light_Sensor1 = digitalRead(Light_Sensor1_PIN);
      Light_Sensor2 = digitalRead(Light_Sensor2_PIN);
      Light_Sensor3 = digitalRead(Light_Sensor3_PIN);
      Light_Sensor4 = digitalRead(Light_Sensor4_PIN);
      Light_Sensor5 = digitalRead(Light_Sensor5_PIN);
      Light_Sensor6 = digitalRead(Light_Sensor6_PIN);
      Water_Sensor1 = digitalRead(Water_Sensor1_PIN);
      Water_Sensor2 = digitalRead(Water_Sensor2_PIN);
      Water_Sensor3 = digitalRead(Water_Sensor3_PIN);
      Water_Sensor4 = digitalRead(Water_Sensor4_PIN);
      Water_Sensor5 = digitalRead(Water_Sensor5_PIN);
      Water_Sensor6 = digitalRead(Water_Sensor6_PIN);
      
      Serial.println();
      success = udp.beginPacket(IPAddress(192,168,0,160),8089);  //InfluxDB UDP sending packet, change IP to our InfluxDB address
      Serial.print("beginPacket: ");
      Serial.println(success ? "success" : "failed");
      
      Hall_1 = String("DC_Istanbul_Hall,Zone_1=Hall_1 PIRsensor1=" + PIR_Sensor1 + "," + "PIRsensor2=" + PIR_Sensor2 + "," + "PIRsensor3=" + PIR_Sensor3 + "," + "PIRsensor4=" + PIR_Sensor4 + "," + "PIRsensor5=" + PIR_Sensor5 + "," + "PIRsensor6=" + PIR_Sensor6 + "," + \
      "VoiceSensor1=" + Voice_Sensor1 + "," + "VoiceSensor2=" + Voice_Sensor2 + "," + "VoiceSensor3=" + Voice_Sensor3 + "," + "VoiceSensor4=" + Voice_Sensor4 + "," + "VoiceSensor5=" + Voice_Sensor5 + "," + "VoiceSensor6=" + Voice_Sensor6 + "," + \
      "LightSensor1=" + Light_Sensor1 + "," + "LightSensor2=" + Light_Sensor2 + "," + "LightSensor3=" + Light_Sensor3 + "," + "LightSensor4=" + Light_Sensor4 + "," + "LightSensor5=" + Light_Sensor5 + "," + "LightSensor6=" + Light_Sensor6 + "," + \
      "WaterSensor1=" + Water_Sensor1 + "," + "WaterSensor2=" + Water_Sensor2 + "," + "WaterSensor3=" + Water_Sensor3 + "," + "WaterSensor4=" + Water_Sensor4 + "," + "WaterSensor5=" + Water_Sensor5 + "," + "WaterSensor6=" + Water_Sensor6);
      success = udp.print(Hall_1);

      Serial.print(F("Hall_1 Data: "));
      Serial.println(Hall_1);

      Serial.print(F("bytes written: "));
      Serial.println(success);

      success = udp.endPacket();

      Serial.print(F("endPacket: "));
      Serial.println(success ? "success" : "failed");
      udp.stop();
      delay(1000);
    }
//Hall_1 Data -CodeEnd
//Cabinet1 Data Sending InfluxDB -CodeStart        
    {   
//      int chk = DHT11.read(DHT_Sensor1_PIN);
      s1temp = DHT_1.temperature, 2;
      s1nem = DHT_1.humidity, 2;
      s1cig = DHT_1.dewPoint(), 2;
      s2temp = DHT_2.temperature, 2;
      s2nem = DHT_2.humidity, 2;
      s2cig = DHT_2.dewPoint(), 2;

      Door_Switch1 = digitalRead(Door_Switch1_PIN);
      Door_Switch2 = digitalRead(Door_Switch2_PIN);

      Serial.println();
      success = udp.beginPacket(IPAddress(192,168,0,160),8089);  //InfluxDB UDP sending packet, change IP to our InfluxDB address
      Serial.print("beginPacket: ");
      Serial.println(success ? "success" : "failed");

      // concatenate the temperature into the line protocol
      Cabinet1 = String("DC_Istanbul_Cabinet,Hall_1=Cabinet1 FrontTemperature=" + s1temp + "," + "FrontHumidity=" + s1nem + "," + "FrontDewpoint=" + s1cig + "," + "RearTemperature=" + s2temp + "," + "RearHumidity=" + s2nem + "," + "RearDewpoint=" + s2cig + "," + "FrontDoor=" + Door_Switch1 + "," + "RearDoor=" + Door_Switch2);
      success = udp.print(Cabinet1);

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Cabinet1 Tmp:" + s1temp + "C");
      lcd.setCursor(0,1);
      lcd.print("Hmd:" + s1nem + "%" + " Dw:" + s1cig);
      
      Serial.print(F("Cabinet1 Data: "));
      Serial.println(Cabinet1);

      Serial.print(F("bytes written: "));
      Serial.println(success);

      success = udp.endPacket();

      Serial.print(F("endPacket: "));
      Serial.println(success ? "success" : "failed");
      udp.stop();
      delay(1000);
    }
//Cabinet1 Data -CodeEnd
//Cabinet2 Data Sending InfluxDB -CodeStart
    {
//      int chk = DHT11.read(DHT_Sensor2_PIN);
      s1temp = DHT_3.temperature, 2;
      s1nem = DHT_3.humidity, 2;
      s1cig = DHT_3.dewPoint(), 2;
      s2temp = DHT_4.temperature, 2;
      s2nem = DHT_4.humidity, 2;
      s2cig = DHT_4.dewPoint(), 2;

      Door_Switch3 = digitalRead(Door_Switch3_PIN);
      Door_Switch4 = digitalRead(Door_Switch4_PIN);

      Serial.println();
      success = udp.beginPacket(IPAddress(192,168,0,160),8089);  //InfluxDB UDP sending packet, change IP to our InfluxDB address
      Serial.print("beginPacket: ");
      Serial.println(success ? "success" : "failed");
      
      Cabinet2 = String("DC_Istanbul_Cabinet,Hall_1=Cabinet2 FrontTemperature=" + s1temp + "," + "FrontHumidity=" + s1nem + "," + "FrontDewpoint=" + "0" + "," + "RearTemperature=" + s2temp + "," + "RearHumidity=" + s2nem + "," + "RearDewpoint=" + "0" + "," + "FrontDoor=" + Door_Switch3 + "," + "RearDoor=" + Door_Switch4);
      success = udp.print(Cabinet2);

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Cabinet2 Tmp:" + s2temp + "C");
      lcd.setCursor(0,1);
      lcd.print("Hmd:" + s2nem + "%" + " Dw:" + s2cig);
      
      Serial.print(F("Cabinet2 Data: "));
      Serial.println(Cabinet2);

      Serial.print(F("bytes written: "));
      Serial.println(success);

      success = udp.endPacket();

      Serial.print(F("endPacket: "));
      Serial.println(success ? "success" : "failed");
      udp.stop();
      delay(1000);
    }
//Cabinet2 Data -CodeEnd
//Cabinet3 Data Sending InfluxDB -CodeStart
    {
//      int chk = DHT11.read(DHT_Sensor2_PIN);
      s1temp = DHT_5.temperature, 2;
      s1nem = DHT_5.humidity, 2;
      s1cig = DHT_5.dewPoint(), 2;
      s2temp = DHT_6.temperature, 2;
      s2nem = DHT_6.humidity, 2;
      s2cig = DHT_6.dewPoint(), 2;

      Door_Switch5 = digitalRead(Door_Switch5_PIN);
      Door_Switch6 = digitalRead(Door_Switch6_PIN);

      Serial.println();
      success = udp.beginPacket(IPAddress(192,168,0,160),8089);  //InfluxDB UDP sending packet, change IP to our InfluxDB address
      Serial.print("beginPacket: ");
      Serial.println(success ? "success" : "failed");
      
      Cabinet3 = String("DC_Istanbul_Cabinet,Hall_1=Cabinet3 FrontTemperature=" + s1temp + "," + "FrontHumidity=" + s1nem + "," + "FrontDewpoint=" + "0" + "," + "RearTemperature=" + s2temp + "," + "RearHumidity=" + s2nem + "," + "RearDewpoint=" + "0" + "," + "FrontDoor=" + Door_Switch3 + "," + "RearDoor=" + Door_Switch4);
      success = udp.print(Cabinet3);

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Cabinet3 Tmp:" + s2temp + "C");
      lcd.setCursor(0,1);
      lcd.print("Hmd:" + s2nem + "%" + " Dw:" + s2cig);
      
      Serial.print(F("Cabinet3 Data: "));
      Serial.println(Cabinet3);

      Serial.print(F("bytes written: "));
      Serial.println(success);

      success = udp.endPacket();

      Serial.print(F("endPacket: "));
      Serial.println(success ? "success" : "failed");
      udp.stop();
      delay(1000);
    }
//Cabinet3 Data -CodeEnd
//Cabinet4 Data Sending InfluxDB -CodeStart
    {
//      int chk = DHT11.read(DHT_Sensor2_PIN);
      s1temp = DHT_7.temperature, 2;
      s1nem = DHT_7.humidity, 2;
      s1cig = DHT_7.dewPoint(), 2;
      s2temp = DHT_8.temperature, 2;
      s2nem = DHT_8.humidity, 2;
      s2cig = DHT_8.dewPoint(), 2;

      Door_Switch7 = digitalRead(Door_Switch7_PIN);
      Door_Switch8 = digitalRead(Door_Switch8_PIN);

      Serial.println();
      success = udp.beginPacket(IPAddress(192,168,0,160),8089);  //InfluxDB UDP sending packet, change IP to our InfluxDB address
      Serial.print("beginPacket: ");
      Serial.println(success ? "success" : "failed");
      
      Cabinet4 = String("DC_Istanbul_Cabinet,Hall_1=Cabinet4 FrontTemperature=" + s1temp + "," + "FrontHumidity=" + s1nem + "," + "FrontDewpoint=" + "0" + "," + "RearTemperature=" + s2temp + "," + "RearHumidity=" + s2nem + "," + "RearDewpoint=" + "0" + "," + "FrontDoor=" + Door_Switch3 + "," + "RearDoor=" + Door_Switch4);
      success = udp.print(Cabinet4);

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Cabinet4 Tmp:" + s2temp + "C");
      lcd.setCursor(0,1);
      lcd.print("Hmd:" + s2nem + "%" + " Dw:" + s2cig);
      
      Serial.print(F("Cabinet4 Data: "));
      Serial.println(Cabinet4);

      Serial.print(F("bytes written: "));
      Serial.println(success);

      success = udp.endPacket();

      Serial.print(F("endPacket: "));
      Serial.println(success ? "success" : "failed");
      udp.stop();
      delay(1000);
    }
//Cabinet4 Data -CodeEnd
  }
