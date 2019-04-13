#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 10, 11, 12, 13 );
int btn_start = 2;
int btn_led = 3;
int btn_buz = 4;
int Led = 5;
int Buz = 6;
double tempoFineLed = 0;
double tempoFineBuz = 0;
bool errori = false;

void setup()
{
  pinMode(btn_start, INPUT);
  pinMode(btn_led,INPUT);
  pinMode(btn_buz,INPUT);
  pinMode(Led,OUTPUT);
  pinMode(Buz,OUTPUT);
  lcd.begin(16, 2);
  tempoFineLed = 0;
  tempoFineBuz = 0;
  errori = false;
}

void loop()
{
  if (digitalRead(btn_start) == HIGH)
  {
    lcd.clear();
    led();
    buz();
    scrivo();
  }
  
}


void led()
{
   lcd.setCursor(0,0);
   lcd.print("attendere il LED");
   delay(random(300,2000));
   if(ritardo(btn_led,"              Non premere il bottone prima del led                ","attendere il LED")){ delay(random(50,100)); }
   digitalWrite(Led,HIGH);
   double tempoInizio = millis();
   tempoTest(btn_led, "  LED","Premi il bottone");
   digitalWrite(Led,LOW);
   tempoFineLed = millis()-tempoInizio;
   lcd.clear();
}

void buz()
{
   lcd.setCursor(0,0);
   lcd.print("attendere il BUZ");
   delay(random(300,2000));
   if(ritardo(btn_buz,"              Non premere il bottone prima del buz                ","attendere il BUZ")){ delay(random(50,100)); }
   tone(Buz, 1000 , 2000);
   double tempoInizio = millis();
   tempoTest(btn_buz,"           BUZ","Premi il bottone");
   noTone(Buz);
   tempoFineBuz = millis()-tempoInizio;
   lcd.clear();
}

void scrivo()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("time LED->" + String(tempoFineLed/1000));
  lcd.setCursor(0, 1);
  lcd.print("time BUZ->" + String(tempoFineBuz/1000));
}

bool controllo(int btn)
{
  errori = false;
  if (digitalRead(btn) == HIGH)
  { 
   errori = true;
  }
  return errori;
}

bool ritardo(int btn, String testo1, String testo2)
{
  bool taa = false;
   int cont = 0;
   while(digitalRead(btn) == HIGH)
   {
    bool taa = true;
    lcd.setCursor(0,1);
    lcd.print(testo1.substring(cont));
    lcd.setCursor(0,0);
    lcd.print(testo2);
    delay(320);
    cont ++;
    if (cont == 50){cont = 0;}
   }
   return taa;
}

void tempoTest(int btn, String testo1, String testo2)
{
  lcd.clear();
  while (digitalRead(btn) == LOW)
   {
    lcd.setCursor(0,0);
    lcd.print (testo1);
    lcd.setCursor(0,1);
    lcd.print (testo2); 
   }
}
