//Boi-Hien Huang
//bhuan019@ucr.edu
//https://docs.google.com/document/d/1nDtm-alhEIsIWlVWrjr4Od8CTiGyJpfF1UkpNldMoyM/edit?usp=sharing
//https://www.youtube.com/watch?v=kwTeKeyumNw

#include "RIMS.h"

volatile int TimerFlag = 0;
void TimerISR() {
   TimerFlag = 1;
}
int winner = 0;
int loser = 0;

enum states {start, button1, button2, button3, button4, button5, finish} states;
enum states2 {start2, press1, press2, press3, press4, press5, success} states2;
enum states3 {start3, flashOn, flashOff, KeepOn} states3;
void Input(){
   switch(states2){//transitions
      case start2:
         states2 = press1;
         break;
      case press1:
         if(A4){
            states2 = press2;  
         }
         else if(A0 || A1 || A2 || A3 || A5 || A6 || A7){
            loser = 1;
            states2 = start2;
         }
         break;
      case press2:
         if(A3){
            states2 = press3;  
         }
         else if(A0 || A1 || A2 || A5 || A6 || A7){
            loser = 1;
            states2 = start2;
         }
         break;
      case press3:
         if(A0){
            states2 = press4;
         }
         else if(A1 || A2 || A5 || A6 || A7){
            loser = 1;
            states2 = start2;
         }
         break;
      case press4:
         if(A6){
            states2 = press5;
         }
         else if(A1 || A2 || A5 || A7){
            loser = 1;
            states2 = start2;
         }
         break;
      case press5:
         if(A2){
            states2 = success;  
         }
         else if(A1 || A5 || A7){
            loser = 1;
            states2 = start2;
         }
      case success:
         states2 = success;
         break;
   }
   switch(states2){//actions
      case start2:
         break;
      case press1:
         break;
      case press2:
         break;
      case press3:
         break;
      case press4:
         break;
      case press5:
         break;
      case success:
         winner = 1;
         break;
   }
}

void Display(){
   switch(states){//transitions
      case start:
         states = button1;
         break;
      case button1:
         states = button2;
         break;
      case button2:
         states = button3;
         break;
      case button3:
         states = button4;
         break;
      case button4:
         states = button5;
         break;
      case button5:
         states = finish;
         break;
      case finish:
         states = finish;
         break;
   }
   switch(states){
      case start:
         B0 = B1 = B2 = B3 = B4 = B5 = B6 = B7 = 0;
         break;
      case button1:
         B0 = 0;
         B1 = 0;
         B2 = 0;
         B3 = 0;
         B4 = 1;
         B5 = 0;
         B6 = 0;
         B7 = 0;
         break;
      case button2:
         B0 = 0;
         B1 = 0;
         B2 = 0;
         B3 = 1;
         B4 = 0;
         B5 = 0;
         B6 = 0;
         B7 = 0;
         break;
      case button3:
         B0 = 1;
         B1 = 0;
         B2 = 0;
         B3 = 0;
         B4 = 0;
         B5 = 0;
         B6 = 0;
         B7 = 0;
         break;
      case button4:
         B0 = 0;
         B1 = 0;
         B2 = 0;
         B3 = 0;
         B4 = 0;
         B5 = 0;
         B6 = 1;
         B7 = 0;
         break;
      case button5:
         B0 = 0;
         B1 = 0;
         B2 = 1;
         B3 = 0;
         B4 = 0;
         B5 = 0;
         B6 = 0;
         B7 = 0;
         break;
      case finish:
         B0 = 0;
         B1 = 0;
         B2 = 0;
         B3 = 0;
         B4 = 0;
         B5 = 0;
         B6 = 0;
         B7 = 0;
         break;
   }
}

void Result(){
   switch(states3){//transition
      case start:
         if(winner){
            states3 = KeepOn;  
         }
         if(loser){
            states3 = flashOn;  
         }
         break;
      case flashOn:
         states3 = flashOff;
         break;
      case flashOff:
         states3 = flashOn;
         break;
      case KeepOn:
         break;
   }
   switch(states3){//actions
      case start:
         break;
      case flashOn:
         B0 = 1;
         B1 = 1;
         B2 = 1;
         B3 = 1;
         B4 = 1;
         B5 = 1;
         B6 = 1;
         B7 = 1;
         break;
      case flashOff:
         B0 = 0;
         B1 = 0;
         B2 = 0;
         B3 = 0;
         B4 = 0;
         B5 = 0;
         B6 = 0;
         B7 = 0;
         break;
      case KeepOn:
         B0 = 1;
         B1 = 1;
         B2 = 1;
         B3 = 1;
         B4 = 1;
         B5 = 1;
         B6 = 1;
         B7 = 1;
         break;
   }
}


int main() {
   int periodGCD = 1000;
   int DisplayElapsedTime = 1000;
   int InputElapsedTime = 1000;
   int ResultElapsedTime = 1000;
   TimerSet(periodGCD);
   TimerOn();
   
   while(1) {
      if(DisplayElapsedTime >= 1000){
         Display();
         DisplayElapsedTime = 0;
      }
      if(InputElapsedTime >= 1000){
         Input();
         InputElapsedTime = 0;
      }
      if(ResultElapsedTime >= 1000){
         Result();
         ResultElapsedTime = 0;
      }
      
      DisplayElapsedTime += 1000;
      InputElapsedTime += 1000;
      ResultElapsedTime += 1000;
      while(!TimerFlag);
      TimerFlag = 0; 
      
   }
   return 0;
}

