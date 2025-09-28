#ifndef BUSINESS_H
#define BUSINESS_H

#include <iostream>
#include "Workers.h"
#include "Forecast.h"
#include "CustomOutput.h"
#include "Investements.h"
using namespace std;

#define end cout<<endl;
#define end2 cout<<endl<<endl;


class Business{
  public:
  CustomOutputClass ccout;
  string businessName;
  char businessLocation;  // 1 - 5 (see below)
  double goldBalance, totalRevenue, totalExpenses;
  double locationMultiplier;
  bool hasVisitedCasinoToday;

  Business(string name, char location){
    this -> businessName = name;
    this -> businessLocation = location;
    this -> goldBalance = 0; 

    // For gold multipliers
    if(location == '5') // Icicle Enclave
      this -> locationMultiplier = 15;
  }

  void newDay(int day, double productivity, double multiplier, double expenses, int goldsellprice, double weather){

    hasVisitedCasinoToday = false;
    multiplier = 1 + (multiplier / 100) + (locationMultiplier / 100); // eg 2 -> 1.02

    // Pre-ramble
    ccout<<"=================================\n="; end
    cout<<"=\t";
    ccout<<businessName;
    ccout<<"'s day #";
    cout<<day;
    ccout<<" in ";
    ccout<<this -> getLocation(); end

    // Gold sell price.
    cout<<"="; end
    ccout<<"=\tCurrent gold sell price: $";
    cout<<goldsellprice;
    ccout<<" / ounce"; end

    // Gold mined.
    ccout<<"=\tGold mined yesterday: ";
    cout<<productivity*8;
    ccout<<" ounces"; end

    ccout<<"=\t\tCurrent multiplier: ";
    cout<<(multiplier-1)*100<<"%"<<endl;

    // Total revenue.
    cout<<"=\t";
    ccout<<"\t\tRevenue: +$";
    cout<<8 * productivity * goldsellprice * multiplier<<endl;
    this -> totalRevenue += 8 * productivity * goldsellprice * multiplier;

    // Total expenses.
    cout<<"=\t";
    ccout<<"\t\tExpenses: -$";
    cout<<expenses<<endl;
    this -> totalExpenses += expenses;

    // Profit
    double profit = (8 * productivity * goldsellprice * multiplier) - expenses;
    cout<<"=\t";
    ccout<<"\t\t\tProfit: $";
    cout<<profit<<" (-"<<abs(weather)<<"%)"<<endl;
    
    profit = profit * (1 - abs(weather) / 100); // weather calculation

    //Balance
    this -> goldBalance += profit;

    ccout<<"=\t"<<"\t\t\tBalance: $";
    printf("%.2f", this -> goldBalance); end

    //Post Ramble
    ccout<<"=\t"<<"\tWeather today: ";
    cout<<weather<<"°C"<<endl;
    ccout<<"=\t"<<"For help, type '/cmds' for a list of available commands."; end
    ccout<<"=\n=================================\n"; end
  }

  void businessStats(int day, int workersHired){
    cout<<businessName<<"'s stats:"<<endl;
    cout<<"\tBusiness age: "<<day<<" day(s)"<<endl;
    cout<<"\tTotal revenue: $"<<totalRevenue<<endl;
    cout<<"\tTotal expenses: $"<<totalExpenses<<endl;
    cout<<"\t\tCurrent balance: $"<<goldBalance<<endl;
    cout<<"\t# of workers hired: "<<workersHired<<endl;
  }
  
  double getBalance(){
    return this -> goldBalance;
  }
  
  string getLocation(){
    if(this -> businessLocation == '1'){
      return "Chillwater Creek";
    }else if(this -> businessLocation == '2'){
      return "Frosty Falls";
    }else if(this -> businessLocation == '3'){
        return "Treasure Tundra";
    }else if(this -> businessLocation == '4'){
      return "Aurora Valley";
    }
    else{ 
      return "Icicle Enclave";
    }
    return 0;
  }

  void addExpenses(double newExpense){
    this -> totalExpenses += newExpense;
    this -> goldBalance -= newExpense;
    ccout<<"New Balance: $";
    printf("%.2f", this -> goldBalance); end
  }

  void addRevenue(double newRevenue){
    this -> totalRevenue += newRevenue;
    this -> goldBalance += newRevenue;
    ccout<<"New Balance: $";
    printf("%.2f", this -> goldBalance); end
  }

};

#endif

/*

Locations:
  - 1. Chillwater Creek ( - 20% housing cost )
  - 2. Frosty Falls ( - 20% worker wages )
  - 3. Klondike Kaves ( + 15% gold )
  - 4. Aurora Valley ( + 25% worker happiness )
  - 5. Icicle Enclave ( - 15% worker hapiness | + 25 % gold )

*/
