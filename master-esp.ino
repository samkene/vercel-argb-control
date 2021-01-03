#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include <ArduinoJson.h>
#include <ws2812_i2s.h>

#define NUM_LEDS 9

const char* ssid = "sitnet_2.4G_BA6C5B";
const char* pass = "19cc94ap";

ESP8266WebServer server(80);

static WS2812 ledstrip;
static Pixel_t pixels[NUM_LEDS];
int led = LED_BUILTIN;

void setup() {
  Serial.begin(115200);
  SPIFFS.begin();
  connectWifi();
  startServer();

  ledstrip.init(NUM_LEDS);
}

void loop() {
  server.handleClient();
}

void connectWifi() {
  Serial.print("Connecting to ");
  Serial.print(WiFi.SSID());

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void startServer() {
  server.begin();
  server.on("/", handleRoot);
  server.on("/colordata", handleColorData);
  server.onNotFound(handleNotFound);
  Serial.println("Server started successfully");
}

void handleRoot() {
  File file = SPIFFS.open("/index.html", "r");
  server.streamFile(file, "text/html");
  file.close();
}

void handleNotFound() {
  server.send(404, "text/plain", "404: Not found");
}

void handleColorData() {
  String data = server.arg("plain");
  StaticJsonBuffer<200> jBuffer;
  JsonObject& root = jBuffer.parseObject(data);
  int colorR = root["r"];
  int colorG = root["g"];
  int colorB = root["b"];
  Serial.print(colorR);
  Serial.print(" : ");
  Serial.print(colorG);
  Serial.print(" : ");
  Serial.println(colorB);
  changeColor(colorR, colorG, colorB);
  digitalWrite(led, !digitalRead(led));
}

void changeColor(int r, int g, int b) {
  int i;
  for (i = 0; i < NUM_LEDS; i++) {
    pixels[i].R = r;
    pixels[i].G = g;
    pixels[i].B = b;
  }
  ledstrip.show(pixels);
}
