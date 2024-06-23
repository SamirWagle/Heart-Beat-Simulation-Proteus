
#include <TimerOne.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

int HBSensor = A0;// Sensor Pin
int HBCount = 0;
int HBCheck = 0;
int TimeinSec = 0;
int HBperMin = 0;
int HBStart = 2;  //Pushbutton Pin
int HBStartCheck = 0;

void setup()
{
  pinMode(HBSensor, INPUT);
  pinMode(HBStart, INPUT_PULLUP);
  Timer1.initialize(800000); 
  Timer1.attachInterrupt( timerIsr );
  
  lcd.begin(20, 4); // set up the LCD's number of columns and rows:
  lcd.clear();
  lcd.setCursor(0,0); // set the cursor position:
  lcd.print("  THE BRIGHT LIGHT    ");
  lcd.setCursor(0,1);
  lcd.print(" Heart-Beat  Sensor");
  lcd.setCursor(0,3);
  lcd.print(" Press Button");
}

void loop() 
{
  if(digitalRead(HBStart) == LOW)
  {
    lcd.setCursor(0,2);
    lcd.print(" HB Counting... ");
    lcd.setCursor(0,3);
    lcd.print(" Please Wait: ");
    HBStartCheck = 1;
  }
  if(HBStartCheck == 1)
  {
    if((digitalRead(HBSensor) == HIGH) && (HBCheck == 0))
      {
        HBCount = HBCount + 1;
        HBCheck = 1;
      }
      
      if((digitalRead(HBSensor) == LOW) && (HBCheck == 1))
      {
        HBCheck = 0;   
      }
      
      if(TimeinSec == 10)
      {
          HBperMin = HBCount*6;
          HBStartCheck = 0;
          lcd.setCursor(0,2);
          lcd.print(" HB Per Min: ");
          lcd.print(HBperMin);
          lcd.print("  ");
          lcd.setCursor(0,3);
          lcd.print(" Press Button Again.");
          HBCount = 0;
          TimeinSec = 0;      
      }
  }
}

void timerIsr()
{
  if(HBStartCheck == 1)
  {
      TimeinSec = TimeinSec + 1;
      lcd.setCursor(14,3);
      lcd.print(TimeinSec);
      lcd.print("       ");
  }
}
