// active command file
#ifndef CMDS_H
#define CMDS_H

#include <iostream>
using namespace std;

#include "Business.h"
#include "Casino.h"
#include "CustomOutput.h"
#include "Equipment.h"
#include "Forecast.h"
#include "Investements.h"
#include "Scenarios.h"
#include "Workers.h"

#define end cout<<endl;
#define end2 cout<<endl<<endl;

// Command input, Business class, Forecast class, Worker array, Equipment array, NYSE, TSX, Day #
int commandInput(string input, Business *game, Forecast weather, Workers *workerList[], Equipment *equipList[], NYSE NYSE_stockList[], TSX TSX_stockList[], int day){   // return 0, means that we will skip to the next day
  
  int temp, balance = game -> getBalance();  // Used to validate commands
  char location = game -> businessLocation;
  bool isValid = true, temp2 = false; // If any command is run, temp2 becomes true. If temp2 is still false by then end, an error message ocurs.

  CustomOutputClass ccout;

  if (input[0] != '/') {
    isValid = false;
    ccout << "/Invalid command. Please try again or type '/cmds' for a list of commands."; end
  } else {
    temp = input.find("/cmds");
    if (temp >= 0 && input.length() == 5) {
      temp2 = true; // to check if input is invalid
      ccout << "\nLIST OF COMMANDS:"; end2
      
      ccout << "\t/worker"; end
      ccout << "\t\t/worker list (display hireable workers)"; end
      ccout << "\t\t/workers (display hired workers)"; end
      ccout << "\t\t/worker hire [HIRE_ID]"; end
      ccout << "\t\t/worker fire [WORKER_ID] "; end2
      
      ccout << "\t/equipment"; end
      ccout << "\t\t/equipment list (displays purchasable equipment)"; end
      ccout << "\t\t/equipment (display purchased equipement)"; end
      ccout << "\t\t/equipment buy [PURCHASE_ID]"; end
      ccout << "\t\t/equipment sell [EQUIPMENT_ID] "; end2
      
      ccout << "\t/forecast"; end
      ccout << "\t\t/forecast view"; end
      ccout << "\t\t/forecast now"; end2
      
      ccout << "\t/business"; end
      ccout << "\t\t/business stats"; end
      ccout << "\t\t/business bal "; end2

      ccout << "\t/stock ($)"; end
      ccout << "\t\t/stock portfolio (displays all stocks)"; end
      ccout << "\t\t/stock buy [STOCK_TICKER]"; end
      ccout << "\t\t/stock sell [STOCK_TICKER]"; end
      ccout << "\t\t/stock help (helpful information regarding the stock market)"; end2

      ccout << "\t/casino ($)"; end2
      
      ccout << "\t/nextday or /nd (skips to following day)"; end2
    }

    temp = input.find("/worker");
    if (temp >= 0) { // ------ Commands with /worker -------
      temp = input.find ("/worker list");
        if(temp >= 0 && input.length() == 12){
          temp2 = true;
          workerList[0] -> workerList();
        }
      temp = input.find("/workers");
      if(temp >= 0 && input.length() == 8){
        temp2 = true;
        cout<<" - # of Prospectors: "<<type_Prospector<<endl;
        cout<<" - # of Managers: "<<type_Manager<<endl;
        cout<<" - # of Polishers: "<<type_Polisher<<endl;
        cout<<" - # of Traders: "<<type_Trader<<endl<<endl;
        for(int i = 0; i < workerList[0]->getEmployeeCount(); i++){
          workerList[i]->workerOutput();
        }
      }

      temp = input.find("/worker hire");
      if(temp >= 0){
        temp = input.find("PROSPECTOR");
        if(temp >= 0 && input.length() == 23){
          temp2 = true;
          if(balance >= 1000){
            if(workerList[0] -> getProspectorCount() < 10){
              workerList[workerList[0]->getEmployeeCount()-1] = new Prospector(day);
              game -> addExpenses(1000);
              cout << "You hired a prospector!" << endl;
            }else{
              cout<<"You have reached the limit of hiring prospectors."<<endl;
            }
          }else{
            cout<<"Insufficient funds."<<endl;
          }
        }
        temp = input.find("MANAGER");
        if(temp >= 0 && input.length() == 20){
          temp2 = true;
          if(balance >= 1000){
            if(workerList[0] -> getManagerCount() < 3){
              workerList[workerList[0]->getEmployeeCount()-1] = new Manager(day);
              game -> addExpenses(1000);
              cout << "You hired a manager!" << endl;
            }else{
              cout<<"You have reached the limit of hiring managers."<<endl;
            }
          }else{
            cout<<"Insufficient funds."<<endl;
          }
        }
        temp = input.find("POLISHER");
        if(temp >= 0 && input.length() == 21){
          temp2 = true;
          if(balance >= 750){
            if(workerList[0] -> getPolisherCount() < 5){
              workerList[workerList[0]->getEmployeeCount()-1] = new Polisher(day);
              game -> addExpenses(750);
              cout << "You hired a polisher!" << endl;
            }else{
              cout<<"You have reached the limit of hiring polishers."<<endl;
            }
          }else{
            cout<<"Insufficient funds."<<endl;
          }
        }
        temp = input.find("TRADER");
        if(temp >= 0 && input.length() == 19){
          temp2 = true;
          if(balance >= 2000){
            if(workerList[0] -> getTraderCount() < 1){
              workerList[workerList[0]->getEmployeeCount()-1] = new Trader(day);
              game -> addExpenses(2000);
              cout << "You hired a trader!" << endl;
            }else{
              cout<<"You have reached the limit of hiring traders."<<endl;
            }
          }else{
            cout<<"Insufficient funds."<<endl;
          }
        }
      }

      temp = input.find("/worker fire");
      if(temp >= 0){
        temp2 = true;
        int fireID = stoi(input.substr(temp + 13));
        if(fireID <= workerList[0]->getEmployeeCount() && fireID >= 1){
          workerList[fireID-1] -> fireEmployee();
        }else{
          cout<<"Invalid ID"<<endl;
        }
      }
    }

    temp = input.find("/equipment");
    if (temp >= 0) { // ------ Commands with /equipment -------
      temp = input.find("/equipment list");
      if(temp >= 0 && input.length() == 15){
        temp2 = true;
        equipList[0] -> equipmentList();
      }

      if(input.length() == 10){ // if input is /equipment
        temp2 = true;
        
        cout<<" - # of Shovels: "<<equipList[0]->getShovelCount()<<endl;
        cout<<" - # of Wheelbarrows: "<<equipList[0]->getWheelbarrowCount()<<endl;
        cout<<" - # of Pickaxes: "<<equipList[0]->getPickaxeCount()<<endl;
        cout<<" - # of Horses: "<<equipList[0]->getHorseCount()<<endl<<endl;
        
        for(int i = 0; i < equipList[0]->getEquipmentCount(); i++){
          equipList[i]->equipmentOutput();
        }
      }

      temp = input.find("/equipment buy");
      if(temp >= 0){
        temp = input.find("WHEELBARROW");
        if(temp >= 0 && input.length() == 26){
          temp2 = true;
          if(balance >= 100){
            if(equipList[0] -> getWheelbarrowCount() < 3){
              cout<<"You bought a wheelbarrow!"<<endl;
              equipList[equipList[0] -> getEquipmentCount()-1] = new Wheelbarrow(day);
              game -> addExpenses(100);
              if(game -> businessLocation == '1'){
                cout<<"\tLocation bonus applied: +$50"<<endl;
                game -> addRevenue(50);
              }
            }else{
              cout<<"You have reached the limit of buying wheelbarrows."<<endl;
            }
          }else{
            cout<<"Insufficient funds."<<endl;
          }
        }
        
        temp = input.find("PICKAXE");
        if(temp >= 0 && input.length() == 22){
          temp2 = true;
          if(balance >= 50){
            if(equipList[0] -> getPickaxeCount() < 5){
              cout<<"You bought a pickaxe!"<<endl;
              equipList[equipList[0] -> getEquipmentCount()-1] = new Pickaxe(day);
              game -> addExpenses(50);
              if(game -> businessLocation == '1'){
                cout<<"\tLocation bonus applied: +$25"<<endl;
                game -> addRevenue(25);
              }
            }else{
              cout<<"You have reached the limit of buying pickaxes."<<endl;
            }
          }else{
            cout<<"Insufficient funds."<<endl;
          }
        }
        
        temp = input.find("SHOVEL");
        if(temp >= 0 && input.length() == 21){
          temp2 = true;
          if(balance >= 30){
            if(equipList[0] -> getShovelCount() < 4){
              cout<<"You bought a shovel!"<<endl;
              equipList[equipList[0] -> getEquipmentCount()-1] = new Shovel(day);
              game -> addExpenses(30);
              if(game -> businessLocation == '1'){
                cout<<"\tLocation bonus applied: +$15"<<endl;
                game -> addRevenue(15);
              }
            }else{
              cout<<"You have reached the limit of buying shovels."<<endl;
            }
          }else{
            cout<<"Insufficient funds."<<endl;
          }
        }

        temp = input.find("HORSE");
        if(temp >= 0 && input.length() == 20){
          temp2 = true;
          if(balance >= 200){
            if(equipList[0] -> getHorseCount() < 2){
              cout<<"You bought a horse!"<<endl;
              equipList[equipList[0] -> getEquipmentCount()-1] = new Horse(day);
              game -> addExpenses(200);
              if(game -> businessLocation == '1'){
                cout<<"\tLocation bonus applied: +$100"<<endl;
                game -> addRevenue(100);
              }
            }else{
              cout<<"You have reached the limit of buying horses."<<endl;
            }
          }else{
            cout<<"Insufficient funds."<<endl;
          }
        }
      }

      temp = input.find("/equipment sell");
      if(temp >= 0){
        temp2 = true;
        int sellID = stoi(input.substr(temp + 16));
        if(sellID <= equipList[0]->getEquipmentCount() && sellID >= 1){
          game -> addRevenue(equipList[sellID-1] -> sell());
          cout<<"You sold equipment #"<<sellID<<endl;
        }else{
          ccout<<"Invalid equipment ID."; end
        }
      }
    }

    temp = input.find("/forecast"); // ------ Commands with /forecast -------
    if (temp >= 0) {
      temp = input.find("/forecast view");
      if(temp >= 0 && input.length() == 14){
        temp2 = true;
        weather.getForecast(day);
      }

      temp = input.find("/forecast now");
      if(temp >= 0 && input.length() == 13){
        temp2 = true;
        cout<<"Current weather: "<< weather.getCurrentWeather(day-1)<<"°C"<<endl;
      }
    }

    temp = input.find("/business"); // ------ Commands with /business -------
    if (temp >= 0) {
      temp = input.find("/business stats");
      if(temp >= 0 && input.length() == 15){
        temp2 = true;
        game -> businessStats(day, workerList[0] -> getEmployeeCount());
      }

      temp = input.find("/business bal");
      if(temp >= 0 && input.length() == 13){
        temp2 = true;
        cout<<"Business Balance: $"<<game -> goldBalance<<endl;
      }
    }

    temp = input.find("/stock"); // ------ Commands with /stock -------
    if (temp >= 0) {
      temp = input.find("/stock portfolio");
      if(temp >= 0 && input.length() == 16){
        temp2 = true;
        
        ccout <<"\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"; end2

        ccout<< "$\tYour NYSE porfolio: "; end2
          for(int i = 0; i < 3; i++){
            NYSE_stockList[i].stockOutput(); end2
          }

        end
        
        ccout << "$\tYour TSX porfolio: "; end2
          for(int i = 0; i < 3; i++){
            TSX_stockList[i].stockOutput(); end
          }
        ccout <<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"; end2
      }

      temp = input.find("/stock buy"); // -------- buying stocks ---------
      if(temp >= 0 && input.length() == 15){
        int amount, stockID;
        bool isNYSE = false;

        temp = input.find("VSNR");
        if(temp >= 0){
          temp2 = true;
          stockID = 0;
          isNYSE = true;
        }

        temp = input.find("SMTS");
        if(temp >= 0){
          temp2 = true;
          stockID = 1;
          isNYSE = true;
        }

        temp = input.find("PNNL");
        if(temp >= 0){
          temp2 = true;
          stockID = 2;
          isNYSE = true;
        }

        ccout<<"How many stocks would you like to buy? "; cin >> amount; 
        game -> addExpenses(NYSE_stockList[stockID].buyStocks(amount, balance));

        if(isNYSE == false){

          temp = input.find("TTTN");
          if(temp >= 0){
            temp2 = true;
            stockID = 0;
          }

          temp = input.find("ENIN");
          if(temp >= 0){
            temp2 = true;
            stockID = 1;
          }

          temp = input.find("FINF");
          if(temp >= 2){
            temp2 = true;
            stockID = 2;
          }

          ccout<<"How many stocks would you like to buy? "; cin >> amount; 
          game -> addExpenses(TSX_stockList[stockID].buyStocks(amount, balance));
        }
      }

      temp = input.find("/stock sell"); // -------- selling stocks ---------
      if(temp >= 0 && input.length() == 16){
        int amount, stockID;
        bool isNYSE = false;
        
        temp = input.find("VSNR");
        if(temp >= 0){
          temp2 = true;
          stockID = 0;
          isNYSE = true;
        }

        temp = input.find("SMTS");
        if(temp >= 0){
          temp2 = true;
          stockID = 1;
          isNYSE = true;
        }

        temp = input.find("PNNL");
        if(temp >= 0){
          temp2 = true;
          stockID = 2;
          isNYSE = true;
        }

        ccout<<"How many stocks would you like to sell? "; cin >> amount; 
        game -> addRevenue(NYSE_stockList[stockID].sellStocks(amount, balance, location));
        
        if(isNYSE == false){
  
          temp = input.find("TTTN");
          if(temp >= 0){
            temp2 = true;
            stockID = 0;
          }
  
          temp = input.find("ENIN");
          if(temp >= 0){
            temp2 = true;
            stockID = 1;
          }
  
          temp = input.find("FINF");
          if(temp >= 0){
            temp2 = true;
            stockID = 2;
          }
  
          ccout<<"How many stocks would you like to sell? "; cin >> amount; 
          game -> addRevenue(TSX_stockList[stockID].sellStocks(amount, balance, location));
        }
      }

      temp = input.find("/stock help");
        if(temp >= 0 && input.length() == 11){
          temp2 = true;
          ccout <<"\t Step into the adrenaline-pumping realm of stocks! \n\t Buy low, sell high, and conquer the dynamic markets of NYSE, known for its wild fluctuations, or TSX, offering a more stable journey. \n\t Are you ready to thrive in the challenge of stock trading?\n\t\tNote: there is a 10% transaction fee when selling stocks."; end2
        }
    }

    temp = input.find("/casino"); // ----------------------- CASINO
      
      if(temp >= 0 && input.length() == 7){
        temp2 = true;
        if(game -> hasVisitedCasinoToday == false){
          CasinoLobby(game);
        }else{
          ccout<<"You've already visted the casino today! Come back tomorrow!"; end
        }
      }
    
    temp = input.find("/nextday");
    int temp3 = input.find("/nd");
    if (temp >= 0 || temp3 >= 0) {
      temp2 = true;
      return 0;
    }

    if (temp2 == false) {
      ccout << "Invalid command. Please try again or type '/cmds' for a list of commands."; end
    }
  }
  return 1;
}

#endif

/*
Command list:
/worker
  /worker list (display all possible workers)
  /workers (display hired workers)
  /worker hire WORKER_ID (hires a worker of given ID)
  /worker fire WORKER_ID (fires a worker of given ID)

/equipment
  /equipment list (display all possible equipment)
  /equipment (display purchased equipement)
  /equipment buy EQUIPEMENT_ID (buys item of given ID)
  /equipment fire EQUIPEMENT_ID (sells item of given ID, returns 70% of original
value)

/forecast
  /forecast view (shows forecast for the week)

/business
  /business stats (displays: )
    Business age
    Total revenue
    Total expenses
    Current balance
    # of workers hired
  /business bal (balance, naturally)
  /business loc (location)
*/
