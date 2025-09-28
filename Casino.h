
#ifndef CASINO_H
#define CASINO_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include "CustomOutput.h"
#include "Business.h"
using namespace std;

#define end cout<<endl;
#define end2 cout<<endl<<endl;

// NOTE: scroll to bottom for "parent" function

void fruitChange(int num){
  if(num == 1){
    cout<<"🍇";
  }else if(num == 2){
    cout<<"🍍";
  }else if(num == 3){
    cout<<"🍒";
  }else if(num == 4){
    cout<<"🥝";
  }else if(num == 5){
    cout<<"🍌";
  }
}

void horseRaces(double balance, Business *game){
  CustomOutputClass ccout;

  char selectedHorse;
  double moneyGambled;
  int winningChances[4] = {0};
  int winningReturn[4] = {0};

  for(int i = 0; i < 100; i++){
    ++ winningChances[rand()%4]; // get each horse's winning chance
  }

  for(int i = 0; i < 4; i++){
    winningReturn[i] = 150 - winningChances[i]; // get each horse's winning return
  }

  ccout<<"Welcome to the Horse Racing!"; end
  ccout<<"You have $"; cout<<balance; ccout<<" in your account."; end
  ccout << "\tCurrent winning chances: "; end2
  
  ccout << "\t\tMean Malcolm (1): "; cout<<winningChances[0]<<"%"; end
  ccout << "\t\t\tWinnings return +"; cout<<winningReturn[0]<<"%"; end2
  
  ccout << "\t\tDaring David (2): "; cout<<winningChances[1] << "%"; end
  ccout << "\t\t\tWinnings Return: "; cout<<winningReturn[1] << "%"; end2

  ccout << "\t\tIconic Ian (3): "; cout<<winningChances[2] << "%"; end
  ccout << "\t\t\tWinnings Return: "; cout<<winningReturn[2] << "%"; end2

  ccout << "\t\tLively Liam (4): "; cout<<winningChances[3] << "%"; end
  ccout << "\t\t\tWinnings Return: "; cout<<winningReturn[3] << "%"; end2

  ccout << "Choose a horse: "; cin >> selectedHorse;

  while(selectedHorse != '1' && selectedHorse != '2' && selectedHorse != '3' && selectedHorse != '4'){
    ccout<<"Invalid input, try again: "; cin >> selectedHorse;
  }

  ccout << "Choose how much to bet: "; cin >> moneyGambled;

  while(moneyGambled > balance || moneyGambled < 0){
    ccout<<"Invalid input, try again: "; cin >> moneyGambled;
  }

  int temp = rand()%100+1;
    
  if(temp <= winningChances[0]){
    cout<<"Mean Malcolm won the race."<<endl;
    if(selectedHorse == '1'){
       game -> addRevenue(moneyGambled * double(winningReturn[0])/100);
    }else{
       game -> addExpenses(moneyGambled);
    }
  }else if(temp <= winningChances[0]+winningChances[1]){
    cout<<"Daring David won the race."<<endl;
    if(selectedHorse == '2'){
      game -> addRevenue(moneyGambled * double(winningReturn[1])/100);
    }else{
       game ->addExpenses(moneyGambled);
    }
  }else if(temp <= winningChances[0]+winningChances[1]+winningChances[2]){
    cout<<"Iconic Ian won the race."<<endl;
    if(selectedHorse == '3'){
      game -> addRevenue(moneyGambled * double(winningReturn[2])/100);
    }else{
       game -> addExpenses(moneyGambled);
    }
  }else{
    cout<<"Lively Liam won the race."<<endl;
    if(selectedHorse == '4'){
      game -> addRevenue(moneyGambled * double(winningReturn[3])/100);
    }else{
       game -> addExpenses(moneyGambled);
    }
  }
  end2;
}

void rouletteTable(double balance, Business *game){
  CustomOutputClass ccout;

  double moneyGambled;
  string input;
  
  ccout<<"Welcome to the roulette table. Simply bet on Black (1) or Red (2).\nPayouts are set at +50%"; end
  
  ccout<<"How much money would you like to bet: "; cin >> moneyGambled;
  while(moneyGambled > balance || moneyGambled < 0){
    ccout<<"Invalid input, try again: "; cin >> moneyGambled;
  }

  ccout <<"\tBlack(1) or Red(2): "; cin >> input;
  while(input != "1" && input != "2"){
    ccout<<"Invalid input, try again: "; cin >> input;
  }

  int temp = rand()%2+1;
  
  ccout<<"Rolling... "; sleep(2);
  
  
  if(input == "1"){
    if(temp == 1){
      ccout<<" Black was rolled. You win!"; end
      game -> addRevenue(moneyGambled * 0.5);
    }else{
      ccout<<"Red was rolled. You lost. "; end
      game ->  addExpenses(moneyGambled);
    }
  }else{
    if(temp == 1){
      ccout<<" Black was rolled. You lost."; end
      game -> addExpenses(moneyGambled);
    }else{
      ccout<<" Red was rolled. You win!"; end
      game -> addRevenue(moneyGambled * 0.5);
    }
  }
  
}

void fruitMachines(double balance, Business *game){
  CustomOutputClass ccout;

  double moneyGambled;
  cout<<"🍒🍌🥝 ";
  ccout<<"Welcome to Fruit Machines! Choose an amount to bet: $"; 
  cin >> moneyGambled;
  while(moneyGambled > balance || moneyGambled < 0){
    ccout<<"Invalid input, try again: $"; cin >> moneyGambled;
  }

  int slot1 = rand()%5+1;
  int slot2 = rand()%5+1;
  int slot3 = rand()%5+1;

  ccout<<"Rolling..."; sleep(2);
  ccout<<"You rolled: "; fruitChange(slot1); fruitChange(slot2); fruitChange(slot3); end2

  if(slot1 == slot2 && slot2 == slot3){
    ccout<<"You 4x'ed your money!"; end
    game -> addRevenue(moneyGambled * 3); 
  }else if(slot1 == slot2 || slot1 == slot3 || slot2 == slot3){
    ccout<<"You 2x'ed your money!"; end
    game -> addRevenue(moneyGambled); 
  }else{
    ccout<<"You lost your money."; end
    game -> addExpenses(moneyGambled); 
  }
}

void CasinoLobby(Business *game){
  CustomOutputClass ccout;

  double balance = game -> goldBalance;
  char input;

  ccout<<"Welcome to the Royal Klondike Casino!"; end
  ccout<<"What would you like to play?\n";
  ccout << "\t\tHorse Racing (1)"; end
  ccout << "\t\tRoulette Table (2)"; end
  ccout << "\t\tFruit Machines (3)"; end
  ccout << "\t\tLeave the casino (4)"; end

  cin >> input;
  while(input < 49 || input > 52){
    ccout<<"Invalid input, try again: ";
    cin >> input;
  }

  if(input == '1'){
    horseRaces(balance, game);
  }else if(input == '2'){
    rouletteTable(balance, game);
  }else if(input == '3'){
    fruitMachines(balance, game);
  }
  
  if(game -> businessLocation != '3'){ // Treasure tundra -> unlimited casino
    game -> hasVisitedCasinoToday = true;
  }
}

#endif
