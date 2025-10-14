#define LATCH_DIO D15   
#define CLK_DIO D14
#define DATA_DIO 2        // D2 is OK, too
#define BUTTON1 BT1
#define BUTTON2 BT2
#define BUTTON3 BT3
#define BUTTON4 BT4
#define BUTTON_A0 A0
#define BUTTON_A1 A1
#define BUTTON_A2 A2
#define BUTTON_A3 A3

char KeyValue[]={'1','2','3','A','4','5','6','B','7','8','9','C','*','0','#','D'};
byte Row=0, Col=0;  // 儲存掃描到的row & col

/* Segment byte maps for numbers 0 to 9 , A, b , C*/ // MSB: dp g f e d c b a :LSB
const byte SEGMENT_MAP[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0X7F,0X6F,0X77,0X7C,0X39};
const byte DP = 0x40;   // Digit Point

 // E: 1110  D: 1101  B: 1011   7: 0111  // position
const byte SEGMENT_SELECT[] = {0x0E,0x0D,0x0B,0x07};

// buffer[0]表示最左(新)，buffer[3]為最右(舊)，-1表示不顯示
int buffer[4] = {-1, -1, -1, -1};
static int bufPacked = 0xFFFF // 初始四個空白 0xF 0xF 0xF 0xF
byte now = 0;
bool lastKeyState = false;
// 新增的數字塞到最左，往右推，最右的會被擠出去
void pushLeft(byte digit)
{
  if(now < 4){
    num[now] = digit;
    now++;
  }
  else{
    for(int i = 0; i <=3; i++){
      num[i] = num[i+1];
    }
    num[3] = digit;
  }
}
void setup() {
  pinMode(LATCH_DIO,  OUTPUT);
  pinMode(CLK_DIO,    OUTPUT);
  pinMode(DATA_DIO,   OUTPUT);

  // 腳位上拉，沒有按時為HIGH，按下後變成LOW
  pinMode(10, INPUT_PULLUP); //R1: S1,S2,S3,S4 (1,2,3,A)                                   
  pinMode(11, INPUT_PULLUP); //R2: S5,S6,S7,S8 (4,5,6,B)
  pinMode(12, INPUT_PULLUP); //R3: S9, S10, S11,S12 (7,8,9,C)
  pinMode(13, INPUT_PULLUP); //R4: (*,0,#,D)
  
  // 欄腳
  pinMode(A0, OUTPUT); // col 欄腳 (1,4,7,*)
  pinMode(A1, OUTPUT); // col 欄腳 (2,5,8,0)
  pinMode(A2, OUTPUT); // col 欄腳 (3,6,9,#)
  pinMode(A3, OUTPUT); // col 欄腳 (A, B, C, D) is correct.
  
  //欄腳位，預設HIGH
  digitalWrite(A0,HIGH);
  digitalWrite(A1,HIGH);
  digitalWrite(A2,HIGH);
  digitalWrite(A3,HIGH);

  // 啟動 LCD
  lcd.begin(16, 2);              // start the library
  lcd.setCursor(0,0); 
  for(int i=0; i<3;i++) //啟用畫面
  {
    lcd.print("Key Martrix Test");
    delay(1000);
    lcd.clear();  //清除畫面
    delay(400);
  }
} 
// display number to 7-segment  位置/值
void WriteNumberToSegment(byte Segment, byte Value)
{
    digitalWrite(LATCH_DIO, LOW); // 鎖存拉低準備送資料
    // MAP first and then SELECT. !!!CANNOT CHANGE THE ORDER!!!
    shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_MAP[Value]); // 先送段碼        
    shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_SELECT[Segment] ); // 再送位選
    digitalWrite(LATCH_DIO,HIGH);  // 鎖存拉高輸出
}

// 跑馬燈: 左->右
void runLeftToRight()
{
  int lightTime;
  for(int i = 3; i >= 0; i--){
     lightTime = 500;
     while(lightTime--){
      for(int j = 3; j >= i; j--){
        WriteNumberToSegment(j-1, num[j]);
        delay(3);
      }
     }
  }
  // 由左->右遞減
  for(int i = 0; i <=3; i++){
    lightTime = 500;
    while(lightTime--)P
    for(int j = i; j <=3; j++){
      WriteNumberToSegment(j, num[j-1]);
      delay(3);
    }
  }
  while(!digitalRaed(BUTTON1);
  delay(100);
}

// 跑馬燈: 右->左
void runRightToLeft()
{
  int lightTime;
  for(int i = 3; i >= 0; i--){
     lightTime = 500;
     while(lightTime--){
      for(int j = 3; j >= i; j--){
        WriteNumberToSegment(j, num[j-1]);
        delay(3);
      }
     }
  }
  // 由右->左遞減
  for(int i = 0; i <=3; i++){
    lightTime = 500;
    while(lightTime--)P
    for(int j = i; j <=3; j++){
      WriteNumberToSegment(3-j, num[3-(j-i)]);
      delay(3);
    }
  }
  while(!digitalRaed(BUTTON2);
  delay(100);
}



void loop() {
  bool = curKeyState = keyscan();
  
  static int keypressedcount=0;  //計數器
  byte keyindex=0;  //對應 KeyValue的索引值
  if(keyscan()==true)   //如果有按下botton
  {
    keyindex=(Row-1) * 4 + Col; //選到正確的索引值
    delay(5);
    if ((keyscan()==true)) 
    {
      lcd.clear();  //確保畫面沒有東西
      lcd.setCursor(0,0);
      lcd.print("Row=");lcd.print(Row);
      lcd.print(",Col=");lcd.print(Col);
      lcd.setCursor(0,1);
      lcd.print(KeyValue[keyindex-1]);
      digitalWrite(A0,LOW);
      digitalWrite(A1,LOW);
      digitalWrite(A2,LOW);
      digitalWrite(A3,LOW);
      delayMicroseconds(100);
      while( (digitalRead(2)==LOW) || (digitalRead(3)==LOW))
        ;  
    }
  } 
}

bool keyscan( )
{
  Row=0;Col=0;
  bool keypressed = false;
  //scan col1
  digitalWrite(A0, LOW);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, HIGH);
  delayMicroseconds(100);

  //Read keys in row.1
  if(digitalRead(10)==LOW)
  {
      digitalWrite(A0, HIGH);
      Col=1;Row=1;
      keypressed = true;
      return(keypressed);
  }
  //Read keys in row.2
  if(digitalRead(11)==LOW)
  {
      digitalWrite(A0, HIGH);
      Col=1;Row=2;
      keypressed = true;
      return(keypressed);
  }
  //Read keys in row.3
  if(digitalRead(12)==LOW)
  {
      digitalWrite(A0, HIGH);
      Col=1;Row=3;
      keypressed = true;
      return(keypressed);
  }
  //Read keys in row.4
  if(digitalRead(13)==LOW)
  {
       digitalWrite(A0, HIGH);
      Col=1;Row=4;
      keypressed = true;
      return(keypressed);
  }
  //scan col 2  
  digitalWrite(A0, HIGH);
  digitalWrite(A1, LOW);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, HIGH);
  delayMicroseconds(100);
  //Read keys in row.1
  if(digitalRead(10)==LOW)
  {
      digitalWrite(A1, HIGH);
      Col=2;Row=1;
      keypressed = true;
      return(keypressed);
  }
    //Read keys in row.2
  if(digitalRead(11)==LOW)
  {
      digitalWrite(A1, HIGH);
      Col=2;Row=2;
      keypressed = true;
      return(keypressed);
  }
  //Read keys in row.3
  if(digitalRead(12)==LOW)
  {
      digitalWrite(A1, HIGH);
      Col=2;Row=3;
      keypressed = true;
      return(keypressed);
  }
  //Read keys in row.4
  if(digitalRead(13)==LOW)
  {
      digitalWrite(A1, HIGH);
      Col=2;Row=4;
      keypressed = true;
      return(keypressed);
  }

  //scan col 3  
  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, LOW);
  digitalWrite(A3, HIGH);
  delayMicroseconds(100);
  //Read keys in row.1
  if(digitalRead(10)==LOW)
  {
      digitalWrite(A2, HIGH);
      Col=3;Row=1;
      keypressed = true;
      return(keypressed);
  }
  //Read keys in row.2
  if(digitalRead(11)==LOW)
  {
      digitalWrite(A2, HIGH);
      Col=3;Row=2;
      keypressed = true;
      return(keypressed);
  }  
  //Read keys in row.3
  if(digitalRead(12)==LOW)
  {
      digitalWrite(A2, HIGH);
      Col=3;Row=3;
      keypressed = true;
      return(keypressed);
  }
  //Read keys in row.4
  if(digitalRead(13)==LOW)
  {
      digitalWrite(A2, HIGH);
      Col=3;Row=4;
      keypressed = true;
      return(keypressed);
  }
  
  //scan col 4  
  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, LOW);
  delayMicroseconds(100);
  //Read keys in row.1
  if(digitalRead(10)==LOW)
  {
      digitalWrite(A3, HIGH);
      Col=4;Row=1;
      keypressed = true;
      return(keypressed);
  }
    //Read keys in row.2
  if(digitalRead(11)==LOW)
  {
      digitalWrite(A3, HIGH);
      Col=4;Row=2;
      keypressed = true;
      return(keypressed);
  }
  //Read keys in row.3
  if(digitalRead(12)==LOW)
  {
      digitalWrite(A3, HIGH);
      Col=4;Row=3;
      keypressed = true;
      return(keypressed);
  }
  //Read keys in row.4
  if(digitalRead(13)==LOW)
  {
      digitalWrite(A3, HIGH);
      Col=4;Row=4;
      keypressed = true;
      return(keypressed);
  }
  return(false);
}



