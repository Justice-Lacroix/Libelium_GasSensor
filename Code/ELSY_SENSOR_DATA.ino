#include <WiFi.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#define AN1 A0
#define AN3 A1
#define AN4 A2
#define AN5 A3
#define AN6 A4
#define AN7 A5


/* read sensor value
 AN1 = Sens Temperature
 AN4 = Sens Humidity
 AN5 = Sens Pressure
 AN3 = Sens CO2 / O2 -> see digital
 AN2 = Sens socket2A/socket2B -> see digital
 AN7 = Sens socket3A/socket3B -> see digital
 AN6 = Sens socket4A

*/

#define DIG1 2
#define DIG2 3
#define DIG3 4
#define DIG4 5
#define DIG5 6
#define DIG6 7
#define DIG7 8
#define DIG8 9

/* set sensor mode
 DIG8 high = Sens pressure 
 DIG2 high = Sens CO2
 DIG2 low  = Sens O2
 DIG4 high = Sens socket 2A
 DIG4 low  = Sens socket 2B
 DIG1 high + DIG7 high = Sens socket 3A
 DIG1 high + DIG6 high = Sens socket 3B
 DIG3 high + DIG5 high = Sens socket 4A
*/

#define	SENS_AMPLI1	0
#define	SENS_AMPLI2	1
#define	SENS_AMPLI3	2
#define	SENS_AMPLI4	4

bool NO2_state = false;

char ssid[] = "504F94A12106";
char pass[] = "";

IPAddress miniserverIP(192, 168, 1, 35);
const unsigned int port = 50003;
WiFiUDP udp;

void connect_wifi(){
  while (WiFi.begin(ssid) != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  udp.begin(port); 
}


void configure_amplifier(uint8_t ampli, uint8_t gain)
{
	switch( ampli )
	{
		case	SENS_AMPLI1	:	set_amplifier(B0101000,gain);
								break;
		case	SENS_AMPLI2	:	set_amplifier(B0101100,gain);
								break;
		case	SENS_AMPLI3	:	set_amplifier(B0101110,gain);
								break;
		case	SENS_AMPLI4	:	set_amplifier(B0101010,gain);
								break;
		default				:	;
	}
}

void set_amplifier(uint8_t address, uint8_t value) {
  uint8_t ampli = 128 - ((128 * (value - 1)) / 100);

  Wire.begin(); 
  delay(100);
  Wire.beginTransmission(address);
  Wire.write(0x10);    
  Wire.write(ampli);
  Wire.endTransmission();
}

void setup() {
  Serial.begin(9600);
  pinMode(AN1, INPUT);
  pinMode(AN3, INPUT);
  pinMode(AN4, INPUT);
  pinMode(AN5, INPUT);
  pinMode(AN6, INPUT);
  pinMode(AN7, INPUT);

  pinMode(DIG1, OUTPUT);
  pinMode(DIG2, OUTPUT);
  pinMode(DIG3, OUTPUT);
  pinMode(DIG4, OUTPUT);
  pinMode(DIG5, OUTPUT);
  pinMode(DIG6, OUTPUT);
  pinMode(DIG7, OUTPUT);
  pinMode(DIG8, OUTPUT);

  digitalWrite(DIG1, LOW);
  digitalWrite(DIG2, LOW);
  digitalWrite(DIG3, LOW);
  digitalWrite(DIG4, LOW);
  digitalWrite(DIG5, LOW);
  digitalWrite(DIG6, LOW);
  digitalWrite(DIG7, LOW);
  digitalWrite(DIG8, LOW);

  configure_amplifier(0, 10);

  connect_wifi();
}

void reset()
{
  digitalWrite(DIG1, LOW);
  digitalWrite(DIG2, LOW);
  digitalWrite(DIG3, LOW);
  digitalWrite(DIG4, LOW);
  digitalWrite(DIG5, LOW);
  digitalWrite(DIG6, LOW);
  digitalWrite(DIG7, LOW);
  digitalWrite(DIG8, LOW);
}


void send_udp(const char* message) {
  udp.beginPacket(miniserverIP, port);
  udp.write(message);
  udp.endPacket();
}

void handle_client()
{
  int packetSize = udp.parsePacket();
  if (packetSize) {
    char incoming[1024];
    int len = udp.read(incoming, 1024);
    if (len > 0) incoming[len] = '\0';
    Serial.print("Received: ");
    Serial.println(incoming);
  }
}

float read_temperature(){
  reset();
  delay(1000);
  int sensorValue = analogRead(AN1);
  float voltage = (float)sensorValue * (4.5 / 1023.0);
  float temp = (voltage -0.5) / 0.01;

  Serial.print("TEMPERATURE: ");
  Serial.print(temp);
  Serial.print(" C\n");

  String msg = "Temperature: " + String(temp);
  send_udp(msg.c_str());
  return temp;
}

float read_humidity(){
  reset();
  delay(1000);
  const int NUM_READINGS = 10;
  float total = 0;

  for (int i = 0; i < NUM_READINGS; i++) {
    int sensorValue = analogRead(AN4);
    float voltage = (float(sensorValue) * 3300.0 / 1023.0) / 0.6;
    float humidity = (voltage - 800) / 31;
    total += humidity;
    delay(500); 
  }

  float avgHumidity = total / NUM_READINGS;

  Serial.print("HUMIDITY: ");
  Serial.print(avgHumidity);
  Serial.println(" %\n");

  String msg = "Humidity: " + String(avgHumidity);
  send_udp(msg.c_str());
  return avgHumidity;
  
}

float voltageToCO2(float voltage) {
  const float voltages[] = {0.40, 0.60, 0.80, 1.00, 1.20, 1.40, 1.60, 1.80, 2.00, 2.20, 2.40, 2.60};
  const int co2[] =        { 350,  600,  900, 1200, 1600, 2100, 2700, 3500, 4500, 6000, 8000,10000};
  const int n = sizeof(voltages) / sizeof(voltages[0]);

  if (voltage <= voltages[0]) return co2[0];
  if (voltage >= voltages[n - 1]) return co2[n - 1];

  for (int i = 0; i < n - 1; i++) {
    if (voltage < voltages[i + 1]) {
      float frac = (voltage - voltages[i]) / (voltages[i + 1] - voltages[i]);
      return co2[i] + frac * (co2[i + 1] - co2[i]);
    }
  }

  return -1; // error
}

float read_co2(){
  reset();
  delay(1000);
  digitalWrite(DIG2, HIGH);
  delay(90*1000); //warmup delay

  int sensorValue = analogRead(AN3);
  float voltage = (float)sensorValue * (3.3 / 1023.0)/5.2;
  //voltage *= (5.2 / 3.3);
  float CO2 = voltageToCO2(voltage);


  digitalWrite(DIG2, LOW);
  Serial.print("CO2 voltage: ");
  Serial.print(voltage);

  Serial.print(" | CO2: ");
  Serial.print(CO2);
  Serial.print(" ppm\n");

  String msg = "o2: " + String(voltage);
  send_udp(msg.c_str());
  delay(10*1000); // cooling delay
  return CO2;
}

float read_o2(){
  digitalWrite(DIG2, LOW);
  delay(30000);

  int sensorValue = analogRead(AN3);
  float voltage = (float)sensorValue * (3.3 / 1023.0);
  float O2 = (voltage);

  Serial.print("O2: ");
  Serial.print(voltage);
  Serial.print(" ppm\n");

  String msg = "o2: " + String(voltage);
  send_udp(msg.c_str());
  return O2;
}

float pulse_socket3A(){     // TGS2442 CO sensor
  digitalWrite(DIG7, HIGH);
  delay(14);
  digitalWrite(DIG7, LOW);
  delay(965);
  digitalWrite(DIG6, LOW);
  delay(10);
  digitalWrite(DIG1, HIGH);
  delay(3); 

  int sensorValue = analogRead(AN7);

  delay(2);
  digitalWrite(DIG1, LOW);
  delay(8);
  if(NO2_state)
  {
    digitalWrite(DIG6, HIGH);
  }
  delay(230);

  float voltage = (float)sensorValue * (3.3 / 1023.0);
  float A3 = (voltage);


  delay(10);
  digitalWrite(DIG1, LOW);
  digitalWrite(DIG7, LOW);

  Serial.print("socket3A: ");
  Serial.print(voltage);
  Serial.print("\n");

  String msg = "o2: " + String(voltage);
  send_udp(msg.c_str());
  return A3;
}

void loop() {
  //read_temperature();
  //read_humidity();
  read_co2();
  //pulse_socket3A();

  handle_client();
}
