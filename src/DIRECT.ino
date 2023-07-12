#include "SPI.h"
#include "MQTT.h"
#include "MFRC522.h"
#include "neopixel.h"

#define SS_PIN A5
#define RST_PIN D5
#define LIGHT D4
#define PIXEL_COUNT 16
#define PIXEL_TYPE WS2812B
#define WAIT_TIME 10

bool CNCT = true;

SYSTEM_THREAD(ENABLED);

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

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
    pinMode(LIGHT, OUTPUT);

    strip.begin();
    strip.show();

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
void BlueChange()
{
    colorWipe(strip.Color(0, 0, 60), WAIT_TIME); // blue
    colorWipe(strip.Color(1, 3, 60), WAIT_TIME);
    colorWipe(strip.Color(2, 7, 60), WAIT_TIME);
    colorWipe(strip.Color(3, 11, 60), WAIT_TIME);
    colorWipe(strip.Color(4, 15, 60), WAIT_TIME);
    colorWipe(strip.Color(5, 19, 60), WAIT_TIME);
    colorWipe(strip.Color(6, 22, 60), WAIT_TIME); // blue/lightblue
    colorWipe(strip.Color(7, 26, 60), WAIT_TIME);
    colorWipe(strip.Color(8, 30, 60), WAIT_TIME);
    colorWipe(strip.Color(9, 34, 60), WAIT_TIME);
    colorWipe(strip.Color(10, 37, 60), WAIT_TIME);
    colorWipe(strip.Color(11, 41, 60), WAIT_TIME);
    colorWipe(strip.Color(12, 45, 60), WAIT_TIME); // light blue
    colorWipe(strip.Color(11, 41, 60), WAIT_TIME);
    colorWipe(strip.Color(10, 37, 60), WAIT_TIME);
    colorWipe(strip.Color(9, 34, 60), WAIT_TIME);
    colorWipe(strip.Color(8, 30, 60), WAIT_TIME);
    colorWipe(strip.Color(7, 26, 60), WAIT_TIME);
    colorWipe(strip.Color(6, 22, 60), WAIT_TIME); // lightblue/blue
    colorWipe(strip.Color(5, 19, 60), WAIT_TIME);
    colorWipe(strip.Color(4, 15, 60), WAIT_TIME);
    colorWipe(strip.Color(3, 11, 60), WAIT_TIME);
    colorWipe(strip.Color(2, 7, 60), WAIT_TIME);
    colorWipe(strip.Color(1, 3, 60), WAIT_TIME);
    colorWipe(strip.Color(0, 0, 60), WAIT_TIME); // blue
    colorWipe(strip.Color(0, 0, 57), WAIT_TIME);
    colorWipe(strip.Color(0, 0, 55), WAIT_TIME);
    colorWipe(strip.Color(0, 0, 52), WAIT_TIME);
    colorWipe(strip.Color(0, 0, 49), WAIT_TIME);
    colorWipe(strip.Color(0, 0, 47), WAIT_TIME);
    colorWipe(strip.Color(0, 0, 45), WAIT_TIME); // blue/navy
    colorWipe(strip.Color(0, 0, 42), WAIT_TIME);
    colorWipe(strip.Color(0, 0, 40), WAIT_TIME);
    colorWipe(strip.Color(0, 0, 37), WAIT_TIME);
    colorWipe(strip.Color(0, 0, 35), WAIT_TIME);
    colorWipe(strip.Color(0, 0, 32), WAIT_TIME);
    colorWipe(strip.Color(0, 0, 30), WAIT_TIME); // navyblue
    colorWipe(strip.Color(0, 0, 32), WAIT_TIME);
    colorWipe(strip.Color(0, 0, 35), WAIT_TIME);
    colorWipe(strip.Color(0, 0, 37), WAIT_TIME);
    colorWipe(strip.Color(0, 0, 40), WAIT_TIME);
    colorWipe(strip.Color(0, 0, 42), WAIT_TIME);
    colorWipe(strip.Color(0, 0, 45), WAIT_TIME); // navy/blue
    colorWipe(strip.Color(0, 0, 47), WAIT_TIME);
    colorWipe(strip.Color(0, 0, 49), WAIT_TIME);
    colorWipe(strip.Color(0, 0, 52), WAIT_TIME);
    colorWipe(strip.Color(0, 0, 55), WAIT_TIME);
    colorWipe(strip.Color(0, 0, 57), WAIT_TIME);
    // back to blue
}
void RedChange()
{
    colorWipe(strip.Color(60, 0, 0), WAIT_TIME); // red
    colorWipe(strip.Color(60, 1, 1), WAIT_TIME);
    colorWipe(strip.Color(60, 2, 2), WAIT_TIME);
    colorWipe(strip.Color(60, 3, 3), WAIT_TIME);
    colorWipe(strip.Color(60, 4, 4), WAIT_TIME);
    colorWipe(strip.Color(60, 5, 5), WAIT_TIME);
    colorWipe(strip.Color(60, 6, 6), WAIT_TIME); // red/pink
    colorWipe(strip.Color(60, 7, 7), WAIT_TIME);
    colorWipe(strip.Color(60, 8, 8), WAIT_TIME);
    colorWipe(strip.Color(60, 9, 9), WAIT_TIME);
    colorWipe(strip.Color(60, 10, 10), WAIT_TIME);
    colorWipe(strip.Color(60, 11, 11), WAIT_TIME);
    colorWipe(strip.Color(60, 12, 12), WAIT_TIME); // pink
    colorWipe(strip.Color(60, 11, 11), WAIT_TIME);
    colorWipe(strip.Color(60, 10, 10), WAIT_TIME);
    colorWipe(strip.Color(60, 9, 9), WAIT_TIME);
    colorWipe(strip.Color(60, 8, 8), WAIT_TIME);
    colorWipe(strip.Color(60, 7, 7), WAIT_TIME);
    colorWipe(strip.Color(60, 6, 6), WAIT_TIME); // pink/red
    colorWipe(strip.Color(60, 5, 5), WAIT_TIME);
    colorWipe(strip.Color(60, 4, 4), WAIT_TIME);
    colorWipe(strip.Color(60, 3, 3), WAIT_TIME);
    colorWipe(strip.Color(60, 2, 2), WAIT_TIME);
    colorWipe(strip.Color(60, 1, 1), WAIT_TIME);
    colorWipe(strip.Color(60, 0, 0), WAIT_TIME); // red
    colorWipe(strip.Color(57, 0, 0), WAIT_TIME);
    colorWipe(strip.Color(55, 0, 0), WAIT_TIME);
    colorWipe(strip.Color(52, 0, 0), WAIT_TIME);
    colorWipe(strip.Color(49, 0, 0), WAIT_TIME);
    colorWipe(strip.Color(47, 0, 0), WAIT_TIME);
    colorWipe(strip.Color(45, 0, 0), WAIT_TIME); // red/maroon
    colorWipe(strip.Color(42, 0, 0), WAIT_TIME);
    colorWipe(strip.Color(40, 0, 0), WAIT_TIME);
    colorWipe(strip.Color(37, 0, 0), WAIT_TIME);
    colorWipe(strip.Color(35, 0, 0), WAIT_TIME);
    colorWipe(strip.Color(32, 0, 0), WAIT_TIME);
    colorWipe(strip.Color(30, 0, 0), WAIT_TIME); // maroon
    colorWipe(strip.Color(32, 0, 0), WAIT_TIME);
    colorWipe(strip.Color(35, 0, 0), WAIT_TIME);
    colorWipe(strip.Color(37, 0, 0), WAIT_TIME);
    colorWipe(strip.Color(40, 0, 0), WAIT_TIME);
    colorWipe(strip.Color(42, 0, 0), WAIT_TIME);
    colorWipe(strip.Color(45, 0, 0), WAIT_TIME); // maroon/red
    colorWipe(strip.Color(47, 0, 0), WAIT_TIME);
    colorWipe(strip.Color(49, 0, 0), WAIT_TIME);
    colorWipe(strip.Color(52, 0, 0), WAIT_TIME);
    colorWipe(strip.Color(55, 0, 0), WAIT_TIME);
    colorWipe(strip.Color(57, 0, 0), WAIT_TIME);
    // back to red
}
void colorWipe(uint32_t c, uint8_t wait)
{
    for (uint16_t i = 0; i < strip.numPixels(); i++)
    {
        strip.setPixelColor(i, c);
        strip.show();
        delay(wait);
    }
}