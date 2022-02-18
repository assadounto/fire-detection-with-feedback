#include <DFPlayerMini_Fast.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <SoftwareSerial.h>
SoftwareSerial mySerial(D7, D8); // RX, TX
DFPlayerMini_Fast myMP3;

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
int alarm = D2;
int sensor = A0;
int flame = D5;

char auth[] = "dOnKpLhBldtJXEJlWBHoZkDvQP1myxSU";
char ssid[] = "Julius53";
char pass[] = "12345678";

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  myMP3.begin(mySerial);
  myMP3.volume(25);
  lcd.init();                      // initialize the lcd
  lcd.init();
  lcd.backlight();
  myMP3.play(1);
  pinMode(alarm, OUTPUT);
  pinMode(sensor, INPUT);
  pinMode(flame, INPUT);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" connecting to ");
  lcd.setCursor(0, 1);
  lcd.print("wifi (Julius53)");
  Blynk.begin(auth, ssid, pass);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("wifi connected");
  delay(1500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("FLAME");
  lcd.setCursor(11, 0);
  lcd.print("SMOKE");

}

void loop() {
  Blynk.run();
  int readSensor = analogRead(sensor);
  int readflame = digitalRead(flame);

  if (readflame == 1 ) {
    lcd.setCursor(1, 1);
    lcd.print("YES");
    Blynk.email("Juliusc230@gmail.com", "Safty Alert", "fire dectected in electrical department");
    Blynk.notify("fire dectected in electrical department");
    Serial.print("email sent"); myMP3.play(4);
    delay(14000);
    
  }

  else {
    digitalWrite(alarm, LOW);
    lcd.setCursor(1, 1);
    lcd.print("NO ");

  }
  if ( readSensor >= 150 ) {
    lcd.setCursor(12, 1);
    lcd.print("YES");
    Blynk.email("Juliusc230@gmail.com", "Safty Alert", "Smoke dectected in electrical department");
    Blynk.notify("Smoke dectected in electrical department");
    Serial.print("email sent"); myMP3.play(2);
    delay(10000);

  }


  else {
    digitalWrite(alarm, LOW);
    lcd.setCursor(12, 1);
    lcd.print("NO ");

  }
  Serial.println(String("Smoke:") + String(readSensor) + String("flame:") + String(readflame));
}
