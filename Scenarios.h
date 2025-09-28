#ifndef SCENARIOS_H
#define SCENARIOS_H

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

#include "CustomOutput.h"

#define end cout<<endl;
#define end2 cout<<endl<<endl;

int gamblerScenario(int);
int voyageScenario(int);
int rivalScenario(int);
int quizScenario(int);
int goldHuntScenario(int);

bool scenario_1 = false;
bool scenario_2 = false;
bool scenario_3 = false;
bool scenario_4 = false;
bool scenario_5 = false;

CustomOutputClass ccout;

int playRandomScenario(int Balance){
  ccout << "\n* * * * * * * * * * * * * * * * * * * * * * * *\n";
  
  bool allScenariosUsed = scenario_1 && scenario_2 && scenario_3 && scenario_4 && scenario_5;
  
  if (allScenariosUsed) {
      scenario_1 = scenario_2 = scenario_3 = scenario_4 = scenario_5 = false; 
  }

  int randomScenario;
  do {
      randomScenario = rand() % 5 + 1;
  } while ((randomScenario == 1 && scenario_1) ||
           (randomScenario == 2 && scenario_2) ||
           (randomScenario == 3 && scenario_3) ||
           (randomScenario == 4 && scenario_4) ||
           (randomScenario == 5 && scenario_5));

    switch (randomScenario) {
        case 1:
          return gamblerScenario(Balance);
            break;
        case 2:
          return voyageScenario(Balance);
            break;
        case 3:
          return rivalScenario(Balance);
            break;
        case 4:
          return quizScenario(Balance);
            break;
        case 5:
          return goldHuntScenario(Balance);
            break;
    }
  ccout << "\n* * * * * * * * * * * * * * * * * * * * * * * *\n";
  return 0;
}

// -----------------------------------------------------------------------------------

  int gamblerScenario(int Balance){
    string input = "z"; 
    int reward = 0, playerTotal = 0, dealerTotal = 0;

    ccout << "*\tA charismatic gambler arrives in town, proposing a game of dice.\n";
    ccout << "*\tIf you choose to participate and win, your business can recieve up to a lucrative reward of $100 in gold.\n";

    ccout<<"*\t1. Participate in a higher stakes match ( $50 )"; end
    ccout<<"*\t2. Participate in a lower stakes match ( $15 )"; end
    cout << "*\t-";
    cin >> input;

    while(input != "1" && input != "2"){
      ccout << "*\tInvalid input, try again.";
      cout << "*\t-";
      cin >> input;
    }

    if(input == "1"){
      reward -= 50;

      while(1){
        ccout<<"*\tType 'ROLL' to roll the dice.";
        cout << "*\t-";
        cin >> input;
        while(input != "ROLL"){
          ccout<<"*\tType 'ROLL' to roll the dice.";
          cin >> input;
        }
        int a = rand()%6+1;
        int b = rand()%6+1;
        ccout<<"You roll a ";
        cout<<a;
        ccout<<" and a ";
        cout<<b<<".";
        
        playerTotal = a + b;
        ccout<<"*\tYour total: ";
        cout<<playerTotal<<endl;
        
        a = rand()%6+1;
        b = rand()%6+1;
        
        ccout<<"*\tDealer roll a ";
        cout<<a;
        ccout << " and a ";
        cout<<b<<".";
        
        dealerTotal = a + b;
        
        ccout<<"*\t\tTheir total: ";
        cout<<dealerTotal<<endl;

        if(playerTotal > dealerTotal){
          ccout<<"*\tYou won $100!";
          reward += 100;
          break;
        }else if(playerTotal < dealerTotal){
          ccout<<"*\tYou lost $50.";
          break;
        }else{
          ccout<<"*\tTie. Play again.";
        }
      }
    }else if(input == "2"){
      reward -= 15;
      while(1){
        ccout<<"*\tType 'ROLL' to roll the dice.";
        cout << "*\t-";
        cin >> input;
        
        while(input != "ROLL"){
          ccout<<"*\tType 'ROLL' to roll the dice.";
          cout << "*\t-";
          cin >> input;
        }
        
        int a = rand()%6+1;
        int b = rand()%6+1;
        
        ccout<<"*\tYou roll a ";
        cout<<a;
        ccout<<" and a ";
        cout<<b<<".";
        
        playerTotal = a + b;
        
        ccout<<"*\t\tYour total: ";
        cout<<playerTotal<<endl;
        
        a = rand()%6+1;
        b = rand()%6+1;
        
        ccout<<"*\tDealer rolled a ";
        cout<<a;
        ccout<<" and a ";
        cout<<b<<".";
        
        dealerTotal = a + b;
        ccout<<"*\t\tTheir total: ";
        cout<<dealerTotal<<endl;

        if(playerTotal > dealerTotal){
          ccout<<"*\tYou won $30!";
          reward += 30;
          break;
        }else if(playerTotal < dealerTotal){
          ccout<<"*\tYou lost $15.";
          break;
        }else{
          ccout<<"*\tTie. Play again.";
        }
      }
    }
    cout << "\n* * * * * * * * * * * * * * * * * * * * * * * *";
    return reward;
  }

// -----------------------------------------------------------------------------------

  int voyageScenario(int Balance){
    int reward = 0;
    ccout<<"*\tThe discovery of enormous riches, according to a renowned geologist, demands a risky voyage through difficult terrain."; end
    
    ccout<<"*\t You must decide whether to invest in the expedition or continue with your current mining activities.";  end2

    string input = "z";
    ccout << "*\t\t1. Invest in the perilous expedition ( $75 )";
    ccout << "*\t\t2. Continue current mining operations ( $0 )";
    cout << "*\t-";

    cin >> input;

    while (input != "1" && input != "2") {
        ccout << "*\tInvalid input, try again.";
        cout << "*\t-";
        cin >> input;
    }

    if (input == "1") {
        int investmentCost = 75;
        int boostersInvested;
        ccout << "*\tHow many boosters would you like to invest in the expedition? (each booster costs $10)";
        cout << "*\t-";
        cin >> boostersInvested;

        while (boostersInvested < 0 || boostersInvested*10 > Balance){
          ccout<<"*\tInvalid input. Your balance is: ";
          cout<<Balance<<endl;
          cout << "*\t-";
          cin >> boostersInvested;
        }

        investmentCost += boostersInvested * 10;

            int a = rand() % 3;  // 0: Failure, 1: Moderate success, 2: Great success

            if (a == 0) {
                ccout << "*\tThe perilous expedition ends in failure. You recover some resources but suffer losses.";

                reward -= investmentCost / 2;
            } else if (a == 1) {
                ccout << "*\tThe perilous expedition is moderately successful. You recover some resources and make a modest profit.";

                reward += investmentCost / 2;
            } else if (a == 2) {
                ccout << "*\tThe perilous expedition is a great success! You discover substantial riches and gain a significant profit.";

                reward += investmentCost * 2;
            }
    } else if (input == "B") {
        ccout << "*\tYou decide to continue with your current mining activities.";
    }
    ccout << "\n* * * * * * * * * * * * * * * * * * * * * * * *";
    return reward;
  }

// -----------------------------------------------------------------------------------

  int rivalScenario(int Balance){
    int reward = 0;
    ccout<<"*\tA rival mining company sets up camp nearby, attempting to outshine your operation by luring away skilled workers with promises of higher wages and better accommodations."; end
    ccout<<"*\tIn response, you must decide whether to use your boosters to improve working conditions and retain your workforce or employ more aggressive tactics to undermine the rival's efforts and protect your claim."; end2

    string input = "z";
    ccout << "*\t\t1. Improve working conditions with boosters ( $30 per booster )";end
    ccout << "*\t\t2. Employ aggressive tactics to undermine the rival ( cost: $50 )";end

    cout << "*\t-";
    cin >> input; 
    while(input != "1" && input != "2"){
      ccout << "*\tInvalid input, try again.";
      
      cout << "*\t-";
      cin >> input;
    }

    if(input == "1"){
      int boostersInvested;
      ccout<<"\t*\tHow many boosters?";
      cout << "*\t-";
      cin >> boostersInvested;
      
      while(boostersInvested<0 || boostersInvested*30>Balance){
        ccout<<"*\tInvalid input. Your balance is: ";
        cout<<Balance<<endl;
        
        cout << "*\t-";
        cin >> boostersInvested;
      }

      if(boostersInvested<3){
        ccout<<"*\tWorkers remain unhappy with your efforts. You are forced to pay a $50 fine to keep your workers.";
        reward-=50;
      }else{
        ccout<<"*\tYour workers become happy again and you gain a significant profit from the increase in production.";
        reward += rand()%50+30;
      }

    }else if(input == "2"){
      reward -= 50;
      int a = rand()%2;
      if(a == 0){
        ccout<<"*\tYou successfully undercut your competitor and operations return to normal.";
        reward += 50;
      }else if(a == 2){
        ccout<<"*\tYou were unable to defend yourself against your rival's tactics and had to pay a $25 fine for illegal business practices.";
        reward -= 25;
      }
    }
    ccout << "\n* * * * * * * * * * * * * * * * * * * * * * * *";
    return reward;
  }

// -----------------------------------------------------------------------------------

  int quizScenario(int Balance){
    int reward = 0; int correctAnswers = 0;

    ccout<<"*\tThe local saloon hosts a quiz night with questions related to mining, geography, and history. Participate to test your knowledge and potentially win cash prize and/or more mining equipement."; end

    string input = "z";
    ccout<<"*\t\t1. Participate in the quiz ( $50 )"; end
    ccout<<"*\t\t2. Skip the quiz ( $0 )"; end

    cout << "*\t-";
    cin >> input; 
    while(input != "1" && input != "2"){
      ccout << "*\tInvalid input, try again."; end
      cout << "*\t-";
      cin >> input;
    }

    if (input == "1") {
      if(Balance < 50){
        ccout<<"*\tInsufficient funds. Your balance is: ";
        cout<<Balance<<endl;
      }else{
        reward -= 50;
        // Question 1
        ccout << "*\tQuestion 1: What is the capital of the Yukon Territory?"; end
        ccout << "*\ta. Dawson City\tb. Whitehorse\tc. Fairbanks\n";
        cout << "*\t-";
        cin >> input;
        if (input == "b") {
            ccout << "*\tCorrect!\n"; end
            correctAnswers++;
        } else {
            ccout << "*\tIncorrect.\n"; end
        }

        // Question 2
        ccout << "*\tQuestion 2: Which river was a major route for Klondike prospectors?"; end
        ccout << "*\ta. Colorado River\tb. Yukon River\tc. Mississippi River\n";
        cout << "*\t-";
        cin >> input;
        if (input == "b") {
            ccout << "*\tCorrect!\n"; end
            correctAnswers++;
        } else {
            ccout << "*\tIncorrect.\n"; end
        }

        // Question 3
        ccout << "*\tQuestion 3: What year did the Klondike Gold Rush begin?"; 
        ccout << "*\ta. 1896\tb. 1905\tc. 1870\t";
        cout << "*\t-";
        cin >> input;
        if (input == "a") {
            ccout << "*\tCorrect!\n"; end
            correctAnswers++;
        } else {
            ccout << "*\tIncorrect.\n"; end
        }

        // Question 4
        ccout << "*\tQuestion 4: What type of mining was predominant during the Klondike Gold Rush?"; end
        ccout << "*\ta. Silver mining\tb. Placer mining\tc. Coal mining\n"; 

        cout << "*\t-";
        cin >> input;
        if (input == "b") {
            ccout << "*\tCorrect!\n"; end
            correctAnswers++;
        } else {
            ccout << "*\tIncorrect.\n"; end
        }

        // Question 5
        ccout << "*\tQuestion 5: What famous trail did prospectors use to access the Klondike region?"; end
        ccout << "*\ta. Oregon Trail\tb. Chilkoot Trail\tc. Appalachian Trail\n"; end

        cout << "*\t-";
        cin >> input;
        if (input == "b") {
            ccout << "*\tCorrect!\n"; end
            correctAnswers++;
        } else {
            ccout << "*\tIncorrect.\n"; end
        }

        // Quiz Results
        if (correctAnswers >= 3) {
          
            ccout << "*\tCongratulations! You answered ";
          cout<< correctAnswers;
          ccout <<" questions correctly. You win $";
          cout<<correctAnswers * 50 + 50 <<"!";
          
          reward += correctAnswers * 50 + 50;
          
        } else {
          ccout << "*\tBetter luck next time. You answered ";
          cout<<correctAnswers;
          ccout<<" questions correctly.";
        }
      }

    } else if (input == "2") {
        ccout << "*\tYou decide to skip the quiz."; end
    }
    ccout << "\n* * * * * * * * * * * * * * * * * * * * * * * *\n";
    return reward;
  }

// -----------------------------------------------------------------------------------

int goldHuntScenario(int Balance){
  int reward = 0; 

  ccout<< "*\tA prospector within your team has recently uncovered an abandoned gold mine in the promising expanse of the Klondike Territory, assuring substantial wealth."; end2
  ccout<< "*\tTo partake in this opportunity, you need to acquire an ancient mining machine capable of navigating the challenging terrain."; end2

  string input = "z";
  ccout << "*\t\t1. Purchase the mining machine ( $50 )"; end
  ccout << "*\t\t2. Continue current mining operations ( $0 )"; end

  cout << "*\t-";
  cin >> input;
  while(input != "1" && input != "2"){
    ccout << "*\tInvalid input, try again."; end
    cout << "*\t-";
    cin >> input;
  }

  if(input == "1"){
    if(Balance < 50){
      ccout<<"*\tInsufficient funds. Your balance is: ";
      cout << Balance << endl;
    }else{
      ccout<< "*\tYou are located on a grid from 1m to 100m."; end
      ccout<< "*\tYour objective is to navigate the grid to find the hidden gold."; end
      ccout<< "*\tYou will be told whether your current guess was warmer or colder than the latter."; end
      ccout<< "*\tCorrectly guessing will win you $200."; end

      int randNum = rand() % 100 + 1;
      int currentGuess, lastGuess;

      for(int i = 1; i <= 10; i++){
        ccout<<"*\tGuess ";
        cout<<i<<"/10: "; 
        
        cout << "\t- ";
        cin >> currentGuess; 

        if(i == 1){
          if(currentGuess == randNum){
            ccout<<"*\tYou win!";
            reward = 200;
            return reward;
          }else{
            lastGuess = currentGuess;
          }
        }else{
          if(currentGuess == randNum){
            ccout<<"*\tYou win!";
            reward = 200;
            return reward;
          }else if(abs(currentGuess - randNum) < abs(lastGuess - randNum)){
            ccout<<"*\tWarmer"; end
            lastGuess = currentGuess;
          }else if(abs(currentGuess - randNum) > abs(lastGuess - randNum)){
            ccout<<"*\tColder"; end
            lastGuess = currentGuess;
          }else{
            ccout<<"*\tSame temperature..."; end
            lastGuess = currentGuess;
          }
        }
      }
      ccout<<"*\tYou lose. Answer: ";
      cout<<randNum<<".";
      return reward;

    }
  }else if(input == "2"){
    ccout << "*\tYou decide to miss the opportunity.";
  }
  ccout << "\n* * * * * * * * * * * * * * * * * * * * * * * *"; end2
  return reward;
}

#endif
