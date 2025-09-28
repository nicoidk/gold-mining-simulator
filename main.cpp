#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <limits>
using namespace std;

#include "Business.h"
#include "cmds.h"
#include "Equipment.h"
#include "Forecast.h"
#include "Workers.h"
#include "CustomOutput.h"
#include "Investements.h"

#define end cout<<endl;
#define end2 cout<<endl<<endl;


int main() {
  ios_base::sync_with_stdio(true); // Synchronizing the IO buffers
  cin.tie(NULL);

  //Custom Output Class
  CustomOutputClass ccout;

  // Stock Class Setup (Price, Name, Ticker)
  NYSE NYSE_stockList[3] = {
    NYSE(87.50, "Visionary Ventures", "VSNR"),
    NYSE(112.30, "Summit Solutions", "SMTS"),
    NYSE(145.80, "Pinnacle Partners", "PNNL"),
  };

  TSX TSX_stockList[3] = {
      TSX(50.25, "Tech Titan", "TTTN"),
      TSX(75.10, "Energy Innovations", "ENIN"),
      TSX(120.55, "Financial Frontier", "FINF"),
  };
  
  
  
  srand(time(0));
  ccout<<"Welcome to Trail of Gold"; end
  ccout<<"========================\n"; end

  string CMD; char location = 'z';

  ccout<<"Enter your business name: "; getline(cin, CMD); 
  
  ccout<<"\nChoose your location: "; end2
  
    // chillwater creek
    ccout << "\t- 1. Chillwater Creek "; end
      ccout << "\t\t - 50% cash back on equipment purchases"; end2
  
    // frosty falls
    ccout << "\t- 2. Frosty Falls "; end
      ccout << "\t\t - 30% reduced worker wages "; end2
  
    //klondike kaves
    ccout << "\t- 3. Treasure Tundra "; end
      ccout << "\t\t - no stock selling fee"; end
      ccout << "\t\t - unlimited casino access"; end2
  
    //aurora valley
    ccout << "\t- 4. Aurora Valley"; end
      ccout << "\t\t - warmer weather"; end2
  
    //icicle enclave
    ccout << "\t- 5. Icicle Enclave"; end
      ccout << "\t\t - 15% gold multiplier"; end2
  
    while(location < 49 || location > 53){ // while the input is valid
      ccout<<"\tChoice: ";
      cin >> location;
    }

    int day = 0;
    
    Business game(CMD, location); 
    Business *gamePtr = &game;
    Forecast weather(location);
  
    Workers *workerList[100]; 
    workerList[0] = new Prospector(1); // Free prospector
  
  
    Equipment *equipList[100];
    equipList[0] = new Shovel(1); // Free shovel
    
    while( game.goldBalance <= 100000 ){
      day++;
      
      // ----------- Pre-round stats start -----------
        cout<<endl;
        weather.generateForecast(day);
        game.newDay(  // day #, productivity (gold mined / hour), productivity multiplier, expenses, gold sell price, weather
          day, 
          workerList[0] -> getProductivity(), 
          equipList[0] -> getProductivityMultiplier(),
          workerList[0] -> getExpenses(game.businessLocation) + equipList[0] -> getExpenses(), 
          workerList[0] -> getSellPrice(),  
          weather.getCurrentWeather(day-1)
          ); 
        
      // equipment durability change
      for(int i = 0; i < equipList[0] -> getEquipmentCount(); i++){
        equipList[i] -> removeDay();
      }
  
      for(int i = 0; i < workerList[0] -> getEmployeeCount(); i++){
        workerList[i] -> newDay(day);
      }
  
      // 
  
      // stock price changes
      for(int i = 0; i < 5; i ++){
        NYSE_stockList[i].priceChange();
      }
      for(int i = 0; i < 5; i ++){
        TSX_stockList[i].priceChange();
      }
      
      // ----------- Pre-round stats end -----------
      
       if( day > 5 && rand()%5 == 0){
         game.goldBalance += playRandomScenario(game.getBalance()); 
       }
  
      cout << "\t- ";
      
      while(1){
        getline(cin, CMD);
        if(CMD != ""){ // preventing blank inputs
          if ( ! commandInput(CMD, gamePtr, weather, workerList, equipList, NYSE_stockList, TSX_stockList, day)){ // Command input, Business class, Forecast class, Worker array, Equipment array, NYSE, TSX, Day #
            break;
          }
          ccout<<"\n================================="; end2
          cout << "\t- ";
        }
      }
    }
  
  ccout<<"You beat ";
  ccout<<game.getLocation();
  ccout<<" in ";
  cout<<day;
  ccout<<" days!"; end2
    

}
