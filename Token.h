#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>

using namespace std;

class Token
{
  friend class myScanner;

private:
  int line; //line number of token
  int type; //token type as an int (enum)
  string value; //value of token
  string new_type; //token tupe as a string

public:
  Token(); //unparameterized constructor
  Token(int in_type, string in_value, int in_line); //parameterized constructor
  string createToken(); //returns the token as a string
  string getType(); //converts type from int (enum) into string
  virtual ~Token(); //destructor
  int getTypeint();
  string getValue();

  enum tokentype
  {
    comma,
    period,
    q_mark,
    left_paren,
    right_paren,
    colon,
    colon_dash,
    multiply,
    add,
    schemes,
    facts,
    rules,
    queries,
    id,
    string_,
    comment,
    undefined,
    eof
  };
};
