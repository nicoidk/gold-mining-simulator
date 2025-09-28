#ifndef INVESTEMENTS_H
#define INVESTEMENTS_H

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include "CustomOutput.h"
using namespace std;

#define end cout<<endl;
#define end2 cout<<endl<<endl;

class NYSE{ // New York Stock Exchange 
  public:
    string stockName, stockTicker;
    double stockPrice;
    int stocksBought, percentDay; 
    // percentDay: change in the past day

    CustomOutputClass ccout;
    
    NYSE(double price, string name, string ticker){
      this -> stockPrice = price;
      this -> stocksBought = 0;
      this -> stockName = name;
      this -> stockTicker = ticker;
    }

    void priceChange(){ // changes every day
      usleep(100); // guaranteeing a new random number
      int change = rand() % 51 - 23; // between -23 and 27
      this -> percentDay = change;

      stockPrice *= (1 + (change / 100.0));
    }

    double buyStocks(int amount, double Balance){
      if(amount * stockPrice > Balance || amount < 1){
        cout<<"Insufficient Funds";
        return 0;
      }else{
        stocksBought += amount;
        cout<<"You purchased "<<amount<<" "<<stockName<<" Stock(s) for $"<<amount * stockPrice<<endl;
        return amount * stockPrice;
      }
    }

    double sellStocks(int amount, double Balance, char location){
      if(amount > stocksBought){
        cout<<"You do not have enough stocks to sell";
        return 0;
      }else{
        stocksBought -= amount;
        if(location != '3'){
          cout<<"You sold "<<amount<<" "<<stockName<<" Stock(s) for $"<< 0.9 * amount * stockPrice<<endl;
          return amount * stockPrice * 0.9;
        }else{
          cout<<"You sold "<<amount<<" "<<stockName<<" Stock(s) for $"<<amount * stockPrice<<endl;
          return amount * stockPrice;
        }
      }
    }

    void stockOutput(){
      ccout << "$\t\t" << stockName << " (" << stockTicker << "): "; end
      
      ccout << "$\t\t\tOwned: ";
      cout << stocksBought; end
      
      ccout << "$\t\t\tCurrent Price: ";
      cout << fixed << setprecision(2) << stockPrice << "$\n";

      ccout << "$\t\t\tPercent Change (1D): ";
      cout << percentDay << "%"; end
    }

  double getPrice(){
    return this -> stockPrice ;
  }
};

class TSX{ // Toronto Stock Exchange 
  public:
    string stockName, stockTicker;
    double stockPrice;
    int stocksBought, percentDay; 
    // percentDay: change in the past day

CustomOutputClass ccout;

    TSX(double price, string name, string ticker){
      this -> stockPrice = price;
      this -> stocksBought = 0;
      this -> stockName = name;
      this -> stockTicker = ticker;
    }

    void priceChange(){ // changes every day
      int change = rand() % 21 - 9; // between -9 and 11
      this -> percentDay = change;

      stockPrice *= (1 + (change / 100.0));
    }

    double buyStocks(int amount, double Balance){
      if(amount * stockPrice > Balance || amount < 1){
        cout<<"Insufficient Funds";
        return 0;
      }else{
        stocksBought += amount;
        cout<<"You purchased "<<amount<<" "<<stockName<<" Stock(s) for $"<<amount * stockPrice<<endl;
        return amount * stockPrice;
      }
    }

    double sellStocks(int amount, double Balance, char location){
      if(amount > stocksBought){
        cout<<"You do not have enough stocks to sell";
        return 0;
      }else{
        stocksBought -= amount;
        if(location != '3'){
          cout<<"You sold "<<amount<<" "<<stockName<<" Stock(s) for $"<< 0.9 * amount * stockPrice<<endl;
          return amount * stockPrice * 0.9;\
        }else{
          cout<<"You sold "<<amount<<" "<<stockName<<" Stock(s) for $"<<amount * stockPrice<<endl;
          return amount * stockPrice;
        }
      }
    }

    void stockOutput(){
      ccout << "$\t\t" << stockName << " (" << stockTicker << "): "; end

      ccout << "$\t\t\tOwned: ";
      cout << stocksBought; end

      ccout << "$\t\t\tCurrent Price: ";
      cout << fixed << setprecision(2) << stockPrice << "$\n";

      ccout << "$\t\t\tPercent Change (1D): ";
      cout << percentDay << "%"; end
    }

  double getPrice(){
    return this -> stockPrice ;
  }
};

#endif

/*
  - NYSE is more volatile (change between -23% to +25% )
  - TSX is more stable (change between -9% to +11%)
*/
