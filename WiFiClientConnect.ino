#include <ESP8266WiFi.h>

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("ESP8266 WiFi Scanner");

  Serial.println("Scanning for available networks...");
  int n = WiFi.scanNetworks();
  Serial.println("Scan complete.");
  
  if (n == 0) {
    Serial.println("No networks found.");
  } else {
    Serial.printf("%d networks found:\n", n);

    for (int i = 0; i < n; ++i) {
      Serial.printf("%d: %s (Signal Strength: %d dBm) %s\n", 
                    i + 1, 
                    WiFi.SSID(i).c_str(), 
                    WiFi.RSSI(i),
                    (WiFi.encryptionType(i) == ENC_TYPE_NONE) ? "Open" : "Encrypted");
      delay(10);
    }

    Serial.println("Enter the number of the WiFi network you want to connect to:");
    while (Serial.available() == 0) {}
    int networkIndex = Serial.parseInt() - 1;

    if (networkIndex >= 0 && networkIndex < n) {
      String ssid = WiFi.SSID(networkIndex);
      Serial.print("Selected network: ");
      Serial.println(ssid);

      String password = "";
      while (password.length() == 0) {
        Serial.println("Enter the WiFi password (or leave blank if the network is open):");
        while (Serial.available() == 0) {}
        password = Serial.readString();
        password.trim();
      }

      WiFi.begin(ssid.c_str(), password.c_str());

      Serial.print("Connecting to ");
      Serial.println(ssid);

      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
      }

      Serial.println("");
      Serial.println("WiFi connected");
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());
    } else {
      Serial.println("Invalid network selection.");
    }
  }
}

void loop() {
}
