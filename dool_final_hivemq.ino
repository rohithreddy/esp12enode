#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Servo.h>
// Update these with values suitable for your network.
const char* ssid = "ssid";
const char* password = "password";
//const char* mqtt_server = "192.168.0.104";
const char* mqtt_server = "broker.hivemq.com";

const short int BUILTIN_LED1 = 2;

Servo myservo;  // create servo object to control a servo
WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(100);
  // We start by connecting to a WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());
  pinMode(BUILTIN_LED1, OUTPUT);
  digitalWrite(BUILTIN_LED1, LOW);
  delay(3000);
  digitalWrite(BUILTIN_LED1, HIGH);
  delay(3000);
  digitalWrite(BUILTIN_LED1, LOW);
  delay(4000);
  digitalWrite(BUILTIN_LED1, HIGH);
  Serial.println(WiFi.localIP());
}
char message_buff[100];
void callback(char* topic, byte* payload, unsigned int length)
{
  Serial.print("Command from MQTT broker is : [");
  Serial.print(topic);
  client.publish("dool_feeder_proto/status", topic);
  if (length == 4){
    digitalWrite(BUILTIN_LED1, LOW);
    delay(700);
    digitalWrite(BUILTIN_LED1, HIGH);
    delay(700);
    digitalWrite(BUILTIN_LED1, LOW);
    delay(700);
    digitalWrite(BUILTIN_LED1, HIGH);
    myservo.attach(D1);
    int pos;
    for(pos = 0; pos <= 180; pos += 1) // goes from 0 degrees to 180 degrees
    {                                  // in steps of 1 degree 
      myservo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(15);                       // waits 15ms for the servo to reach the position 
    }
    for(pos = 180; pos>=0; pos-=1)     // goes from 180 degrees to 0 degrees 
    {
      myservo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(15);                       // waits 15ms for the servo to reach the position 
    }
    myservo.detach();
    client.publish("dool_feeder_proto/status","dool_has_been_fed");
    }
    else {
      digitalWrite(BUILTIN_LED1, LOW);
      delay(700);
      digitalWrite(BUILTIN_LED1, HIGH);
      delay(700);
      digitalWrite(BUILTIN_LED1, LOW);
      delay(700);
      digitalWrite(BUILTIN_LED1, HIGH);
      }
}//end callback

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-doolfeeder-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    //if you MQTT broker has clientID,username and password
    //please change following line to    if (client.connect(clientId,userName,passWord))
    if (client.connect(clientId.c_str()))
    {
      Serial.println("connected");
      //once connected to MQTT broker, subscribe command if any
      client.publish("dool_feeder_proto/status", "Hello From Dool Feeder + Connected Now");
      client.subscribe("dool_feeder_proto/control");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 6 seconds before retrying
      client.publish("dool_feeder_proto/status", "Hello From Dool Feeder + Connected Again");
      delay(6000);
    }
  }
} //end reconnect()

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

}
