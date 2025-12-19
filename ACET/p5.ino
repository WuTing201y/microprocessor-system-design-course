#include<LiquidCrystal.h>
LiquidCrystal lcd(8,9,4,5,6,7);
#include<RTC.h>

int year = 2020;
byte month = 12;
byte day = 25;
byte hour = 12;
byte minute = 20;
byte second = 3;

void setup(){
  lcd.begin(16,2);
  lcd.clear();
  RTC.settime(day, hour, minute, second);
  RTC.startcounting();
}

void print2(byte value)
{
  if(value<10){
    lcd.print("0");
  }
  lcd.print(value);
}

void loop()
{
  lcd.setCursor(0,0);
  
  byte dd = RTC.getday();
  byte hr = RTC.gethours();
  byte mins = RTC.getminutes();
  byte sec = RTC.getseconds();
  
  lcd.print(year);
  lcd.print("/");
  print2(month);  // print2函式已經有print了，不需要再寫lcd.print(print2(...))
  lcd.print("/");
  print2(dd);
  
  lcd.setCursor(0,1);
  print2(hr);
  lcd.print(":");
  print2(mins);
  lcd.print(":");
  print2(sec);
}
