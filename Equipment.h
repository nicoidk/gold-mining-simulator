#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

string horseDiseases[10] = {"Flu", "Cold", "Fever", "Cough", "Rash", "Fatigue", "Headache", "Allergy", "Starvation", "Cramps"};

int type_Shovel = 0; // Counts how many equipment of each type there is to calculate expenses & to make sure no equipment goes past the limit.
int type_Wheelbarrow = 0;
int type_Pickaxe = 0;
int type_Horse = 0; 


class Equipment{ // superclass
  public:
  bool active;
  static int productivityMultiplier; // multiplier of overall productivity (in %)
  static int equipmentID;
  int equipmentNum; // starts at 1 and counts up
  static int dailyExpenses;
  int durability, roundBought; // durability is dependant on the type of equipment, and once it hits 0, the equipment is destroyed
  double sellPrice;
  string equipmentType;


  virtual void equipmentOutput() = 0;

  Equipment(){}

  virtual void removeType() = 0; // to lessen equipment count by 1 if durability is 9 (see functions below)

  virtual void horseFate(){}

  virtual double sell() = 0; // sell piece of equipment

  void removeDay(){ // new day
    if(this-> active == true){
      this -> durability--;
      this -> updateSellPrice();
      this -> horseFate();
      
      if(durability == 0){
        active = false;
        this -> durability -= productivityMultiplier;
        this -> removeType();
        cout<<"Your "<<equipmentType<<" broke."<<endl<<endl;
      }
    }
  }

  void updateSellPrice(){
    this -> sellPrice *= 0.9;

  }

  double getProductivityMultiplier(){
    return productivityMultiplier;
  }

  double getExpenses(){
    return dailyExpenses;
  }

  int getEquipmentCount(){
    return equipmentID - 1;
  }

  void equipmentList(){
  cout << "Wheelbarrow:\n"
           << "\tPrice: $100 (per wheelbarrow)\n"
           << "\tDurability: 10 rounds\n"
           << "\tProductivity Increase: 8% per round\n"
           << "\tLimit: 3\n"
           << "\t\tPurchase ID: WHEELBARROW\n"
           << "Pickaxe:\n"
           << "\tPrice: $50 (per pickaxe)\n"
           << "\tDurability: 5 rounds\n"
           << "\tProductivity Increase: 5% per round\n"
           << "\tLimit: 5\n"
           << "\t\tPurchase ID: PICKAXE\n"
           << "Shovel:\n"
           << "\tPrice: $30 (per shovel)\n"
           << "\tDurability: 5 rounds\n"
           << "\tProductivity Increase: 2% per round\n"
           << "\tLimit: 4\n"
           << "\t\tPurchase ID: SHOVEL\n"
           << "Horses:\n"
           << "\tPrice: $200 (per horse)\n"
           << "\tDuration: Alive until RNG death\n"
           << "\tProductivity Increase: 20%\n"
           << "\tLimit: 2\n"
           << "\t\tPurchase ID: HORSE\n";
    
    }

  int getWheelbarrowCount(){
    return type_Wheelbarrow;
  }

  int getPickaxeCount(){
    return type_Pickaxe;
  }

  int getShovelCount(){
    return type_Shovel;
  }

  int getHorseCount(){
    return type_Horse;
  }
};

class Wheelbarrow : public Equipment{
  public:
  Wheelbarrow(int day){
    this -> equipmentNum = equipmentID;
    equipmentID ++;
    type_Wheelbarrow ++;
    this -> active = true;
    this -> durability = 10;
    this -> productivityMultiplier += 8;
    this -> roundBought = day;
    this -> sellPrice = 125;
    this -> equipmentType = "Wheelbarrow";
  }

  void equipmentOutput(){
    if(active == true){
      cout<<endl;
      cout<<"Stats for Equipment #"<<equipmentNum<<":"<<endl;
      cout<<"\tType: Wheelbarrow"<<endl;
      cout<<"\t Day bought: "<<roundBought<<endl;
      cout<<"\tCurrent resell value: $"<<sellPrice<<endl;
      if(active == true)
        cout<<"\tStatus: " <<durability<<" days left."<<endl;
      else
        cout<<"\tStatus: Destroyed."<<endl;
    }
  }

  double sell(){
    if(this -> active == false){ // if wheelbarrow is already destroyed or sold
      return 0;
    }
    productivityMultiplier -= 8;
    this -> active = false;
    type_Wheelbarrow --;
    return sellPrice;
  }

  void removeType(){
    type_Wheelbarrow --;
  }
};

class Pickaxe : public Equipment{
  public: 
  Pickaxe(int day){
    this -> equipmentNum = equipmentID;
    equipmentID ++;
    type_Pickaxe ++;
    this -> active = true;
    this -> durability = 5;
    this -> productivityMultiplier += 5;
    this -> roundBought = day;
    this -> sellPrice = 50;
    this -> equipmentType = "Pickaxe";
  }

  void equipmentOutput(){
    if(active == true){
      cout<<endl;
      cout<<"Stats for Equipment #"<<equipmentNum<<":"<<endl;
      cout<<"\tType: Pickaxe"<<endl;
      cout<<"\t Day bought: "<<roundBought<<endl;
      cout<<"\tCurrent resell value: $"<<sellPrice<<endl;
      if(active == true)
        cout<<"\tStatus: " <<durability<<" days left."<<endl;
      else
        cout<<"\tStatus: Destroyed."<<endl;
    }
  }

  double sell(){
    if(this -> active == false){ // if pickaxe is already destroyed or sold
      return 0;
    }
    productivityMultiplier -= 5;
    type_Pickaxe--;
    this -> active = false;
    return this -> sellPrice;
  }

  void removeType(){
    type_Pickaxe--;
  }

};

class Shovel : public Equipment{
  public:
  Shovel(int day){
    this -> equipmentNum = equipmentID;
    equipmentID ++;
    type_Shovel ++;
    this -> active = true;
    this -> durability = 5;
    this -> productivityMultiplier += 2;
    this -> roundBought = day;
    this -> sellPrice = 30;
    this -> equipmentType = "Shovel";
  }

  void equipmentOutput(){
    if(active == true){
      cout<<endl;
      cout<<"Stats for Equipment #"<<equipmentNum<<":"<<endl;
      cout<<"\tType: Shovel"<<endl;
      cout<<"\t Day bought: "<<roundBought<<endl;
      cout<<"\tCurrent resell value: $"<<sellPrice<<endl;
      if(active == true)
        cout<<"\tStatus: " <<durability<<" days left."<<endl;
      else
        cout<<"\tStatus: Destroyed."<<endl;
    }
  }

  double sell(){
    if(this -> active == false){ // if shovel is already destroyed or sold
      return 0;
    }
    productivityMultiplier -= 2;
    type_Shovel--;
    this -> active = false;
    return sellPrice;
  }

  void removeType(){
    type_Shovel--;
  }
};

class Horse : public Equipment{
  public:
  Horse(int day){
    this -> equipmentNum = equipmentID;
    equipmentID ++;
    type_Horse++;
    this -> active = true;
    this -> durability = 1000000;

    productivityMultiplier += 20;
    this -> roundBought = day;
    this -> sellPrice = 100;
    dailyExpenses += 10;
    this -> equipmentType = "Horse";
  }

  void equipmentOutput(){
    if(active == true){
      cout<<endl;
      cout<<"Stats for Equipment #"<<equipmentNum<<":"<<endl;
      cout<<"\tType: Horse"<<endl;
      cout<<"\t Day bought: "<<roundBought<<endl;
      cout<<"\tCurrent resell value: $"<<sellPrice<<endl;
      if(active == true)
        cout<<"\tStatus: Active."<<endl;
      else
        cout<<"\tStatus: Destroyed."<<endl;
    }
  }

  double sell(){
    if(this -> active == false){ // if horse is dead
      return 0;
    }
    productivityMultiplier -= 20;
    type_Horse --;
    dailyExpenses -= 10;
    this -> active = false;
    return sellPrice;
  }

  void removeType(){
    type_Horse--;
  }

  void horseFate(){
    int a = rand()%10;
    if(a == 0){
      cout<<"Your horse died!\n\tCause of death: "<<horseDiseases[rand()%10]<<endl;
      cout<<"\t Equipment ID: #"<<this -> equipmentNum<<endl;
      this -> active = false;
      productivityMultiplier -= 20; // horse insurance
      type_Horse--;
      dailyExpenses -= 10;
    }
  }
};

int Equipment::productivityMultiplier = 0;
int Equipment::dailyExpenses = 0;
int Equipment::equipmentID = 1;

// these variables are static so they can be viewed and modified by all subclasses without being inherited


#endif

/* 
  Wheelbarrow (limit 3):
  Price: $125 each
  Durability: 10 rounds
  Productivity Increase per Round: 8%
  EUC: 0.64%

Pickaxe (limit 5):
  Price: $50 each
  Durability: 5 rounds
  Productivity Increase per Round: 5%
  EUC: 0.5%

Shovel (limit 5):
  Price: $30 each
  Durability: 5 rounds
  Productivity Increase per Round: 2%
  EUC: 0.333%

Horses (limit 2):
  Price: $200 each + $5 per round
  Duration: Alive until RNG death
  Productivity Increase per Round: 20%

EUC (Efficiency per Unit Cost): measures the productivity increase per unit of currency spent.
*/
