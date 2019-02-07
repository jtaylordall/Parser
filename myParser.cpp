#include "myParser.h"

using namespace std;

//Constructor
myParser::myParser(vector<Token> in) {
  v = in;
  i = 0;
  tok = v.at(i);
  catchErrors();
}

//throws errors
void myParser::error(){
  throw tok;
  i++;
}

//checks to see if tok matches expected type, increments r or throws error
void myParser::match(int type){
  if (type == tok.getTypeint()){
    i++;
    tok = v.at(i);
  }
  else{
    error();
  }
  return;
}

void myParser::op(){
  int type = tok.getTypeint();
  if(type == _add){
    match(_add);
  }
  else if(type == _multiply){
    match(_multiply);
  }
  else{
    error();
  }
  return;
}

void myParser::expression(){
  match(_left_paren);
  parameter();
  op();
  parameter();
  match(_right_paren);
  return;
}

void myParser::parameter(){
  int type = tok.getTypeint();
  if(type == _string){
    match(_string);
  }
  else if(type == _id){
    match(_id);
  }
  else{
    expression();
  }
  return;
}

void myParser::idList(){
  if(tok.getTypeint() != _right_paren){
    match(_comma);
    match(_id);
    idList();
  }
  else {
    return;
  }
}

void myParser::stringList(){
  if(tok.getTypeint() != _right_paren){
    match(_comma);
    match(_string);
    stringList();
  }
  else {
    return;
  }
}

void myParser::parameterList(){
  if(tok.getTypeint() != _right_paren){
    match(_comma);
    parameter();
    parameterList();
  }
  else {
    return;
  }
}

void myParser::predicateList(){
  if(tok.getTypeint() == _period){
    return;
  }
  else{
    match(_comma);
    predicate();
    predicateList();
  }
}

void myParser::predicate(){
  match(_id);
  match(_left_paren);
  parameter();
  parameterList();
  match(_right_paren);
  return;
}

void myParser::headPredicate(){
  match(_id);
  match(_left_paren);
  match(_id);
  idList();
  match(_right_paren);
  return;
}

void myParser::query(){
  predicate();
  match(_q_mark);
  return;
}

void myParser::rule(){
  headPredicate();
  match(_colon_dash);
  predicate();
  predicateList();
  match(_period);
  return;
}

void myParser::fact(){
  match(_id);
  match(_left_paren);
  match(_string);
  stringList();
  match(_right_paren);
  match(_period);
  return;
}

void myParser::scheme(){
  match(_id);
  match(_left_paren);
  match(_id);
  idList();
  match(_right_paren);
  return;
}

void myParser::queryList(){
  if(tok.getTypeint() != _eof){
    queryList();
    query();
  }
  else {
    return;
  }
}

void myParser::ruleList(){
  if(tok.getTypeint() == _rules || tok.getTypeint() == _id){
    rule();
    ruleList();
  }
  else if(tok.getTypeint() == _queries){
    return;
  }
  else{
    error();
  }
}

void myParser::factList(){
  if(tok.getTypeint() == _facts || tok.getTypeint() == _id){
    fact();
    factList();
  }
  else if(tok.getTypeint() == _rules){
    return;
  }
  else{
    error();
  }
}

void myParser::schemeList(){
  if(tok.getTypeint() == _schemes || tok.getTypeint() == _id){
    scheme();
    schemeList();
  }
  else if(tok.getTypeint() == _facts){
    return;
  }
  else{
    error();
  }
}

//Runs datalogProgram and catches any errors thrown
//if errors, prints failure. else prints success
void myParser::catchErrors(){
  try{
    datalogProgram();
  }
  catch (Token t){
    cout << "Failure!\n\t"<< t.createToken() << "\n";
    return;
  }
  cout << "Success!\n";
}

void myParser::datalogProgram(){
  while(tok.getTypeint() != _eof){
    match(_schemes);
    match(_colon);

    scheme();
    schemeList();

    match(_facts);
    match(_colon);
    factList();

    match(_rules);
    match(_colon);
    ruleList();

    match(_queries);
    match(_colon);
    query();
    queryList();

    return;
  }

}
