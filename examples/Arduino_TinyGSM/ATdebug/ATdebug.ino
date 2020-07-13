/*
  This can be used to test AT commands
  and communicate directly with the Module.

  List of SIM7000 AT commands can be found here
  http://www.microchip.ua/simcom/LTE/SIM7000/SIM7000%20Series_AT%20Command%20Manual_V1.04.pdf
*/

#define TINY_GSM_MODEM_SIM7000

#define SerialMon Serial
#define SerialAT Serial1

#define TINY_GSM_DEBUG SerialMon

#include <TinyGsmClient.h>

#define PWR_PIN     4
#define RX          26
#define TX          27

void modem_on() {
  // Set-up modem  power pin
  Serial.println("\nStarting Up Modem...");
  pinMode(PWR_PIN, OUTPUT);
  digitalWrite(PWR_PIN, HIGH);
  delay(10);
  digitalWrite(PWR_PIN, LOW);
  delay(1010);
  digitalWrite(PWR_PIN, HIGH);

  int i = 10;
  delay(10000);
  Serial.println("\nTesting Modem Response...");
  while (i) {
    SerialAT.println("AT");
    if (SerialAT.available()) {
      String r = SerialAT.readString();
      Serial.println(r);
      if ( r.indexOf("OK") >= 0 ) break;;
    }
    delay(1000);
    i--;
  }
}

void setup() {
  SerialMon.begin(9600); // Set console baud rate
  SerialAT.begin(9600, SERIAL_8N1, RX, TX);
  delay(100);
  
  modem_on();

  SerialMon.println(F("***********************************************************"));
  SerialMon.println(F(" You can now send AT commands"));
  SerialMon.println(F(" Enter \"AT\" (without quotes), and you should see \"OK\""));
  SerialMon.println(F(" If it doesn't work, select \"Both NL & CR\" in Serial Monitor"));
  SerialMon.println(F(" DISCLAIMER: Entering AT commands without knowing what they do"));
  SerialMon.println(F(" can have undesired consiquinces..."));
  SerialMon.println(F("***********************************************************"));
}

void loop() {
  while (true) {
    if (SerialAT.available()) {
      SerialMon.write(SerialAT.read());
    }
    if (SerialMon.available()) {
      SerialAT.write(SerialMon.read());
    }
    delay(0);
  }
  Serial.println("Failed");
  setup();
}
