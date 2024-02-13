#include <SimpleDHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
int pinDHT11 = 2;
SimpleDHT11 dht11(pinDHT11);

int motor = 12;
int potpin = A0;
int potvalue = 0;
unsigned long lastDHTReadTime = 0;
const int DHTReadInterval = 1200;

void setup()
{
    pinMode(motor, OUTPUT);
    pinMode(potpin, INPUT);
    Serial.begin(9600);

    lcd.begin();
    lcd.backlight();
}

void loop()
{
    byte temperature = 0;
    byte humidity = 0;

    if (millis() - lastDHTReadTime >= DHTReadInterval)
    {
        dht11.read(&temperature, &humidity, NULL);
        lastDHTReadTime = millis();

        lcd.setCursor(0, 0);
        lcd.print("Temp  ");
        lcd.print((int)temperature);
        lcd.print("C");

        lcd.setCursor(0, 1);
        lcd.print("Humidity  ");
        lcd.print((int)humidity);
        lcd.print("%");
        Serial.print("Umiditate: ");
        Serial.println((int)humidity);
    }

    potvalue = analogRead(potpin);
    analogWrite(3, potvalue);
    delay(20);
}
