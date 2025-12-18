#include<LiquidCrystal.h>
LiquidCrystal lcd(8,9,4,5,6,7);
#include<RTC.h>

byte year = 2020;
byte month = 12;
byte day = 25;
byte hour = 12;
byte minute = 20
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
	lcd.print(year);
	lcd.print("/");
	lcd.print(print2(month));
	lcd.print("/");
	lcd.print(print2(RTC.getday()));
	lcd.print("");

	lcd.print(print2(RTC.gethour()));
	lcd.print(":");
	lcd.print(print2(RTC.getminutes()));
	lcd.print(":");
	lcd.print(print2(RTC.getseconds()));
}
