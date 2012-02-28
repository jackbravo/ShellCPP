#ifndef READER_H
#define READER_H
#include "Lexeme.cpp"
#include <cstdio>
#include <cstring>
using namespace std;

class Reader{
  
  char* leido;
  
public:
  
  Reader()
  {
    leido = NULL;
  }

  virtual ~Reader() {}

  virtual void flush()
  {
    leido = NULL;
  }

  virtual Lexeme* nextLexeme()
  {
    char* token = NULL;
    Lexeme* lex = NULL;

    // --------------------
    // Parte de lectura
    // --------------------
    if(!leido)
      {	 // primera vez que haces cin
	leido = new char[256];
	cin.getline(leido,256,'\n');
	token = strtok(leido, " \t\n");
      }
    else
      {	 // si ya hiciste un cin
	token = strtok(NULL, " \t\n");
      }
    // --------------------
    if ( token == NULL ) 
      {
	lex = NULL;
	leido = NULL;
      }
    else if ( strcmp(token, "exit") == 0 ) lex = new Lexeme(EXIT, token);
    else if ( strcmp(token,    "|") == 0 ) lex = new Lexeme(PIPE, token);
    else if ( strcmp(token,    "&") == 0 ) lex = new Lexeme(AND, token);
    else if ( strcmp(token,   ">>") == 0 ) lex = new Lexeme(APP, token);
    else if ( strcmp(token,   "2>") == 0 ) lex = new Lexeme(ERR, token);
    else if ( strcmp(token,    ">") == 0 ) lex = new Lexeme(OUT, token);
    else if ( strcmp(token,    "<") == 0 ) lex = new Lexeme(IN, token);
    else if ( strcmp(token,   "cd") == 0 ) lex = new Lexeme(CD, token);
    else lex = new Lexeme(CMD, token);
 
    return lex;
  }
};

#endif // READER_H
