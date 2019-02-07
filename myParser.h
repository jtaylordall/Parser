#ifndef MY_PARSER_H
#define MY_PARSER_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <cctype>
#include "Token.h"
#include "Rule.h"

using namespace std;

// scans input string
class myParser
{
  friend class Token;

private:
  vector<Token> v; //vector of Tokens passed in from myScanner
  int i;
  Token tok;


  //Token nextTok(int a);

  void match(int type);
  void error();
  void datalogProgram();
  void schemeList();
  void factList();
  void ruleList();
  void queryList();
  void scheme();
  void fact();
  void rule();
  void query();
  void headPredicate();
  void predicate();
  void predicateList();
  void parameterList();
  void stringList();
  void idList();
  void parameter();
  void expression();
  void op();
  void catchErrors();


public:
  myParser(vector<Token> in); //constructor

  enum Tokentype
  {
    _comma,
    _period,
    _q_mark,
    _left_paren,
    _right_paren,
    _colon,
    _colon_dash,
    _multiply,
    _add,
    _schemes,
    _facts,
    _rules,
    _queries,
    _id,
    _string,
    _comment,
    _undefined,
    _eof
  };
};

#endif
