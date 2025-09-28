// For delayed messages that output character by character.

#ifndef CUSTOMOUTPUT_H
#define CUSTOMOUTPUT_H

#include <iostream>
#include <ctime>
#include <unistd.h>

using namespace std;

class CustomOutputClass {
  public:
  template <typename T>
  CustomOutputClass& operator<<(const T* message) {
    while (*message != '\0') {
        cout << *message << flush;
        usleep(12500);
        ++message;
    }
    return *this;
  }

  CustomOutputClass& operator<<(string str){
    for(int i = 0; i < str.length(); i++) {
      cout << str[i] << flush;
      usleep(12500);
    }
    return *this;
  }
};

#endif
