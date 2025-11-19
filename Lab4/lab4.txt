#include <LiquidCrystal.h>
#include<string>
#define BUTTON1 BT1
#define BUTTON2 BT2
#define BUTTON3 BT3
#define BUTTON4 BT4

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
char KeyValue[]={'1','2','3','A','4','5','6','B','7','8','9','C','*','0','#','D'};
byte Row=0, Col=0;
int speakerPin = D3;

// ======預錄歌曲=======
char song_notes[] = "cdeccdecefgefg "; // 依照簡譜的順序，填入代表的音符，空白代表休止符
// 決定每個音階的拍子，注意這邊用 unsigned long 所以拍子只能是正整數
unsigned long song_beats[] = {1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,2};
// 利用 sizeof()，算出總共要多少音符
int song_len = sizeof(song_notes);
// 決定一拍多長，這邊一拍 300 ms
int tempo = 300;

// 音調Do ~ Si
String names[] = { "Do", "Re", "Mi", "Fa", "So", "La", "Si"};

//========高、中、低音輸出=================
// [哪個音調][第幾個音符]
int tones[3][7] = {
                  {1046, 1175, 1318, 1397, 1568, 1760, 1976},   //高音
                  {523, 587, 659, 698, 784, 880, 988},          //中音
                  {261, 294, 330, 349, 392, 440, 494}           //低音
                 };
int toneflag = 1;  //0=high, 1=middle, 2=low。最初預設為中音: 1

// ======== 錄音變數設定===========
#define maxlen 100
bool isRecording = false; //是否正在錄音
bool hasRecording = false; //是否有錄音的紀錄
int recording_index = 0; //錄音中每個音符的索引
int recording_notes[maxlen];  //紀錄錄音的音符
int recording_tone[maxlen]; //紀錄錄音的音調

// ======== 各種函數===========
void playTone(int noteIndex)
{
  lcd.setCursor(0,0); //設游標在(0,0)位置
  lcd.print("                "); // 先清空第一行，用寫入16個空白做到
  lcd.setCursor(0,0); //再把游標設回(0,0)位置
  lcd.print(names[noteIndex]); // 顯示音符名稱
  
  if(toneflag == 0){ //如果目前選擇高音
    lcd.print("          High");  //第一行最後面輸出High
  }else if(toneflag == 1){ //如果目前選擇中音
    lcd.print("        Middle"); //第一行最後面輸出Middle
  }
  else if(toneflag == 2){ //如果目前選擇低音
    lcd.print("           Low"); //第一行最後面輸出Low
  }
  lcd.noCursor(); // 不顯示游標
  // tone(哪個腳位發聲, 發出什麼聲, 發出多久時間)
  tone(speakerPin, tones[toneflag][noteIndex], tempo);  //發出[哪個音調][哪個音符]
  delay(tempo); // 延遲一點時間
  noTone(speakerPin); //停止發出聲音

  // 如果正在錄音，記錄音符
  if(isRecording && recording_index < maxlen) { //如果正在錄音且錄音的索引沒有超過設定的最大長度
    recording_notes[recording_index] = noteIndex;  //音符在錄音音符陣列索引裡的位置上是哪個
    recording_tone[recording_index] = toneflag;  // 將目前的錄音索引放入音調的陣列裡，並在裡面寫上目前的音調
    recording_index++; //錄音索引+1
  }
}
void bA()
{
  toneflag = 0;
  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(0,0);
  lcd.print("            High");
  lcd.noCursor();
}
void bB()
{
  toneflag = 1;
  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(0,0);
  lcd.print("          Middle");
  lcd.noCursor();
}
void bC()
{
  toneflag = 2;
  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(0,0);
  lcd.print("             Low");
  lcd.noCursor();
}
void BTN1() //開始錄音
{
  isRecording = true;
  recording_index = 0;
  hasRecording = false;
  
  lcd.setCursor(0,0);
  lcd.print("                ");
  
  lcd.setCursor(0,1);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print("Recording");
  lcd.noCursor();
}
void BTN2() //停止錄音
{
  if(isRecording){
    isRecording = false;
    hasRecording = true;

    lcd.setCursor(0,0);
    lcd.print("                ");
    
    lcd.setCursor(0,1);
    lcd.print("                ");
    lcd.setCursor(0,1);
    lcd.print("No Recording");
    lcd.noCursor();
  }
}
void BTN3()
{
  if(recording_index == 0 || !hasRecording) return;

  for(int i = 0; i < recording_index; i++)
  {
    int note_index = recording_notes[i];
    int tone_index = recording_tone[i];

     // 顯示字符Playing
    lcd.setCursor(0,1);
    lcd.print("                ");
    lcd.setCursor(0,1);
    lcd.print("Playing");
    lcd.noCursor();

    // 顯示音符名稱
    lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,0);
    lcd.print(names[note_index]);
    lcd.noCursor();

    //播放音符
    tone(speakerPin, tones[tone_index][note_index], tempo);
    delay(tempo);
    noTone(speakerPin);
    delay(50);
  }
}
void BTN4() //播放預錄歌曲
{
  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(0,0);
  lcd.print("Two Tigers");
  lcd.noCursor();
  delay(tempo*2);

    // 顯示音符名稱
  lcd.setCursor(0,1);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print("Playing a Song.");
  lcd.noCursor();

  for(int i = 0; i < song_len; i++)
  {
    if(song_notes[i] == ' ')
    {
      delay(song_beats[i] * tempo);
    }else
    {
      int song_note_idx = song_notes[i] - 'c';
      if(song_note_idx>= 0 && song_note_idx < 7)
      {
        tone(speakerPin, tones[1][song_note_idx], song_beats[i] * tempo); //使用中音
        delay(tempo);
        noTone(speakerPin);

        lcd.setCursor(0,1);
        lcd.print("                ");
        lcd.setCursor(0,1);
        lcd.print(names[song_note_idx]);
        lcd.noCursor();
      }      
    }
  }
  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print("                ");
  lcd.noCursor();
}
void setup() {
  pinMode(speakerPin, OUTPUT);

  pinMode(10, INPUT); //R1: S1,S2,S3,S4 (1,2,3,A)                                   
  pinMode(11, INPUT_PULLUP); //R2: S5,S6,S7,S8 (4,5,6,B)
  pinMode(12, INPUT_PULLUP); //R3: S9, S10, S11,S12 (7,8,9,C)
  pinMode(13, INPUT_PULLUP); //R4: (*,0,#,D)
  pinMode(A0, OUTPUT); //A1, C1: S1,S5,S9 (1,4,7,*)
  pinMode(A1, OUTPUT); //A2, C2: S2,S6,S10 (2,5,8,0)
  pinMode(A2, OUTPUT); //A3, C3: S3,S7,S11 (3,6,9,#)
  pinMode(A3, OUTPUT); //A4, C4: S4,S8,S12 (*,0, #,D)
  //Pin left to right :R1 R2 R3 R4 C1 C2 C3 C4

  digitalWrite(A0,HIGH);
  digitalWrite(A1,HIGH);
  digitalWrite(A2,HIGH);
  digitalWrite(A3,HIGH);

  // start the library
  lcd.begin(16, 2);  
  lcd.clear();            
  lcd.setCursor(0,0);   //顯示cursor在左上角
  lcd.cursor();

}

void loop() 
{
  static int keypressedcount=0;
  byte keyindex=0;
  
  bool press_btn1 = false;
  bool press_btn2 = false;
  bool press_btn3 = false;
  bool press_btn4 = false;

  if(digitalRead(BT1) == LOW && !press_btn1)
  {
    press_btn1 = true;
    BTN1();
    delay(200);
  }
  if(digitalRead(BT1) == HIGH) press_btn1 = false;

  if(digitalRead(BT2) == LOW && !press_btn2)
  {
    press_btn2 = true;
    BTN2();
    delay(200);
  }
  if(digitalRead(BT2) == HIGH) press_btn2 = false;

  if(digitalRead(BT3) == LOW && !press_btn3)
  {
    press_btn3 = true;
    BTN3();
    delay(200);
  }
  if(digitalRead(BT3) == HIGH) press_btn3 = false;

  if(digitalRead(BT4) == LOW && !press_btn4)
  {
    press_btn4 = true;
    BTN4();
    delay(200);
  }
  if(digitalRead(BT4) == HIGH) press_btn4 = false;

  if(keyscan()==true) 
  {
    keyindex=(Row-1)*4+Col;
    delay(5);
    if ((keyscan()==true) && (keyindex=(Row-1)*4+Col))
    {
        char pressKey = KeyValue[keyindex - 1];
        digitalWrite(A0,LOW);
        digitalWrite(A1,LOW);
        digitalWrite(A2,LOW);
        digitalWrite(A3,LOW);
        delayMicroseconds(100);
        while( (digitalRead(10)==LOW) || (digitalRead(11)==LOW) || 
               (digitalRead(12)==LOW) || (digitalRead(13)==LOW))
          ; 
        
        if(pressKey == '1') playTone(0);
        if(pressKey == '2') playTone(1);
        if(pressKey == '3') playTone(2);
        if(pressKey == '4') playTone(3);
        if(pressKey == '5') playTone(4);
        if(pressKey == '6') playTone(5);
        if(pressKey == '7') playTone(6);
        if(pressKey == 'A') bA();
        if(pressKey == 'B') bB();
        if(pressKey == 'C') bC();
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
