#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x20, 16, 2); // address, columns, rows -- confirmed via I2C scanner

float duration;
float distance;
int sigPin = 9;
int buzzerpin = 8;
int lightpin = 4;
int lightsensor = A0;
int anchorpin = A1;
int time;
int buttonOld = 1;
int buttonNew;
int anchorstate = 0;
int displaytime;

// Track what's currently on screen so we only rewrite when it changes
String lastState = "";
int lastAnchorState = -1;

void setup()
{
  pinMode(buzzerpin, OUTPUT);
  pinMode(lightpin, OUTPUT);
  pinMode(lightsensor, INPUT);
  pinMode(anchorpin, INPUT);
  Serial.begin(9600);

  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Open Sea");
  lcd.setCursor(0, 1);
  lcd.print("Anchor: UP");
  lastState = "Open Sea";
  lastAnchorState = 0;
}

// Updating the LCD only when the hazard state or anchor state actually changed
void updateLCD(String hazardState)
{
  if (hazardState != lastState)
  {
    lcd.setCursor(0, 0);
    lcd.print(" "); // clear line 
    lcd.setCursor(0, 0);
    lcd.print(hazardState);
    lastState = hazardState;
  }

  if (anchorstate != lastAnchorState)
  {
    lcd.setCursor(0, 1);
    lcd.print("                "); // clear line 2
    lcd.setCursor(0, 1);
    lcd.print(anchorstate == 1 ? "Anchor: DOWN" : "Anchor: UP");
    lastAnchorState = anchorstate;
  }
}

void loop()
{
  // CHARYBDIS
  // The trigger pulse that is to send the echo
  pinMode(sigPin, OUTPUT);
  digitalWrite(sigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(sigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(sigPin, LOW);
  // Switching to input to listen for the echo
  pinMode(sigPin, INPUT);
  duration = pulseIn(sigPin, HIGH);
  // Distance
  distance = (duration * .0343) / 2;
  delay(100);

  time = 0; // setting time for timer
  if (distance < 100)
  {
    Serial.println("The state is: Charybdis state");
    updateLCD("Charybdis!");
  }
  while (distance < 100) // checking charybdis
  {
    buttonNew = digitalRead(anchorpin);
    if (buttonOld == 0 && buttonNew == 1)
    {
      if (anchorstate == 0)
      {
        anchorstate = 1;
      }
      else
      {
        anchorstate = 0;
      }
    }
    buttonOld = buttonNew;
    updateLCD("Charybdis!"); // keep anchor line current every pass

    tone(buzzerpin, 1000); // buzzer for the charybdis
    delay(100);
    noTone(buzzerpin);
    delay(100);
    if (anchorstate == 1)
    {
      Serial.println("You are safe for now");
      break;
    }
    if (time >= 5 && anchorstate == 0)
    {
      Serial.println("You've been hit by a smooth criminal (Wrecked)");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("WRECKED!");
      while (true)
      {
        // inf loop to stay wrecked
      }
    }
    time = time + 1;
    displaytime = 6 - time;
    Serial.print("You have:");
    Serial.println(displaytime);
    delay(700);
    pinMode(sigPin, OUTPUT); // rechecking values of ultrasonic sensor
    digitalWrite(sigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(sigPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(sigPin, LOW);
    pinMode(sigPin, INPUT);
    duration = pulseIn(sigPin, HIGH);
    distance = (duration * .0343) / 2;
  }

  // STORM
  int valueoflight = analogRead(A0);
  delay(100);
  time = 0; // setting timer
  if (valueoflight > 488)
  {
    Serial.println("The state is: stormy");
    updateLCD("Storm!");
  }
  while (valueoflight > 488)
  {
    buttonNew = digitalRead(anchorpin); // arming anchor
    if (buttonOld == 0 && buttonNew == 1)
    {
      if (anchorstate == 0)
      {
        anchorstate = 1;
      }
      else
      {
        anchorstate = 0;
      }
    }
    buttonOld = buttonNew; // Led for storm
    updateLCD("Storm!");

    digitalWrite(4, HIGH);
    delay(250);
    digitalWrite(4, LOW);
    delay(250);
    if (anchorstate == 1) // conditions for wrecking
    {
      Serial.println("You are safe for now");
      break;
    }
    if (time >= 5 && anchorstate == 0)
    {
      Serial.println("Bitch, You wrecked");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("WRECKED!");
      while (true)
      {
        // inf loop so that it stays wrecked
      }
    }
    time = time + 1;
    displaytime = 6 - time;
    Serial.print("You have:");
    Serial.println(displaytime);
    delay(400);
    valueoflight = analogRead(A0);
  }

  // OPEN SEA - default state, shown whenever neither hazard is currently active
  if (distance >= 100 && valueoflight <= 488)
  {
    if (lastState != "Open Sea") // only print once when entering this state
    {
      Serial.println("The state is: Open sea");
    }
    updateLCD("Open Sea");
  }
}
/* I hope you like this, this has taken a very long time to learn 
how to code this and hours went into debugging this.
This me singing off :) */
