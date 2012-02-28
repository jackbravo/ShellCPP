#include "Parser.cpp"
#include <iostream>
#include <unistd.h>
#include <signal.h>
using namespace std;

void catchINT(int);
void catchQUIT(int);
void catchTSTP(int);

int main(void)
{
  signal(SIGINT, catchINT);
  signal(SIGQUIT, catchQUIT);
  signal(SIGTSTP, catchTSTP);
  cout << endl;
  cout << "********************" << endl;
  cout << "*                  *" << endl;
  cout << "*    mini-Shell    *" << endl;
  cout << "*      V. 0.1      *" << endl;
  cout << "*                  *" << endl;
  cout << "********************" << endl;
  cout << endl;
  cout << endl;

  int status;
  char path[256];
  Reader* readObj = new Reader();
  Parser* parsObj = new Parser(readObj);

  cout << getcwd(path,256) << " % ";
  while( parsObj->readLine()!=END && feof(stdin)==0 )
    {
      cout << getcwd(path,256) << " % ";
    }
  if(feof(stdin)!=0) cout << endl;
  cout << "ta-luego..." << endl;
  exit(0);
}

void catchINT(int i)
{
  signal(SIGINT, catchINT);
  cout << "\nPresionaste Ctr-C... no paso nada :)\n";
  cout << "para salir hay varias opciones:\n";
  cout << "1. escribe \"exit\".\n";
  cout << "2. presiona Ctr-\\ (manda la señal de Quit)\n";
  cout << "3. presiona Ctr-D (manda el caracter de EOF)\n";
  cout << "gracias\n";
}

void catchTSTP(int i)
{
  signal(SIGTSTP, catchTSTP);
  cout << "\nNo se puede suspender este proceso\n";
}

void catchQUIT(int i)
{
  cout << "ta-luego..." << endl;
  exit(0);
}
