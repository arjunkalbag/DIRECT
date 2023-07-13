#include "SPI.h"
#include "MQTT.h"
#include "MFRC522.h"
#include "neopixel.h"

#define SS_PIN A5
#define RST_PIN D5
#define MUSIC_RST D2
#define LIGHT D4
#define PIXEL_COUNT 16
#define PIXEL_TYPE WS2812B
#define WAIT_TIME 1

#define song1 D8
#define song2 D7
#define song3 D6

bool CNCT = true;

SYSTEM_THREAD(ENABLED);

Adafruit_NeoPixel strip(PIXEL_COUNT, LIGHT, PIXEL_TYPE);

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.

MFRC522::MIFARE_Key key;

void callback(char *CapstoneNode, byte *payload, unsigned int length);

MQTT client("lab.thewcl.com", 1883, callback);

void setup()
{

    pinMode(SS_PIN, INPUT);
    pinMode(RST_PIN, INPUT);
    pinMode(MUSIC_RST, OUTPUT);
    pinMode(LIGHT, OUTPUT);

    pinMode(song1, OUTPUT);
    digitalWrite(song1, HIGH);
    pinMode(song2, OUTPUT);
    digitalWrite(song2, HIGH);
    pinMode(song3, OUTPUT);
    digitalWrite(song3, HIGH);

    strip.begin();
    strip.show();

    Serial.begin(9600);
    SPI.begin();        // Init SPI bus
    mfrc522.PCD_Init(); // Init MFRC522 card

    while (!Serial.isConnected())
        ;

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
        client.publish("CapstoneNode", "See You Again - Tyler, The Creator (feat. Kali Uchis");
        Serial.println("L1");
        PurpleChange();
        playSong(song1);
        break;
    case 0xF1:
        client.publish("CapstoneNode", "Sparks - Coldplay");
        Serial.println("L2");
        RedChange();
        playSong(song2);
        break;
    case 0x8B:
        client.publish("CapstoneNode", "pluh!");
        Serial.println("L3");
        BlueChange();
        playSong(song3);
        break;
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
void PurpleChange()
{
    colorWipe(strip.Color(36, 24, 48), WAIT_TIME); // purple
    colorWipe(strip.Color(35, 22, 46), WAIT_TIME);
    colorWipe(strip.Color(35, 20, 44), WAIT_TIME);
    colorWipe(strip.Color(34, 18, 43), WAIT_TIME);
    colorWipe(strip.Color(34, 16, 41), WAIT_TIME);
    colorWipe(strip.Color(33, 14, 40), WAIT_TIME);
    colorWipe(strip.Color(33, 12, 39), WAIT_TIME); // purple/violet
    colorWipe(strip.Color(32, 10, 37), WAIT_TIME);
    colorWipe(strip.Color(32, 8, 36), WAIT_TIME);
    colorWipe(strip.Color(31, 6, 34), WAIT_TIME);
    colorWipe(strip.Color(31, 4, 33), WAIT_TIME);
    colorWipe(strip.Color(30, 2, 31), WAIT_TIME);
    colorWipe(strip.Color(30, 0, 30), WAIT_TIME); // violet
    colorWipe(strip.Color(30, 2, 31), WAIT_TIME);
    colorWipe(strip.Color(31, 4, 33), WAIT_TIME);
    colorWipe(strip.Color(31, 6, 34), WAIT_TIME);
    colorWipe(strip.Color(32, 8, 36), WAIT_TIME);
    colorWipe(strip.Color(32, 10, 37), WAIT_TIME);
    colorWipe(strip.Color(33, 12, 39), WAIT_TIME); // violet/purple
    colorWipe(strip.Color(33, 14, 40), WAIT_TIME);
    colorWipe(strip.Color(34, 16, 41), WAIT_TIME);
    colorWipe(strip.Color(34, 18, 43), WAIT_TIME);
    colorWipe(strip.Color(35, 20, 44), WAIT_TIME);
    colorWipe(strip.Color(35, 22, 46), WAIT_TIME);
    colorWipe(strip.Color(36, 24, 48), WAIT_TIME); // purple
    colorWipe(strip.Color(38, 22, 49), WAIT_TIME);
    colorWipe(strip.Color(40, 20, 50), WAIT_TIME);
    colorWipe(strip.Color(42, 18, 51), WAIT_TIME);
    colorWipe(strip.Color(44, 16, 52), WAIT_TIME);
    colorWipe(strip.Color(46, 14, 53), WAIT_TIME);
    colorWipe(strip.Color(48, 12, 54), WAIT_TIME); // purple/magenta
    colorWipe(strip.Color(50, 10, 55), WAIT_TIME);
    colorWipe(strip.Color(52, 8, 56), WAIT_TIME);
    colorWipe(strip.Color(54, 6, 57), WAIT_TIME);
    colorWipe(strip.Color(56, 4, 58), WAIT_TIME);
    colorWipe(strip.Color(58, 2, 59), WAIT_TIME);
    colorWipe(strip.Color(60, 0, 60), WAIT_TIME); // magenta
    colorWipe(strip.Color(58, 2, 59), WAIT_TIME);
    colorWipe(strip.Color(56, 4, 58), WAIT_TIME);
    colorWipe(strip.Color(54, 6, 57), WAIT_TIME);
    colorWipe(strip.Color(52, 8, 56), WAIT_TIME);
    colorWipe(strip.Color(50, 10, 55), WAIT_TIME);
    colorWipe(strip.Color(48, 12, 54), WAIT_TIME); // magenta/purple
    colorWipe(strip.Color(46, 14, 53), WAIT_TIME);
    colorWipe(strip.Color(44, 16, 52), WAIT_TIME);
    colorWipe(strip.Color(42, 18, 51), WAIT_TIME);
    colorWipe(strip.Color(40, 20, 50), WAIT_TIME);
    colorWipe(strip.Color(38, 22, 49), WAIT_TIME);
    // back to purple
}
void GreenChange()
{
    colorWipe(strip.Color(0, 30, 0), WAIT_TIME); // green
    colorWipe(strip.Color(0, 32, 0), WAIT_TIME);
    colorWipe(strip.Color(0, 35, 0), WAIT_TIME);
    colorWipe(strip.Color(0, 37, 0), WAIT_TIME);
    colorWipe(strip.Color(0, 40, 0), WAIT_TIME);
    colorWipe(strip.Color(0, 42, 0), WAIT_TIME);
    colorWipe(strip.Color(0, 45, 0), WAIT_TIME); // green/lime
    colorWipe(strip.Color(0, 47, 0), WAIT_TIME);
    colorWipe(strip.Color(0, 49, 0), WAIT_TIME);
    colorWipe(strip.Color(0, 52, 0), WAIT_TIME);
    colorWipe(strip.Color(0, 55, 0), WAIT_TIME);
    colorWipe(strip.Color(0, 57, 0), WAIT_TIME);
    colorWipe(strip.Color(0, 60, 0), WAIT_TIME); // lime
    colorWipe(strip.Color(0, 57, 0), WAIT_TIME);
    colorWipe(strip.Color(0, 55, 0), WAIT_TIME);
    colorWipe(strip.Color(0, 52, 0), WAIT_TIME);
    colorWipe(strip.Color(0, 49, 0), WAIT_TIME);
    colorWipe(strip.Color(0, 47, 0), WAIT_TIME);
    colorWipe(strip.Color(0, 45, 0), WAIT_TIME); // lime/green
    colorWipe(strip.Color(0, 42, 0), WAIT_TIME);
    colorWipe(strip.Color(0, 40, 0), WAIT_TIME);
    colorWipe(strip.Color(0, 37, 0), WAIT_TIME);
    colorWipe(strip.Color(0, 35, 0), WAIT_TIME);
    colorWipe(strip.Color(0, 32, 0), WAIT_TIME);
    colorWipe(strip.Color(0, 30, 0), WAIT_TIME); // green
    colorWipe(strip.Color(0, 30, 0), WAIT_TIME);
    colorWipe(strip.Color(1, 31, 1), WAIT_TIME);
    colorWipe(strip.Color(1, 31, 1), WAIT_TIME);
    colorWipe(strip.Color(2, 32, 2), WAIT_TIME);
    colorWipe(strip.Color(2, 32, 2), WAIT_TIME);
    colorWipe(strip.Color(3, 33, 3), WAIT_TIME); // green/seagreen
    colorWipe(strip.Color(3, 33, 3), WAIT_TIME);
    colorWipe(strip.Color(4, 34, 4), WAIT_TIME);
    colorWipe(strip.Color(4, 34, 4), WAIT_TIME);
    colorWipe(strip.Color(5, 35, 5), WAIT_TIME);
    colorWipe(strip.Color(5, 35, 5), WAIT_TIME);
    colorWipe(strip.Color(6, 36, 6), WAIT_TIME); // seagreen
    colorWipe(strip.Color(5, 35, 5), WAIT_TIME);
    colorWipe(strip.Color(5, 35, 5), WAIT_TIME);
    colorWipe(strip.Color(4, 34, 4), WAIT_TIME);
    colorWipe(strip.Color(4, 34, 4), WAIT_TIME);
    colorWipe(strip.Color(3, 33, 3), WAIT_TIME);
    colorWipe(strip.Color(3, 33, 3), WAIT_TIME); // seagreen/green
    colorWipe(strip.Color(2, 32, 2), WAIT_TIME);
    colorWipe(strip.Color(2, 32, 2), WAIT_TIME);
    colorWipe(strip.Color(1, 31, 1), WAIT_TIME);
    colorWipe(strip.Color(1, 31, 1), WAIT_TIME);
    colorWipe(strip.Color(0, 30, 0), WAIT_TIME);
    // back to green
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

void playSong(pin_t songPin)
{
    digitalWrite(MUSIC_RST, LOW);
    delay(10);
    digitalWrite(MUSIC_RST, HIGH);
    delay(1000);
    digitalWrite(songPin, LOW);
    delay(100);
    digitalWrite(songPin, HIGH);
}