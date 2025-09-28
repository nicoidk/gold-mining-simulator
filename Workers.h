#ifndef WORKERS_H
#define WORKERS_H

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

string firstNames[15] = {"Bill", "Jeffrey", "Phillip", "David", "Andrew", "Ian", "Justin", "Tristan", "Liam", "Bernard", "Ian", "Sean", "Samuel", "Matthew", "Joshua"};

string lastNames[15] = {"Smith", "Johnson", "Williams", "Brown", "Jones", "Miller", "Davis", "Wilson", "Moore", "Boyd", "Anderson", "Thomas", "Harris", "Martin", "White"};

string leaveCauses[10] = {"Poor Management", "Limited Growth", "Inadequate Compensation", "Toxic Culture", "Lack of Recognition", "Unfulfilling Work", "Insufficient Benefits", "Work-Life Balance", "No Career Development", "Commute Stress"};

int type_Prospector = 0; // Counts how many worker of each type there is to calculate expenses & to mak sure theres no workers past the limit.
int type_Manager = 0;
int type_Polisher = 0;
int type_Trader = 0; 

class Workers{ // Superclass
  public:
  static double workerproductivity; // ( gold per hour )
  static int goldsellprice; // dollar per troy ouce
  static int employeeID; // starts at one and counts up
  virtual void workerOutput() = 0; // pure virtual

  int roundHired; // round the worker was hired ( used to determine stats )
  int employeeNum; // employeeNum is ALWAYS 1 unit greater than his placement in the array
  int tier; 
  string prenom, nom; // name and last name (french)
  bool isHired;

  Workers(){} // no worker will be jobless 

  string generateFirst(){
    srand(time(0));
    return firstNames[rand()%15];
  }
  string generateLast(){
    srand(time(0));
    return lastNames[rand()%15];
  }

  virtual void fireEmployee() = 0;
  virtual void leaveEmployee() = 0;

  double getProductivity(){
      return workerproductivity;
  }

  double getExpenses(char Location){
    int expn = type_Prospector * 50 +
            type_Manager * 100 +
            type_Polisher * 50 +
            type_Trader * 80;

    if(Location == '2'){
      return 0.7 * expn;
    }else{
      return expn;
    }
  }

  int getSellPrice(){
    return this -> goldsellprice;
  }

  int getEmployeeCount(){ // TOTAL EMPLOYEE COUNT (including fired / left)
    return employeeID - 1;
  }

  int getProspectorCount(){
    return type_Prospector;
  }

  int getManagerCount(){
    return type_Manager;
  }

  int getPolisherCount(){
    return type_Polisher;
  }

  int getTraderCount(){
    return type_Trader;
  }

  void workerList(){
    //Prospector
    cout<<"Prospectors: find 0.5 ounces of gold per hour"<<endl;
    cout<<"\tOriginal Hiring Cost: $1000"<<endl;
    cout<<"\tWage: $50 / Day"<<endl;
    cout<<"\tMaximum: 10"<<endl;
    cout<<"\t\tHiring ID: PROSPECTOR"<<endl<<endl;
    //Manager
    cout<<"Managers: greatly increase worker productivity"<<endl;
    cout<<"\tOriginal Hiring Cost: $1000"<<endl;
    cout<<"\tWage: $100 / Day"<<endl;
    cout<<"\tMaximum: 3"<<endl;
    cout<<"\t\tHiring ID: MANAGER"<<endl<<endl;
    //Polisher
    cout<<"Polishers: improve gold selling price"<<endl;
    cout<<"\tOriginal Hiring Cost: $750"<<endl;
    cout<<"\tWage: $50 / Day"<<endl;
    cout<<"\tMaximum: 5"<<endl<<endl;
    cout<<"\t\tHiring ID: POLISHER"<<endl<<endl;
    //Trader
    cout<<"Trader: Greatly improves gold sell price"<<endl;
    cout<<"\tOriginal Hiring Cost: $2000"<<endl;
    cout<<"\tWage: $80 / Day"<<endl;
    cout<<"\tMaximum: 1"<<endl;
    cout<<"\t\tHiring ID: TRADER"<<endl<<endl;
  }

  void newDay(int day){
    if(this -> isHired == true){
      // Tier Levels
      if(day - roundHired == 5){
        this -> upgradeTierLevel();
      }else if(day - roundHired == 10){
        this -> upgradeTierLevel();
      }else if(day - roundHired == 15){
        this -> upgradeTierLevel();
      }else if(day - roundHired == 25){
        this -> upgradeTierLevel();
      }
      
      // Resign rate -> 1/30
      if(rand() % 30 == 19 & this -> getEmployeeCount() > 1){
          this -> leaveEmployee();
      }
    }
  }

  virtual void upgradeTierLevel() = 0;

  string getTier(int tier){
    if(tier == 1){
      return "I";
    }else if(tier == 2){
      return "II";
    }else if(tier == 3){
      return "III";
    }else if(tier == 4){
      return "IV";
    }else{
      return "V";
    }
  }


};

class Prospector : public Workers{
  public:

  Prospector(int day){
    this -> prenom = generateFirst();
    this -> nom = generateLast();
    workerproductivity += .5; // generates .5 ounces of gold per hour.
    this -> roundHired = day;
    this -> employeeNum = employeeID;
    employeeID++;
    type_Prospector++;
    this -> isHired = true;
    this -> tier = 1;
  }

  void workerOutput(){
    if(isHired == true){
      cout<<endl;
      cout<<"Employee stats for "<<prenom<<" "<<nom<<":"<<endl;
      cout<<"\tEmployement: Prospector"<<endl;
      cout<<"\tDay Hired: "<<roundHired<<endl;
      cout<<"\t\tEmployee ID: "<<this -> employeeNum<<endl;
      cout<<"\t\tTier Level: "<<getTier(this -> tier)<<endl;
      if(isHired == true)
        cout<<"\tEmployement Status: Working\n"<<endl;
      if(isHired == false)
        cout<<"\tEmployement Status: Unemployed\n"<<endl;
    }
  }

  void fireEmployee(){
    if(isHired == true){
      this -> isHired = false;
      workerproductivity -= .5 * this->tier; // removes .5 ounces of gold per hour * tier level.
      type_Prospector--;
      cout<<"Employee #"<<employeeNum<<": "<<prenom<<" "<<nom<<" was fired."<<endl;
    }else{
      cout<<"Worker is already fired."<<endl;
    }
  }

  void leaveEmployee(){
    if(type_Prospector > 1){
      this -> isHired = false;
      workerproductivity -= .5 * this->tier; // removes .5 ounces of gold per hour * tier level.
      type_Prospector--;
      cout<<"Employee id #"<<employeeNum<<": "<<prenom<<" "<<nom<<" left due to " <<leaveCauses[rand()%10]<<"."<<endl;
      cout<<"\tType: Prospector"<<endl;
    }
  }

  void upgradeTierLevel(){
    workerproductivity += .5;
    this -> tier ++;
  }

};

class Manager : public Workers{
  public:

  Manager(int day){
    this -> prenom = generateFirst();
    this -> nom = generateLast();
    workerproductivity *= 1.5; // increases overall productivity by 50%
    this -> roundHired = day;
    this -> employeeNum = employeeID;
    employeeID++;
    type_Manager++;
    this -> isHired = true;
    this -> tier = 1;
  }

  void workerOutput(){
    if(isHired == true){
      cout<<endl;
      cout<<"Employee stats for "<<prenom<<" "<<nom<<":"<<endl;
      cout<<"\tEmployement: Manager"<<endl;
      cout<<"\tDay Hired: "<<roundHired<<endl;
      cout<<"\t\tEmployee ID: "<<this -> employeeNum<<endl;
      cout<<"\t\tTier Level: "<<getTier(this -> tier)<<endl;
      if(isHired == true)
        cout<<"\tEmployement Status: Working\n"<<endl;
      if(isHired == false)
        cout<<"\tEmployement Status: Unemployed\n"<<endl;
    }
  }

  void fireEmployee(){
    if(isHired == true){
      this -> isHired = false;
      workerproductivity /= ( 1.5 + 0.1 * (this -> tier - 1)); // decreases worker productivity by 50%
      type_Manager--;
      cout<<"Employee #"<<employeeNum<<": "<<prenom<<" "<<nom<<" was fired."<<endl;
    }else{
      cout<<"Worker is already fired."<<endl;
    }
  }

  void leaveEmployee(){
    this -> isHired = false;
    workerproductivity /= ( 1.5 + 0.1 * (this -> tier - 1)); // decreases worker productivity by 50%
    type_Manager--;
    cout<<"Employee id #"<<employeeNum<<": "<<prenom<<" "<<nom<<" left due to " <<leaveCauses[rand()%10]<<"."<<endl;
    cout<<"\tType: Manager"<<endl;
    
  }

  void upgradeTierLevel(){
    this -> tier ++;
    if(this -> tier == 2){
      workerproductivity /= 1.5;
      workerproductivity *= 1.6; // increases worker productivity by an additional 10%
    }if(this -> tier == 3){
      workerproductivity /= 1.6;
      workerproductivity *= 1.7; // increases worker productivity by an additional 20% 
    }if(this -> tier == 4){
      workerproductivity /= 1.7;
      workerproductivity *= 1.8; // increases worker productivity by an additional 30% |
    }if(this -> tier == 5){
      workerproductivity /= 1.8;
      workerproductivity *= 1.9; // increases worker productivity by an additional 40%
    }
  }
};

class Polisher : public Workers{
  public:

  Polisher(int day){
    this -> prenom = generateFirst();
    this -> nom = generateLast();
    goldsellprice += 3; // increases selling price of gold by $3 per ounce
    this -> roundHired = day;
    this -> employeeNum = employeeID;
    employeeID++;
    type_Polisher++;
    this -> isHired = true;
    this -> tier = 1;
  }

  void workerOutput(){
    if(isHired == true){
      cout<<endl;
      cout<<"Employee stats for "<<prenom<<" "<<nom<<":"<<endl;
      cout<<"\tEmployement: Polisher"<<endl;
      cout<<"\tDay Hired: "<<roundHired<<endl;
      cout<<"\t\tEmployee ID: "<<this -> employeeNum<<endl;
      cout<<"\t\tTier Level: "<<getTier(this -> tier)<<endl;
      if(isHired == true)
        cout<<"\tEmployement Status: Working\n"<<endl;
      if(isHired == false)
        cout<<"\tEmployement Status: Unemployed\n"<<endl;
    }
  }

  void fireEmployee(){
    if(isHired == true){
      this -> isHired = false;
      goldsellprice -= (3 + (this->tier-1)); // decreases price of gold by $3 per ounce + $1 per ounce per tier level.
      type_Polisher--;
      cout<<"Employee #"<<employeeNum<<": "<<prenom<<" "<<nom<<" was fired."<<endl;
  }else{
      cout<<"Worker is already fired."<<endl;
    }
  }

  void leaveEmployee(){
    this -> isHired = false;
    goldsellprice -= (3 + (this->tier-1)); // decreases price of gold by $3 per ounce + $1 per ounce per tier level.
    type_Polisher--;
    cout<<"Employee id #"<<employeeNum<<": "<<prenom<<" "<<nom<<" left due to " <<leaveCauses[rand()%10]<<"."<<endl;
    cout<<"\tType: Polisher"<<endl;
  }

  void upgradeTierLevel(){
    this -> tier ++;
    goldsellprice += 1;
  }
};

class Trader : public Workers{
  public:

  Trader(int day){
    this -> prenom = generateFirst();
    this -> nom = generateLast();
    goldsellprice += 10; // increases selling price of gold by $10 per ounce
    this -> roundHired = day;
    this -> employeeNum = employeeID;
    employeeID++;
    type_Trader++;
    this -> isHired = true;
    this -> tier = 1;
  }

  void workerOutput(){
    if(isHired == true){
      cout<<endl;
      cout<<"Employee stats for "<<prenom<<" "<<nom<<":"<<endl;
      cout<<"\tEmployement: Trader"<<endl;
      cout<<"\tDay Hired: "<<roundHired<<endl;
      cout<<"\t\tEmployee ID: "<<this -> employeeNum<<endl;
      cout<<"\t\tTier Level: "<<getTier(this -> tier)<<endl;
      if(isHired == true)
        cout<<"\tEmployement Status: Working\n"<<endl;
      if(isHired == false)
        cout<<"\tEmployement Status: Unemployed\n"<<endl;
    }
  }

  void fireEmployee(){
    if(this -> isHired == true){
      this -> isHired = false;
      goldsellprice -= (10 - 3 * (this -> tier - 1)); // decreases price of gold by $10 per ounce
      type_Trader--;
      cout<<"Employee #"<<employeeNum<<": "<<prenom<<" "<<nom<<" was fired."<<endl;
    }else{
      cout<<"Worker is already fired."<<endl;
    }
  }

  void leaveEmployee(){
    this -> isHired = false;
    goldsellprice -= (10 - 3 * (this -> tier - 1)); // decreases price of gold by $10 per ounce
    type_Trader--;
    cout<<"Employee id #"<<employeeNum<<": "<<prenom<<" "<<nom<<" left due to " <<leaveCauses[rand()%10]<<"."<<endl;
    cout<<"\tType: Trader/nd"<<endl;
  }

  void upgradeTierLevel(){
    this -> tier ++;
    goldsellprice += 3; // increases price of gold by $3
  }
};

double Workers::workerproductivity = 0;
int Workers::goldsellprice = 20;
int Workers::employeeID = 1;

// these variables are static so they can be viewed and modified by all subclasses without being inherited

#endif
