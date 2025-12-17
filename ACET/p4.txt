#include<LiquidCrystal.h>
LiquidCrystal lcd(8,9,4,5,6,7);
String keys[16] = {"1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16"};

int col[]={A0,A1,A2,A3};
int row[]={D10,D11,D12,D13};

bool keypressed = 0;
byte keyindex = 0;

void setup() {
  //row 是 input_pullup
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);
  // col 是 output
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);

  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, HIGH);

  lcd.begin(16,2);
  lcd.clear();
}

void loop() {
  keyindex = keyScan();
  if(keypressed == 1){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(keys[keyindex]);
    keypressed = 0;
  }
}

byte keyScan()
{
  keyindex = 0;
  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, HIGH);
  for(int i = 0; i < 4; i++){
    digitalWrite(col[i], LOW);
    for(int j = 0; j < 4; j++){
      if(!digitalRead(row[j])){
        keypressed = 1;
        keyindex = 4*j+i;
      }
    }
    digitalWrite(col[i], HIGH);
  }
  return keyindex;
}
