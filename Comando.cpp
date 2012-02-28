#ifndef COMANDO_H
#define COMANDO_H
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include "Lexeme.cpp"
using namespace std;

#define RD 7
#define WR 6

class Comando {
public:
  Comando(Lexeme* c) : cmd(c) {
    nxt = NULL;
    init_args(); // inicializa la variable args
    size = 1;
    args[0] = strdup(c->data);
    args[1] = NULL;
    pipe1 = NULL;
    pipe2 = NULL;
    output = -1;
    input =  -1;
    error =  -1;
  }

  ~Comando() {
    delete cmd;
    delete []args;
  }

  virtual char* name() {
    return cmd->data;
  }

  virtual void addArg(Lexeme* a)
  {
    args[size] = strdup(a->data);
    args[++size] = NULL;
    delete a;
  }

  virtual int eval()
  {
    int pid = -1;

    pid = fork();
    if ( pid < 0 )
      {
	cerr << "fork" << endl;
	exit(1);
      }
    if ( pid == 0)  // codigo del hijo
      {
	if (input != -1) {
	  dup2(input, 0); close(input);
	}
	if (output != -1) { 
	  dup2(output, 1); close(output);
	}
	if (error != -1) {
	  dup2(error, 2); close(error);
	}
	if (pipe1) {
	  close(pipe1[0]);
	  dup2(pipe1[1],1); close(pipe1[1]);
	}
	if (pipe2) {
	  close(pipe2[1]);
	  dup2(pipe2[0],0); close(pipe2[0]);
	}

	execvp(cmd->data,args);
	cerr << "Could not execvp" << endl;
	_exit(1);
      }
    // codigo del padre
    if(pipe1) close(pipe1[1]);
    if(pipe2) close(pipe2[0]);
    if(nxt) return nxt->eval();
    return pid;
  }

  virtual void setOutput(int o) {output = o;}
  virtual void setInput(int i) {input = i;}
  virtual void setError(int e) {error = e;}
  virtual void setNext(Comando* c) {nxt = c;}

  virtual void setPipe1(int in, int out)
  {
    pipe1 = new int[2];
    pipe1[0] = in;
    pipe1[1] = out;
  }

  virtual void setPipe2(int in, int out)
  {
    pipe2 = new int[2];
    pipe2[0] = in;
    pipe2[1] = out;
  }

private:
  Lexeme* cmd;
  Comando* nxt;
  char** args;
  int size;
  int output;
  int input;
  int error;
  int* pipe1;
  int* pipe2;

  void init_args()
  {
    // Alocation of memory for an array 
    if((args = (char **) malloc(5 * sizeof(char *))) == NULL) {
      cerr << "Couldn't allocate memory\n";
      exit(1);
    }
  }
};
#endif // COMANDO_H
