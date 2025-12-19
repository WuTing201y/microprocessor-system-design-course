// ADP-Corvette-F1 的蜂鳴器產生振動。
// ADP-Corvette-F1 的蜂鳴器產生音樂及唱歌。
int speakerPin = D3;

char notes[] = "ccggaagffeeddc ";
unsigned long beats[] = {1,1,1,1,1,1,2,1,1,1,1,1,1,2,4};
int length = sizeof(notes);
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

//=============================
void setup(){
	pinMode(D3, OUTPUT);
}

char song[] = "ccggaagffeeddc ";
unsigned long beats[] = {1,1,1,1,1,1,2, 1,1,1,1,1,1,2, 4};
int len = sizeof(song);
int tmp = 300;

void loop(){
	for(int i = 0; i < len; i++){
		if(song[i] == ' '){
			delay(tmp * beats[i]);
		}else{
			playfunc(song[i], tmp*beats[i]);
		}
		delay(tmp/10);
	}
}

void playfunc(char note, unsigned long dur){
	char notes[] = {'c','d','e','f','g','a','b','C'};
	int tones[] = {261, 294, 330, 349, 392, 440, 494, 523};
	for(int i = 0; i < 8; i++){
		if(notes[i] == note){
			tone(D3, tones[i], dur);
			delay(dur);
			noTone(D3);
		}
	}
}
