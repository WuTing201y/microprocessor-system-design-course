/*
ADP-Corvette-F1 的 LED 13 點亮 5 秒之後中斷。
*/
#include<FlexiTimer2.h>
const in ledpin = 13;

void setup(){
	
}

void loop()
{}

void flash() // 計時中斷函數
{
	static boolean flag = 1; // 
	digitalWrite(ledpin, flag); // LED輸出
	flag = !flag; // 位元旗標顛倒
}

void setup()
{
	pinMode(ledpin, OUTPUT);
	FlexiTimer2::set(5000, flash); // 每5000ms產生中斷，進入flash
	FlexiTimer2::start(); // 啟動開始計時
}

void loop(){} // nothing
