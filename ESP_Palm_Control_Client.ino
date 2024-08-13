#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

float ax, ay, az, G;
 
// Set WiFi credentials
#define WIFI_SSID "TheOtherESP"
#define WIFI_PASS "flashmeifyoucan"

// UDP
WiFiUDP UDP;
IPAddress remote_IP(192,168,4,1);
#define UDP_PORT 4210

void setup() {

  // Setup IO
  //pinMode(2, INPUT);
  
  // Setup serial port
  Serial.begin(115200);
  Serial.println();
  
  while (!Serial) {
    delay(10); // will pause Zero, Leonardo, etc until serial console opens
  }

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  
  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.println("");
  delay(100);
  
  // Begin WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  WiFi.mode(WIFI_STA);
 
  // Connecting to WiFi...
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  // Loop continuously while WiFi is not connected
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
 
  // Connected to WiFi
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  // Begin UDP port
  UDP.begin(UDP_PORT);
  Serial.print("Opening UDP port ");
  Serial.println(UDP_PORT);
 
}
 
void loop() {

  // Read button
  //char buttonState = digitalRead(2);
  
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  
  ax = a.acceleration.x;
  ay = a.acceleration.y;
  az = a.acceleration.z;

  G = 12;

  UDP.beginPacket(remote_IP, UDP_PORT);
  
  if (-ay > G*sin(38))// && az < g*cos(40) && abs(ax) < g/4)
  {
	UDP.write("f");
  Serial.println("f");
  }
  
  if (ay > G*sin(38))// && az < g*cos(40) && abs(ax) < g/4)
  {
	UDP.write("b");
  Serial.println("b");
  }
  
  if (ax > G*sin(38))// && az < g*cos(40) && abs(ay) < g/4)
  {
	UDP.write("r");
  Serial.println("r");
  }
  
  if (-ax > G*sin(38))// && az < g*cos(40) && abs(ay) < g/4)
  {
	UDP.write("l");
  Serial.println("l");
  }

  else
  {
  UDP.write("s");
  Serial.println("s");
  }
  
  // Send Packet
  //UDP.write(buttonState);
  UDP.endPacket();
  delay(10);
  
}