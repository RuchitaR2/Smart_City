#define BLYNK_TEMPLATE_ID "TMPL359zRjOHD"
#define BLYNK_TEMPLATE_NAME "Smart Parking System"
#define BLYNK_AUTH_TOKEN "A-K8IJ1dnovMPRsWIpR_3G7n0RtXzhTI"

#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <BlynkSimpleEsp8266.h> // Include the appropriate Blynk library for your hardware
LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo myservo;

#define ir_enter D0
#define ir_back D7

#define ir_car1 D6
#define ir_car2 D4
#define ir_car3 D8
#define ir_car4 D5


#define gate_light S2
#define parking_light S3

unsigned long previousMillis = 0;  // Variable to store the last time gate_light was updated
const unsigned long interval = 5000;  // Interval in milliseconds (5 seconds)

int S1 = 0, S2 = 0, S3 = 0, S4 = 0;
int flag1 = 0, flag2 = 0;
int slot = 4;

char ssid[] = "URVASH"; // Your WiFi SSID
char pass[] = "bhavesh2003"; // Your WiFi password

void setup() {
  Serial.begin(9600);

  pinMode(ir_car1, INPUT);
  pinMode(ir_car2, INPUT);
  pinMode(ir_car3, INPUT);
  pinMode(ir_car4, INPUT);

  pinMode(ir_enter, INPUT);
  pinMode(ir_back, INPUT);

  pinMode(gate_light,OUTPUT);
  pinMode(parking_light,OUTPUT);
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  myservo.attach(D3);
  myservo.write(90);


  lcd.init();
  lcd.backlight();
  lcd.clear();
  delay(200);
  lcd.setCursor(0, 0);
  lcd.print("Welcome To Smart");
  lcd.setCursor(0, 1);
  lcd.print("Parking System");
  delay(3000);
  lcd.clear();

  Read_Sensor();

  int total = S1 + S2 + S3 + S4;
  slot = slot - total;
}

void loop() {

  Read_Sensor();
  Blynk.virtualWrite(V0, !digitalRead(ir_car1)); // Assuming V0 is the virtual pin in your Blynk project for ir_car1
  Blynk.virtualWrite(V1, !digitalRead(ir_car2)); // Assuming V1 is the virtual pin in your Blynk project for ir_car2
  Blynk.virtualWrite(V2, !digitalRead(ir_car3)); // Assuming V2 is the virtual pin in your Blynk project for ir_car3
  Blynk.virtualWrite(V3, !digitalRead(ir_car4)); // Assuming V3 is the virtual pin in your Blynk project for ir_car4
  lcd.setCursor(0, 0);
  lcd.print("Slot: ");
  lcd.print(slot);
  lcd.setCursor(8, 0);
  if (S1 == 1) {
    lcd.print("S1:F ");
  } else {
    lcd.print("S1:E ");
  }

  lcd.setCursor(0, 1);
  if (S2 == 1) {
    lcd.print("S2:F ");
  } else {
    lcd.print("S2:E ");
  }

  lcd.setCursor(5, 1);
  if (S3 == 1) {
    lcd.print("S3:F ");
  } else {
    lcd.print("S3:E ");
  }

  lcd.setCursor(10, 1);
  if (S4 == 1) {
    lcd.print("S4:F ");
  } else {
    lcd.print("S4:E ");
  }

  if (digitalRead(ir_enter) == HIGH || digitalRead(ir_back) == HIGH) {
    // Set gate_light HIGH
    digitalWrite(gate_light, HIGH);
    // Save the current time
    previousMillis = millis();
  } else {
    // Check if it's been 5 seconds since gate_light was set HIGH
    if (millis() - previousMillis >= interval) {
      // If 5 seconds have passed, set gate_light LOW
      digitalWrite(gate_light, LOW);
    }
  }

  if (digitalRead(ir_enter) == 0 && flag1 == 0) {
    if (slot > 0) {
      flag1 = 1;
      if (flag2 == 0) {
        myservo.write(180);
        slot = slot - 1;
      }
    } else {
      lcd.setCursor(0, 0);
      lcd.print(" Sorry Parking Full ");
      delay(1500);
    }
  }

  if (digitalRead(ir_back) == 0 && flag2 == 0) {
    flag2 = 1;
    if (flag1 == 0) {
      myservo.write(180);
      slot = slot + 1;
    }
  }

  if (flag1 == 1 && flag2 == 1) {
    delay(1000);
    myservo.write(90);
    flag1 = 0, flag2 = 0;
  }

  delay(1);
}

void Read_Sensor() {
  S1 = 0, S2 = 0, S3 = 0, S4 = 0;

  if (digitalRead(ir_car1) == 0) {
    S1 = 1;
  }
  if (digitalRead(ir_car2) == 0) {
    S2 = 1;
  }
  if (digitalRead(ir_car3) == 0) {
    S3 = 1;
  }
  if (digitalRead(ir_car4) == 0) {
    S4 = 1;
  }
}
