#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>
#include "Token.h"

using namespace std;

class Rule
{
private:
  vector<Token> r;
  int counter;


public:
  Rule();
  void newRule();
  vector<Token> getRules();
};
