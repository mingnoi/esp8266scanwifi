#include <ESP8266WiFi.h>;
#include <ESP8266WebServer.h>;
 
const char *ssid = "MyESP8266AP";
const char *password = "testpassword";
 
ESP8266WebServer server(80);
 
void handleRoot() {
  server.send(200, "text/html", "<h1>;Hello from ESP8266 AP!</h1> <a href='scan'>scan</a>;");
}

void handleScan() {
  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  String scanResult = "" ;
   
  Serial.println("Scan done");
  
  if (n == 0)
    Serial.println("No Networks Found");
  else
  {
    Serial.print(n);
    Serial.println(" Networks found");
    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);  //Sr. No
      Serial.print(": ");
      Serial.print(WiFi.SSID(i)); //SSID
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i)); //Signal Strength
      Serial.print(") MAC:");
      Serial.print(WiFi.BSSIDstr(i));
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" Unsecured":" Secured");
      delay(10);
      scanResult += "<br>" + String(i + 1) + ": " + String(WiFi.SSID(i)) + " (" + String(WiFi.RSSI(i)) +") MAC:" + String(WiFi.BSSIDstr(i)) + "<br>";
    }
  }
  Serial.println("");
  server.send(200, "text/html", "<h1>;Scan Complete</h1> <a href='scan'>scan Again</a>;" + scanResult);
}
 
void setup() {
 
  Serial.begin(115200);
 
  WiFi.softAP(ssid, password);
 
  Serial.println();
  Serial.print("Server IP address: ");
  Serial.println(WiFi.softAPIP());
  Serial.print("Server MAC address: ");
  Serial.println(WiFi.softAPmacAddress());
 
  server.on("/", handleRoot);
  server.on("/scan", handleScan);
  server.begin();
 
  Serial.println("Server listening");
}
 
void loop() {
  server.handleClient();
}
