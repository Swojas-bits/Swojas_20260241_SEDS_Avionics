// C++ code
//
float duration;
float distance;
int sigPin = 9;
int buzzerpin = 8;
int lightpin = 4;
int lightsensor = A0;
int anchorpin = A1;
int time;
int buttonOld= 1;
int buttonNew;
int anchorstate = 0;
int displaytime;

void setup()
{
 pinMode(buzzerpin,OUTPUT);
 pinMode(lightpin,OUTPUT); 
 pinMode(lightsensor,INPUT);
 pinMode(anchorpin,INPUT); 
 Serial.begin(9600);
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
  
  time = 0;// setting time for timer
  while(distance < 100)// checking charybdis
  { 
  buttonNew = digitalRead(anchorpin);
  if(buttonOld==0 && buttonNew==1) 
{
  if(anchorstate == 0) 
  { 
    anchorstate = 1; 
  }
  else { 
    anchorstate = 0; 
  }
}
  buttonOld = buttonNew;
  tone(buzzerpin, 1000); //buzzer for the charybdis
    delay(100);
    noTone(buzzerpin);
    delay(100);
  if(anchorstate==1)
  {
  	Serial.println("You are safe for now");
    break;
  }  
  if(time >= 5 && anchorstate == 0)
  {
    Serial.println("You've been hit by a smooth criminal (Wrecked)");
    while(true)
    {
    // inf loop to stay wrecked
    }
  }

  time = time + 1;
  displaytime = 6 - time;  
  Serial.print("You have:");
  Serial.println(displaytime);  
  delay(700);
  pinMode(sigPin, OUTPUT);// rechecking values of ultrasonic sensor
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

time=0;//setting timer
//Checking slider values  
while(valueoflight>488)
{
  buttonNew = digitalRead(anchorpin);//arming anchor
  if(buttonOld==0 && buttonNew==1) 
{
  if(anchorstate == 0) 
  { 
    anchorstate = 1; 
  }
  else { 
    anchorstate = 0; 
  }
}
  buttonOld = buttonNew;//Led for storm
  digitalWrite(4,HIGH);
  delay(250);
  digitalWrite(4,LOW);
  delay(250);
  if(anchorstate==1)//conditions for wrecking
  {
  	Serial.println("You are safe for now");
    break;
  }  
  if(time >= 5 && anchorstate == 0)
  {
    Serial.println("Bitch, You wrecked");
    while(true)
    {
      //inf loop so that it stays wrecked
    }
  }

  time = time + 1;
  displaytime = 6 - time;
  Serial.print("You have:");
  Serial.println(displaytime);
  delay(400);
  valueoflight = analogRead(A0);
}
  }
/* I hope you like this, put a lot of effort and hours into 
learning coding, actually coding and debugging this but 
I loved every minute of this.
This me signing off ;) */   