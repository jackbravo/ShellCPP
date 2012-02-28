#ifndef CMDEXCEPTION_H
#define CMDEXCEPTION_H
#include <cstring>
using namespace std;

class CMDException {
  int type;
  char* data;
  string message;

  string generarMsg()
  {
    string str1 = "Error: se esperaba ";
    string str2 = getTipo();
    string str3 = ". Se encontro: ";
    string str4 = data;
    return str1 + str2 + str3 + str4;
  }

  string getTipo()
  {
    string t;
    switch (type) {
    case AND : t = "&"; break;
    case ERR : t = ">>"; break;
    case OUT : t = ">"; break;
    case IN  : t = "<"; break;
    case PIPE: t = "|"; break;
    case EXIT: t = "exit"; break;
    case CMD : t = "string(comando)"; break;
    }
    return t;
  }

public:
  CMDException(int t, char* d) : type(t), data(d) {
    message = generarMsg();
  }

  ~CMDException() {}

  int getType() {return type;}
  char* getData() {return data;}
  string getMessage() {return message;}
};
#endif // CMDEXCEPTION_H
