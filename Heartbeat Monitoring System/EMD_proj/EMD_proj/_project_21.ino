#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
#include <Keypad.h> 

const byte ROWS = 4; 
const byte COLS = 4;

byte rowPins[ROWS] = {10,9,8,7}; //Pins for the rows
byte colPins[COLS] = {6,5,4,3}; //Pins for the cols
 
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

int tempPin=A0;
int inp;
double temp;
int myNum[4];
int arr[4][4]={
  {0,1,4,7},
  {0,1,6,5},
  {2,7,4,9},
  {8,1,5,0},
};
String s[4]={"Shrestha","Ram","Sham","Mohan"};
int hb[4]={80,90,120,52};
int flag=0;
int in;
void setup() {
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(A3,OUTPUT);
  pinMode(A4,OUTPUT);
  pinMode(13,INPUT);
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop() {
  while(analogRead (A5)>100 || digitalRead(13) ){
    Serial.println(digitalRead(13));
    int val = analogRead (A5);
    Serial.println(val);
    digitalWrite(A4, HIGH);
    lcd.setCursor(2, 0);
    lcd.print("WARNING..!");
    delay(500);
    lcd.clear();
  }
  digitalWrite(A4, LOW);
  if(flag ==0){
    lcd.setCursor(2, 0);
    lcd.print("hello, world!");
    lcd.setCursor(4, 1);
    lcd.print("Enter_ID");
  }
  else{
//__________________________________________________________
    lcd.setCursor(0,0);
    lcd.print("ID ");
    lcd.setCursor(7, 0);
    lcd.print(myNum[0]-'0');
    lcd.setCursor(8, 0);
    lcd.print(myNum[1]-'0');
    lcd.setCursor(9, 0);
    lcd.print(myNum[2]-'0');
    lcd.setCursor(10, 0);
    lcd.print(myNum[3]-'0');
    lcd.setCursor(0,1);
    lcd.print("Name ");
    lcd.setCursor(7,1);
    lcd.print(s[in]);
    delay(6000);
    lcd.clear();
//--------------------------------------------------------
    lcd.setCursor(0,0);
    lcd.print("Measure The");
    lcd.setCursor(0,1);
    lcd.print("Temperatue");
    delay(6000);
    inp=analogRead(A0);
    temp=(double)inp/1024;
    temp*=5;
    temp=temp-0.5;
    temp*=100;
    Serial.print("Temperature:");
    Serial.println(temp);
    lcd.clear();
//--------------------------------------------------------
    lcd.setCursor(0,0);
    lcd.print("Heart Beat");
    lcd.setCursor(12,0);
    lcd.print(hb[in]);
    lcd.setCursor(0,1);
    lcd.print("Temperature");
    lcd.setCursor(12,1);
    lcd.print(temp);
    delay(6000);
//---------------------------------------------------------
    lcd.clear();
    if(hb[in]>=60 && hb[in]<=100){
      lcd.setCursor(0,0);
      lcd.print("Normal rate");
    }
    else{
      lcd.setCursor(0,0);
      lcd.print("Abnormal rate");
    }
    if(temp>=97 && temp<=99){
      lcd.setCursor(0,1);
      lcd.print("Normal Temp");
    }
    else{
      lcd.setCursor(0,1);
      lcd.print("Abnormal Temp");
    }
    if(hb[in]>=60 && hb[in]<=100 && temp>=97 && temp<=99 ) digitalWrite(A1,HIGH);
    else if(hb[in]>=60 && hb[in]<=100) digitalWrite(A2,HIGH);
    else if(temp>=97 && temp<=99) digitalWrite(A3,HIGH);
    else digitalWrite(A4,HIGH);
    delay(6000);
    digitalWrite(A1,LOW);
    digitalWrite(A2,LOW);
    digitalWrite(A3,LOW);
    digitalWrite(A4,LOW);
  }
  delay(1000);
  lcd.clear();
  delay(1000);
  flag=0;
  while(1){
       Serial.println("Enter four-digit ID -");
        for (int i = 0; i < 4; ++i){
          while((myNum[i] = keypad.getKey())==NO_KEY) {
            delay(1);
          } 
          while(keypad.getKey() != NO_KEY) {
            delay(1);
          } 

        }
    for(int i=0;i<4;i++){
      int temp=1;
      for(int j=0;j<4;j++){
        if(myNum[j]-'0'!=arr[i][j]){
          temp=0;
          break;
        }
      }
      if(temp){
        flag=1;
        in=i;
        break;
      }
    }
       if(flag){
           Serial.println("Correct ID\n");
           break;
       }
      else{
          Serial.println("ID not exist\n");
      }
    }
    delay(1000);
}
 