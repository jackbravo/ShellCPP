#ifndef PARSER_H
#define PARSER_H
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "Lexeme.cpp"
#include "Reader.cpp"
#include "CMDException.cpp"
#include "Comando.cpp"
using namespace std;

#define END 20
#define NXT 21
#define RD 7
#define WR 6

class Parser{

  Reader* rdr;
  Lexeme* current;

public:

  Parser(Reader* r)
  {
    rdr = r;
    current = NULL;
  }
	
  virtual ~Parser() {}

  /**
   * Avanza un lexema
   **/  
  virtual Lexeme* advance()
  {
    Lexeme* tmp = current;
    current = rdr->nextLexeme();
    return tmp;
  }

  /**
   * Checa si es el lexema que buscas y avanza un lugar
   * avienta una exception si ocurre un error
   **/
  virtual Lexeme* match(int type) throw(CMDException)
  {
    if(check(type))
      return advance();
    else
      throw CMDException(type, current->data);
  }

  /**
   * Cheque que el lexema en el que te encuentras
   * sea del tipo especificado
   **/
  virtual bool check(int type)
  {
    if (current) return current->type == type;
    else return current;
  }

  /**
   * Lee una línea de comandos ( ;)
   **/
  virtual int readLine()
  {
    int status = NXT;
    int esperar = 0;
    int pid;
    advance();
    if(current) {
      try {
	if (check(EXIT)) {
	  advance();
	  status = END;
	}
	else if (check(CD)) {
	  advance();
	  Lexeme* dir = match(CMD);
	  if (chdir(dir->data) == -1) cerr << "error\n";
	}
	else {
	  esperar = 1;
	  Comando* cmd = leeComandos(-1,-1);
	  pid = cmd->eval();
	  // si llego al final y hay &: no esperes
	  if (check(AND)) {
	    advance();
	    esperar = 0;
	  }
	}
	if (esperar == 1)
	  while(wait(NULL)!=pid);
      }
      catch (CMDException e) {
	cerr << e.getMessage() << endl;
	rdr->flush();
	return NXT;
      }
    }
    rdr->flush();
    return status;
  }

  virtual Comando* leeComandos(int in, int out)
  {
    Comando* cmd1 = leeUnComando();
    if (in != -1) cmd1->setPipe2(in, out);
    if (check(ERR)) {
      advance();
      Lexeme* file = match(CMD);
      int fildes = open(file->data, O_WRONLY|O_CREAT|O_APPEND, 0666);
      if(fildes == -1) { cerr << "bad file name" << endl; exit(1); }
      cmd1->setError(fildes);
    }
    if (check(OUT)) {
      advance();
      Lexeme* file = match(CMD);
      int fildes = open(file->data, O_WRONLY|O_CREAT|O_TRUNC, 0666);
      if(fildes == -1) { cerr << "bad file name" << endl; exit(1); }
      cmd1->setOutput(fildes);
    }
    if (check(APP)) {
      advance();
      Lexeme* file = match(CMD);
      int fildes = open(file->data, O_WRONLY|O_CREAT|O_APPEND, 0666);
      if(fildes == -1) { cerr << "bad file name" << endl; exit(1); }
      cmd1->setOutput(fildes);
    }
    if (check(IN)) {
      advance();
      Lexeme* file = match(CMD);
      int fildes = open(file->data, O_RDONLY|O_CREAT, 0666);
      if(fildes == -1) { cerr << "bad file name" << endl; exit(1); }
      cmd1->setInput(fildes);
    }
    if (check(PIPE)) {
      advance();
      int pipes[2];
      pipe(pipes);
      cmd1->setPipe1(pipes[0],pipes[1]);
      cmd1->setNext(leeComandos(pipes[0],pipes[1]));
    }
    // return cmd1->eval();
    return cmd1;
  }

  virtual Comando* leeUnComando() throw(CMDException)
  {
    Comando* cmd = new Comando( match(CMD) );
    while( check(CMD) )
      cmd->addArg( advance() );
    return cmd;
  }
};

#endif // PARSER_H
