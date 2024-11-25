// #include <Arduino.h>
// #include <SoftwareSerial.h>

// SoftwareSerial BT(13,2);

// void setup(){
//     Serial.begin(9600);
//     BT.begin(9600);
//     Serial.print("Bluetooth communication started");
// }

// void loop(){
//     if (BT.available()){
//         char incoming = BT.read();
//         Serial.print("Received:");
//         Serial.println(incoming);
//     }

//     if (Serial.available()){
//         char outgoing = Serial.read();
//         BT.print(outgoing);
//     }
// }
