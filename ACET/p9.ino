/*
ADP-Corvette-F1 的外部中斷文字顯示。
按 S17(KEY)鍵,在串列監控視窗顯示中斷次數。
*/

int cnt = 0; //外部中斷次數

void setup(){
	Serial.begin(9600);
	pinMode(BT1, INPUT_PULL);
	attachInterrupt(BT1, disp_count, FALLING);
}

void loop()
{}

void disp_count() // INT0 中斷服務程式
{
	unsigned int delay1 = 5000;
	noInterrupts(); // 停止中斷
	while(delay1--); // 延遲，防止機械彈跳
	while(!digitalRead(BT1)); // 等待放開BT1
	delay1 = 5000;
	while(delay1--); // 延遲 防止機械彈跳
	Serial.println(cnt++);
	interrupts(); // 恢復中斷
}
