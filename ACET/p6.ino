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
char song[] = "ccggaagffeeddc";
unsigned long beats[] = {1,1,1,1,1,1,2,1,1,1,1,1,1,2};
int tempo = 300;
int tone[] = {261, 294, 330, 349, 392, 440, 494};

void loop()
{
	for(int i = 0 ; i < sizeof(song); i++)
	{
		tone(D3, tone[i], tempo*beats[i]);
		delay(tempo);
		noTone(D3);
	}
	delay(tempo);
}
