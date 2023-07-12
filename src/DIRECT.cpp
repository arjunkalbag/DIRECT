/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/student/Desktop/IoT/NfcTest/src/DIRECT.ino"
#include <SPI.h>
#include "MQTT.h"
#include <MFRC522.h>

void setup();
void loop();
void dump_byte_array(byte *buffer, byte bufferSize);
void cardScan();
void lightFunc();
void selfTest();
#line 5 "/Users/student/Desktop/IoT/NfcTest/src/DIRECT.ino"
#define SS_PIN A5
#define RST_PIN D5
#define light1 D4
#define light2 D6
#define light3 D7
#define light4 D8

bool CNCT = true;

SYSTEM_THREAD(ENABLED);

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.

MFRC522::MIFARE_Key key;

void callback(char *CapstoneNode, byte *payload, unsigned int length);

MQTT client("lab.thewcl.com", 1883, callback);

void setup()
{

    pinMode(SS_PIN, INPUT);
    pinMode(RST_PIN, INPUT);
    pinMode(light1, OUTPUT);
    pinMode(light2, OUTPUT);
    pinMode(light3, OUTPUT);
    pinMode(light4, OUTPUT);

    Serial.begin(9600);
    SPI.begin();        // Init SPI bus
    mfrc522.PCD_Init(); // Init MFRC522 card

    // while (!Serial.isConnected())
    //   ;

    selfTest();
}

void loop()
{
    if (client.isConnected())
    {
        client.loop();
        if (CNCT == true)
        {
            Serial.println("Connected");
            CNCT = false;
        }
        lightFunc();
    }
    else
    {
        client.connect(System.deviceID());
        client.subscribe("CapstoneNode");
    }

    if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial())
    {
        cardScan();
    }

    // Halt PICC
    // mfrc522.PICC_HaltA();
    //  // Stop encryption on PCD
    // mfrc522.PCD_StopCrypto1();
}

void dump_byte_array(byte *buffer, byte bufferSize)
{
    for (byte i = 0; i < bufferSize; i++)
    {
        Serial.print(buffer[i] < 0x10 ? " 0" : " ");
        Serial.print(buffer[i], HEX);
    }
}

void callback(char *CapstoneNode, byte *payload, unsigned int length)
{
}

void cardScan()
{
    // HACK: This is necessary to make card reading more consistent. Otherwise, when the card gets
    // stuck reading previously, it won't be able to read anymore.
    digitalWrite(RST_PIN, LOW);
    delay(1);
    digitalWrite(RST_PIN, HIGH);

    Serial.println("Card Present");
    Serial.print(F("Card UID:"));
    dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
    Serial.println();
    byte choice = mfrc522.uid.uidByte[1];

    switch (choice)
    {
    case 0x47:
        digitalWrite(light1, HIGH);
        digitalWrite(light2, LOW);
        digitalWrite(light3, LOW);
        digitalWrite(light4, LOW);
        break;
    case 0xF1:
        digitalWrite(light1, LOW);
        digitalWrite(light2, HIGH);
        digitalWrite(light3, LOW);
        digitalWrite(light4, LOW);
        break;
    case 0x8B:
        digitalWrite(light1, LOW);
        digitalWrite(light2, LOW);
        digitalWrite(light3, HIGH);
        digitalWrite(light4, LOW);
        break;
    case 0x7B:
        digitalWrite(light1, LOW);
        digitalWrite(light2, LOW);
        digitalWrite(light3, LOW);
        digitalWrite(light4, HIGH);
        break;
    }
}

void lightFunc()
{
    int LightOne = digitalRead(light1);
    int LightTwo = digitalRead(light2);
    int LightThree = digitalRead(light3);
    int LightFour = digitalRead(light4);

    if (LightOne == true)
    {
        client.publish("CapstoneNode", "Light 1!");
        Serial.println("L1");
    }
    if (LightTwo == true)
    {
        client.publish("CapstoneNode", "Light 2!");
        Serial.println("L2");
    }
    if (LightThree == true)
    {
        client.publish("CapstoneNode", "Light 3!");
        Serial.println("L3");
    }
    if (LightFour == true)
    {
        client.publish("CapstoneNode", "Light 4!");
        Serial.println("L4");
    }
}

void selfTest()
{
    Serial.println(F("*****************************"));
    Serial.println(F("MFRC522 Digital self test"));
    Serial.println(F("*****************************"));
    mfrc522.PCD_DumpVersionToSerial(); // Show version of PCD - MFRC522 Card Reader
    Serial.println(F("-----------------------------"));
    Serial.println(F("Only known versions supported"));
    Serial.println(F("-----------------------------"));
    Serial.println(F("Performing test..."));
    bool result = mfrc522.PCD_PerformSelfTest(); // perform the test
    Serial.println(F("-----------------------------"));
    Serial.print(F("Result: "));
    if (result)
        Serial.println(F("OK"));
    else
        Serial.println(F("DEFECT or UNKNOWN"));
    Serial.println();
}