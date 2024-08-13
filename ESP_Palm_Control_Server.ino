#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

// Set AP credentials
#define AP_SSID "TheOtherESP"
#define AP_PASS "flashmeifyoucan"

// UDP
WiFiUDP UDP;
IPAddress local_IP(192,168,4,1);
IPAddress gateway(192,168,4,1);
IPAddress subnet(255,255,255,0);
#define UDP_PORT 4210

// UDP Buffer
char packetBuffer[UDP_TX_PACKET_MAX_SIZE];
// Motor A connections

int in1 = D3;
int in2 = D4;
// Motor B connections
int in3 = D5;
int in4 = D6;

int t = 0;

void setup() {

    
  // Setup serial port
  Serial.begin(115200);
  Serial.println();

  pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);
	
	// Turn off motors - Initial state
	//digitalWrite(in1, LOW);
	//digitalWrite(in2, LOW);
	//digitalWrite(in3, LOW);
	//digitalWrite(in4, LOW);

  // Begin Access Point
  Serial.println("Starting access point...");
  WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAP(AP_SSID, AP_PASS);
  Serial.println(WiFi.localIP());

  // Begin listening to UDP port
  UDP.begin(UDP_PORT);
  Serial.print("Listening on UDP port ");
  Serial.println(UDP_PORT);

}

void loop() {

  // Receive packet
  UDP.parsePacket();
  delay(100);
  UDP.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
  Serial.println(packetBuffer[0]);
  t = int(packetBuffer[0]);
  Serial.println(t);
  if(t==98){
  digitalWrite(in1, LOW);
	digitalWrite(in2, HIGH);
	digitalWrite(in3, LOW);
	digitalWrite(in4, HIGH);
  }
  else if(t==102){
  digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
	digitalWrite(in3, HIGH);
	digitalWrite(in4, LOW);
  }
 
  else if(t==108){
  digitalWrite(in1, LOW);
	digitalWrite(in2, HIGH);
	digitalWrite(in3, HIGH);
	digitalWrite(in4, LOW);
  }

  else if(t==114){
  digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, HIGH);
  }
  else if(t==115){
  digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
  }
 
}