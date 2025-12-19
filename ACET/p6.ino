// ADP-Corvette-F1 的蜂鳴器產生振動。
// ADP-Corvette-F1 的蜂鳴器產生音樂及唱歌。

int speakerPin = D3;

void setup(){
  pinMode(speakerPin, OUTPUT);
  // 也可以直接寫成 pinMode(D3, OUTPUT);
  digitalWrite(D3, HIGH);
}
// do re mi fa so la si 
// c  d  e  f  g   a  b
char song[] = "ccggaagffeeddc "; //空白=>休止符
unsigned long beats[] = {1,1,1,1,1,1,2,1,1,1,1,1,1,2,4};
int tempo = 300;
int tones[] = {261, 294, 330, 349, 392, 440, 494};

void loop()
{
  for(int i = 0 ; i < sizeof(song); i++)
  {
    if(song[i] = ' ') delay(tempo * beats[i]);
    else
    {
      tone(D3, tones[i], tempo * beats[i]);
      delay(tempo);
      noTone(D3);
    }
    
  }
  delay(tempo);
}
//==================================================
int speakerPin = D3;

// 依照簡譜的順序,填入代表的音符,空白代表休止符
char notes[] = "ccggaagffeeddc ";

unsigned long beats[] = {1,1,1,1,1,1,2,1,1,1,1,1,1,2,4};
// 利用 sizeof(),算出總共要多少音符
int length = sizeof(notes);
// 決定一拍多長,這邊一拍 300 ms
int tempo = 300;
void setup() {
pinMode(speakerPin, OUTPUT);
}
void loop() {
// 利用 for 來播放我們設定的歌曲,一個音一個音撥放
  for (int i = 0; i < length; i++) {
    // 如果是空白的話,不撥放音樂
    if (notes[i] == ' ') {
      delay(beats[i] * tempo); // rest
    } 
    else{
      playNote(speakerPin,notes[i], beats[i] * tempo);
    }
    delay(tempo/10);
   }
}
void playNote(int OutputPin, char note, unsigned long duration) {
  // 音符字元與對應的頻率由兩個矩陣表示
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 261, 294, 330, 349, 392, 440, 494, 523 };
  // 播放音符對應的頻率
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      tone(OutputPin,tones[i], duration);
      delay(duration);
      noTone(OutputPin);
    }
  }
}
