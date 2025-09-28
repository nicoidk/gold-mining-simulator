#ifndef FORECAST_H
#define FORECAST_H

#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

class Forecast {
public:
  int weather[7]; // mon - sun
  char businessLocation;

  Forecast(char location) { this->businessLocation = location; };

  void generateForecast(int day) {
    if ((day - 1) % 7 == 0) {
      for (int i = 0; i < 7; i++) {
        weather[i] =
            -1 * (rand() % 12 + 20); // Range between -20 degrees to -31 degrees
        if (this->businessLocation == '4') // Aurora Valley
          weather[i] += 15;
      }
    }
  }

  void getForecast(int day) {
    cout << endl << "Forecast for the week: " << endl;
    cout << "\tMonday: " << weather[0] << "°C" << endl;

    cout << "\tTuesday: " << weather[1] << "°C" << endl;

    cout << "\tWednesday: " << weather[2] << "°C" << endl;

    cout << "\tThursday: " << weather[3] << "°C" << endl;

    cout << "\tFriday: " << weather[4] << "°C" << endl;

    cout << "\tSaturday: " << weather[5] << "°C" << endl;

    cout << "\tSunday: " << weather[6] << "°C" << endl;
    
    cout << endl;
  };

  int getCurrentWeather(int day) { return this->weather[day % 7]; }
};

#endif
