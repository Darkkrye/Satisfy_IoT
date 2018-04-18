
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>


#define ROUGE D1
#define ORANGE D2
#define VERT D3

int buttonState = 0;
int UID = 0;

const char* ssid = "S10 PRO";
const char* password = "a2e79cd42338";

const char* host_c = "http://satisfyapi.herokuapp.com/api/satisfaction";
const String host = "http://satisfyapi.herokuapp.com/api/satisfaction";
const String route = "/api/satisfaction";
const int port = 443;


//WiFiClientSecure client;

HTTPClient client;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(ROUGE, INPUT_PULLUP);
  pinMode(ORANGE, INPUT_PULLUP);
  pinMode(VERT, INPUT_PULLUP);

  Serial.begin(115200);

  // WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  digitalWrite(LED_BUILTIN, LOW);

  //connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Wi-Fi connected successfully");




}

// the loop function runs over and over again forever
void loop() {
  // read the state of the pushbutton value:


  if (digitalRead(ROUGE) == 0) {
    Serial.println("2");
    callAPI(2);
  } else if (digitalRead(ORANGE) == 0 ) {
    Serial.println("1");
    callAPI(1);
  } else if (digitalRead(VERT) == 0) {
    Serial.println("0");
    callAPI(0);
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("error internet");
  }

  //digitalWrite(LED_BUILTIN, HIGH);



}


void log() {
  Serial.print("ROUGE");
  Serial.println(digitalRead(ROUGE));

  Serial.print("ORANGE");
  Serial.println(digitalRead(ORANGE));


  Serial.print("VERT");
  Serial.println(digitalRead(VERT));

}
void callAPI(int btn) {

  String json = "{ \"id\" : 0, \"id_button\" : " + String(btn) + " }";

  client.begin(host);
  client.addHeader("Content-Type", "application/json");

  int response = client.POST(json);
  delay(500);
  String payload = client.getString();

  Serial.println(response);


  Serial.println(payload);

  client.end();
  //
  //    client.println("POST / HTTP/1.1");
  //    client.println("Host: " + host + route);
  //    client.println("Accept: */*");
  //    client.println("Content-Type: application/json");
  //    client.print("Content-Length: ");
  //    client.println(json.length());
  //    client.println();
  //    client.print(json);

  Serial.println(json);


  delay(500);
  //
  //  if (client.connected()) {
  //    client.stop();  // DISCONNECT FROM THE SERVER




}




