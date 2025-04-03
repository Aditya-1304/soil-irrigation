/*
   Arduino Water Irrigation System

   Components:
   - Arduino Uno
   - LCD I2C 16x2 Display (I2C address: 0x27)
   - Soil Moisture Sensor (analog sensor)
   - 5V Relay Module (to control a water pump)
   - Water Pump (motor) with its battery
   - Breadboard (for circuit connections)

   Wiring Notes:
   - The breadboard is used to organize connections and distribute power.
   - Ensure you have a common ground between Arduino, sensor, relay, and any external power supplies.

   Connections (see below for details):
   1. LCD I2C Display: Connect via the breadboard’s power rails.
   2. Soil Moisture Sensor: Wired to analog input A0 via the breadboard.
   3. Relay Module: Control signal from digital pin 2 routed through the breadboard.
   4. Water Pump: Connect the pump’s power circuit through the relay contacts.

   Note:
   - Adjust the moisture threshold values (300 and 950 in this example) according to your sensor's behavior.
   - Relay logic (HIGH/LOW) may differ based on your module; here, LOW activates the pump.
*/

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Initialize the LCD with I2C address 0x27, 16 columns, 2 rows

void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();

  // Set pin 2 as output for controlling the relay
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH); // Set relay off initially (modify if your relay's logic is inverted)

  // Display startup message
  lcd.setCursor(0, 0);
  lcd.print("IRRIGATION");
  lcd.setCursor(0, 1);
  lcd.print("SYSTEM IS ON ");
  delay(300);
  lcd.clear();
}

void loop()
{
  // Read the soil moisture sensor value from analog pin A0
  int sensorValue = analogRead(A0);
  Serial.println(sensorValue);

  // Determine water pump state based on sensor reading
  if (sensorValue > 950)
  {                       // Soil is dry
    digitalWrite(2, LOW); // Activate relay (pump ON)
    lcd.setCursor(0, 0);
    lcd.print("Water Pump ON ");
  }
  else
  {
    digitalWrite(2, HIGH); // Deactivate relay (pump OFF)
    lcd.setCursor(0, 0);
    lcd.print("Water Pump OFF");
  }

  // Display soil moisture level on LCD
  if (sensorValue < 300)
  {
    lcd.setCursor(0, 1);
    lcd.print("Moisture: HIGH ");
  }
  else if (sensorValue >= 300 && sensorValue <= 950)
  {
    lcd.setCursor(0, 1);
    lcd.print("Moisture: MID  ");
  }
  else
  { // sensorValue > 950
    lcd.setCursor(0, 1);
    lcd.print("Moisture: LOW  ");
  }

  delay(200); // Wait 2 seconds before next reading
}
