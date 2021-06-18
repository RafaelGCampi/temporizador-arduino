// Variaveis globais
#include <LiquidCrystal.h>
#define btoSEL 3 // Botao para andar no menu
#define btoVALOR 2 // Botão para dar o ok

LiquidCrystal lcd(12, 11, 5, 4, 1, 0);
//variavel relogio e data
int seg = 0, min = 0, hor = 0, dia = 15, mes=6, ano=2021, bisexto = 0, btoSTATUS = 0;
int selBTO = -1, btoSTATUS2=0;
//Variavel motor
float sinVal;
int toneVal, segA = 0, minA = 1, horA=0, alarme =0, selA=0;
int fotoresistor= A0;

int motor = 10;
int motor1 = 9;
int motor2 = 8;

void setup() {
 lcd.clear();
 lcd.begin(16, 2);
 pinMode(btoSEL, INPUT); //definindo pino como entrada
 pinMode(btoVALOR, INPUT); //definindo pino como entrada
 
 pinMode(10, OUTPUT);
 pinMode(9, OUTPUT);
 pinMode(8, OUTPUT);
 TCCR1A = 0;
 TCCR1B = 0;
 TCCR1B |= (1<<CS10)|(1 << CS12); 
 TCNT1 = 0xC2F6;
 TIMSK1 |= (1 << TOIE1);
  pinMode(10, OUTPUT);
   pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  
 
 attachInterrupt(digitalPinToInterrupt(btoSEL), menu, RISING); //Interrupção externa para o botão de seleção
 attachInterrupt(digitalPinToInterrupt(btoVALOR), valor, RISING); //Interrupção externa para o botão de alteração de valor
 //Serial.begin(9600);
  
} //end  setup

void loop() {
  
  //Serial.println("olas");
  
  //analogWrite(80,30);
  //analogWrite(motor1,30);
  //digitalWrtie(10,LOW);
 }
 
ISR(TIMER1_OVF_vect){ //rotina de interrupção por overflow do TIMER1
  TCNT1 = 0xC2F6; // Reinicia contador do TIMER1
  //Conta do relogio
    seg++;// Cada volta adiciona 1 na variavel seg
  if(seg == 60){ min++; seg = 0;} // alterando o minuto sempre que a variavel seg chegar em 60
    if(min == 60){ hor++; min = 0;}// alterando a hora sempre que a variavel mim chegar em 60
  
  //Alarme
  if(alarme == 1){ //entra no alarme
    lcd.setCursor(0,0);
    lcd.print(" -  ALARME  - ");
    
    if(horA<10){
      lcd.setCursor(1,1); lcd.print("0");lcd.print(horA);lcd.print(":");} //colocando valor zero na primeira casa do display quando numeros menor que 9
    if(horA >=10){ lcd.setCursor(1,1); lcd.print(horA);lcd.print(":");} // colocando os valores maires que 10

    if(minA<10){
    lcd.setCursor(4,1); lcd.print("0");lcd.print(minA);lcd.print(":");}//colocando valor zero na primeira casa do display quando numeros menor que 9
    if(horA >=10){ lcd.setCursor(4,1); lcd.print(minA);lcd.print(":");}    
    
  if(segA<10){
    lcd.setCursor(7,1); lcd.print("0");lcd.print(segA);} //colocando valor zero na primeira casa do display quando numeros menor que 9
  else{ lcd.setCursor(7,1); lcd.print(segA);}  
  
  }
  else{
  //Relogio display
    if(hor<10){
      lcd.setCursor(1,1); lcd.print("0");lcd.print(hor);lcd.print(":");} //colocando valor zero na primeira casa do display quando numeros menor que 9
    if(hor >=10){ lcd.setCursor(1,1); lcd.print(hor);lcd.print(":");} // colocando os valores maires que 10

    if(min<10){
    lcd.setCursor(4,1); lcd.print("0");lcd.print(min);lcd.print(":");}//colocando valor zero na primeira casa do display quando numeros menor que 9
    if(hor >=10){ lcd.setCursor(4,1); lcd.print(min);lcd.print(":");}    
    
  if(seg<10){
    lcd.setCursor(7,1); lcd.print("0");lcd.print(seg);} //colocando valor zero na primeira casa do display quando numeros menor que 9
  else{ lcd.setCursor(7,1); lcd.print(seg);}    

 // Data
    if(ano%4 ==0){bisexto =1;} // Calculo ano bisexto     
    if(hor == 24){dia++; hor = 0;} // Alterar o dia depois de 24horas
  
 if(dia>=1 && dia<=31){if(dia<10){mes=31;lcd.setCursor(1,0); lcd.print("0");lcd.print((dia-1)+1);lcd.print("/");}
              else{lcd.setCursor(1,0); lcd.print((dia-1)+1);lcd.print("/");}
                        lcd.setCursor(4,0);lcd.print("01/");} // Janeiro
 if(dia>=32 && dia<=(59+bisexto)){mes=28+bisexto;if((dia-32+1)<10){lcd.setCursor(1,0);lcd.print("0");lcd.print(dia-32+1);lcd.print("/");}
                    else{lcd.setCursor(1,0);lcd.print(dia-32+1);lcd.print("/");}
                                  lcd.setCursor(4,0);lcd.print("02/");} //Fevereiro
 if(dia>=(60+bisexto) && dia<=(90+bisexto)){mes=31;if((dia-(60+bisexto)+1)<10){lcd.setCursor(1,0);lcd.print("0");lcd.print(dia-(60+bisexto)+1);lcd.print("/");}
                          else{lcd.setCursor(1,0);lcd.print(dia-(60+bisexto)+1);lcd.print("/");}
                        lcd.setCursor(4,0);lcd.print("03/");} //Março
 if(dia>=(91+bisexto) && dia<=(120+bisexto)){mes=30;if((dia-(91+bisexto)+1)<10){lcd.setCursor(1,0);lcd.print("0");lcd.print(dia-(91+bisexto)+1);lcd.print("/");}
                          else{lcd.setCursor(1,0);lcd.print(dia-(91+bisexto)+1);lcd.print("/");}
                        lcd.setCursor(4,0);lcd.print("04/");} //Abril   
 if(dia>=(121+bisexto) && dia<=(151+bisexto)){mes=31;if((dia-(121+bisexto)+1)<10){lcd.setCursor(1,0);lcd.print("0");lcd.print(dia-(121+bisexto)+1);lcd.print("/");}
                            else{lcd.setCursor(1,0);lcd.print(dia-(121+bisexto)+1);lcd.print("/");}
                          lcd.setCursor(4,0);lcd.print("05/");} //Maio
 if(dia>=(152+bisexto) && dia<=(181+bisexto)){mes=30;if((dia-(152+bisexto)+1)<10){lcd.setCursor(1,0);lcd.print("0");lcd.print(dia-(152+bisexto)+1);lcd.print("/");}
                              else{lcd.setCursor(1,0);lcd.print(dia-(152+bisexto)+1);lcd.print("/");}
                          lcd.setCursor(4,0);lcd.print("06/");} //Junho
 if(dia>=(182+bisexto) && dia<=(212+bisexto)){mes=31;if((dia-(182+bisexto)+1)<10){lcd.setCursor(1,0);lcd.print("0");lcd.print(dia-(182+bisexto)+1);lcd.print("/");}
                              else{lcd.setCursor(1,0);lcd.print(dia-(182+bisexto)+1);lcd.print("/");}
                          lcd.setCursor(4,0);lcd.print("07/");} //Julho
  if(dia>=(213+bisexto) && dia<=(243+bisexto)){mes=31;if((dia-(213+bisexto)+1)<10){lcd.setCursor(1,0);lcd.print("0");lcd.print(dia-(213+bisexto)+1);lcd.print("/");}
                              else{lcd.setCursor(1,0);lcd.print(dia-(213+bisexto)+1);lcd.print("/");}
                          lcd.setCursor(4,0);lcd.print("08/");} //Agosto
  if(dia>=(244+bisexto) && dia<=(273+bisexto)){mes=30;if((dia-(244+bisexto)+1)<10){lcd.setCursor(1,0);lcd.print("0");lcd.print(dia-(244+bisexto)+1);lcd.print("/");}
                              else{lcd.setCursor(1,0);lcd.print(dia-(244+bisexto)+1);lcd.print("/");}
                          lcd.setCursor(4,0);lcd.print("09/");} //Setembro
  if(dia>=(274+bisexto) && dia<=(304+bisexto)){mes=31;if((dia-(274+bisexto)+1)<10){lcd.setCursor(1,0);lcd.print("0");lcd.print(dia-(274+bisexto)+1);lcd.print("/");}
                              else{lcd.setCursor(1,0);lcd.print(dia-(274+bisexto)+1);lcd.print("/");}
                          lcd.setCursor(4,0);lcd.print("10/");} //Outubro
  if(dia>=(305+bisexto) && dia<=(334+bisexto)){mes=30;if((dia-(305+bisexto)+1)<10){lcd.setCursor(1,0);lcd.print("0");lcd.print(dia-(305+bisexto)+1);lcd.print("/");}
                              else{lcd.setCursor(1,0);lcd.print(dia-(305+bisexto)+1);lcd.print("/");}
                          lcd.setCursor(4,0);lcd.print("11/");} //Novembro
  if(dia>=(335+bisexto) && dia<=(365+bisexto)){mes=31;if((dia-(335+bisexto)+1)<10){lcd.setCursor(1,0);lcd.print("0");lcd.print(dia-(335+bisexto)+1);lcd.print("/");}
                              else{lcd.setCursor(1,0);lcd.print(dia-(335+bisexto)+1);lcd.print("/");}
                          lcd.setCursor(4,0);lcd.print("12/");} //Dezembro 
  
  lcd.setCursor(7,0);  
  lcd.print(ano); // Ano

  if(dia == (365+bisexto)){ano++; dia =0;} // adicionando o ano após 365 dias
    
  if((horA == hor) && (minA == min)){ // Disparar o alarme quando as 2 variaveis de hora e minuto forem iguais
        sinVal = (sin(seg*(3.1416/60)));
      toneVal = 2000+(int(sinVal*1000));
      tone(8, toneVal);}//end sonorizador
  }//end else
}//end ISR

void menu(){ //função para seleção do botão que percorre o relogio
  btoSTATUS = digitalRead(btoSEL);
    if(btoSTATUS == HIGH){
      selBTO++;
      switch (selBTO){
        //case selecionando a data
        case 0: lcd.setCursor(0,0);lcd.print(">");break;
        case 1: lcd.setCursor(3,0);lcd.print(">");break;
        case 2: lcd.setCursor(6,0);lcd.print(">");break;
        //case selecionando relogio
        case 3: lcd.setCursor(0,1);lcd.print(">");break;
        case 4: lcd.setCursor(3,1);lcd.print(">");break;
        case 5: lcd.setCursor(6,1);lcd.print(">");break;
        //case selecionando alarme
        case 6: alarme = 1;lcd.setCursor(0,1);lcd.print(">");break;
        case 7: lcd.setCursor(3,1);lcd.print(">");break;
        case 8: lcd.setCursor(6,1);lcd.print(">");break;
        case 9: alarme = 0;selBTO=-1;break;
      }//end switch
     }//end if
} //end função menu

void valor(){ // função para alterar os valores da data e relogio
   btoSTATUS2 = digitalRead(btoVALOR);
      if(btoSTATUS2 == HIGH){
        switch(selBTO){
          case 0:dia++;break;
          case 1:dia=dia+mes;break;
          case 2:ano++;break;
          case 3:hor++;break;
          case 4:min++;break;
          case 5:seg++;break;
          case 6: horA++;break;
          case 7: minA++;break;
          case 8: segA++;break;
        } //end switch
    }//end if void valor
} // end void valor
