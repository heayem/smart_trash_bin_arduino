#include <WiFi.h>
WiFiClient espClient;

class WiFiController{
public:
    void setup() {
        for (int i = 0; i < sizeof(wifiSSID) / sizeof(wifiSSID[0]); ++i) {
            if (connectToWiFi(wifiSSID[i], wifiPassword[i])) {
                if (WiFi.status() == WL_CONNECTED) {
                    Serial.print("IP Address: ");
                    Serial.println(WiFi.localIP());
                    String localIP = WiFi.localIP().toString();
                }
                break;
            }
        }
    }

private:
    static constexpr int maxAttempt = 5;
    const char* wifiSSID[5] = {"Leyy Leyy", "SMART-WIFI-F215", "Phanna", "Nova Coffee F1", "Norak3"};
    const char* wifiPassword[5] = {"Leyy0824", "66C90FC7", "qwerty123", "Nova1234", "Norak@2022"};

    bool connectToWiFi(const char* ssid, const char* password) {
        WiFi.begin(ssid, password);
        unsigned long startAttemptTime = millis();
        while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 5000) { // 5 second timeout
            delay(100);
        }
        return WiFi.status() == WL_CONNECTED;
    }
};