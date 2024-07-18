#include <FirebaseESP32.h>

FirebaseData firebaseData;
FirebaseConfig firebaseConfig;
FirebaseAuth firebaseAuth;

#define FIREBASE_HOST "https://training-smart-trash-bin-default-rtdb.asia-southeast1.firebasedatabase.app"
#define FIREBASE_AUTH "joAFigWH6tHGNgJ3MHS7fxTgKVqrxOAHReNusYJc"

class FirebaseController{
public:
    void setupFirebase(){
        firebaseConfig.host = FIREBASE_HOST;
        firebaseConfig.signer.tokens.legacy_token = FIREBASE_AUTH;
        Firebase.begin(&firebaseConfig, &firebaseAuth);
        Firebase.reconnectWiFi(true);
    }
    void sendToFirebase(int level, float lat, float lng) {
        String path = "/trash-bin-database/bin-1";  // Adjust the path as necessary
        if(lat == 0 || lng == 0){
            lat = 11.5703844;
            lng = 104.8939048;
        }
        FirebaseJson json;
        json.set("fill", level);
        json.set("lat", lat);
        json.set("lng", lng);

        if (Firebase.updateNode(firebaseData, path, json)) {
        Serial.println("Data sent to Firebase successfully");
        } else {
            Serial.println("Failed to send data to Firebase");
        }
    }
};
