
// void setupCommunication()
// {
//   BLEService textService("0x1800");  // genermic access
//   BLECharacteristic textCharacteristic("0x1801", BLERead | BLENotify);  // generic attribute 

//   if (!BLE.begin()) 
//   {
//     Serial.println("Starting Bluetooth failed!");
//   }

//   BLE.setLocalName("UFO Lamp");  // Set the local name
//   BLE.setAdvertisedService(textService);  // Advertise the text service
//   textService.addCharacteristic(textCharacteristic);  // Add the characteristic to the service
//   BLE.addService(textService);  // Add the service to the peripheral device

//   BLE.advertise();  // Start advertising the service

//   Serial.println("Bluetooth device is ready to pair!");
// }

// String receiveMessage()
// {
//   BLEDevice central = BLE.central();  // Check if a central device (e.g., phone) connects

//   if (central) 
//   {
//     Serial.print("Connected to central: ");
//     Serial.println(central.address());

//     // While the central device is connected
//     while (central.connected()) 
//     {
//       if (textCharacteristic.written()) 
//       {  // Check if data was written to the characteristic
//         String receivedText = textCharacteristic.value();  // Get the received text
//         Serial.print("Received text: ");
//         Serial.println(receivedText);
//         return receivedText;
//       }
//     }
//   }
//   return "";
// }