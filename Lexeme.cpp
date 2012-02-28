#ifndef LEXEME_H
#define LEXEME_H
#include <iostream>
using namespace std;

#define CMD  10 // cualquier string
#define AND  11 // &
#define ERR  12 // 2>
#define OUT  13 // >
#define APP  14 // >>
#define IN   15 // <
#define CD   16 // cd
#define PIPE 17 // |
#define EXIT 18 // exit

struct Lexeme{

  char* data;
  int type;
  
  Lexeme() {
    type = 0;
    data = NULL;
  }
	
  Lexeme(int tipo, char* dato) {
    type = tipo;
    data = dato;
  }
  
  virtual ~Lexeme() {}
  
  // 	friend ostream& operator<<(ostream& ostr, const Lexeme& output) {
  // 		return ostr << data;
  // 	}
  
};

#endif // LEXEME_H
