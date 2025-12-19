/*
ADP-Corvette-F1 的 UART 輸出訊息至超級終端機格式。
ADP-Corvette-F1 的 COM 上傳送數字1~9,UART 顯示:數字 1~9。
*/
int num = 65;
int i = 1;
char ch;


void setup(){
  Serial.begin(9600);
}


void loop()
{
  Serial.print(num);
  delay(500);

  if(Serial.available()){
    ch = Serial.read();
    if(ch > '0' && ch <= '9'){
      num = ch - '0';
      Serial.print(num);
      Serial.print(" ");
      for(int j = 0; j < num; j++){
        Serial.print("*");
      }
      Serial.println();
    }
  }


}
