****************************************
*                                      *
*                                      *
*             Mini-Shell               *
*                 1.0                  *
*                                      *
*                                      *
****************************************

Campus: GDA
Fecha:  Octubre 2004
Equipo: The Incredibles!
Integrantes:
  - German Villalpando	668145
  - Faustino Navarro	667190
  - Victor Torres	990096
  - Joaquin Bravo	990055

Este es el instructivo de nuestro proyecto.
El proyecto está desarrollado en C++.
Cuenta con 6 archivos:

driver.cpp
Donde se encuentra el método main.

Lexeme.cpp
Que guarda la información de cada palabra que se lee.

Reader.cpp
Se encarga de leer del stdin y separar cada línea en Lexemes.

Comando.cpp
Guarda el nombre de un comando, sus descriptores de archivo,
sus argumentos y (si existe) una referencia al comando siguiente.
Cada comando se ejecuta a sí mismo mediante un fork, hace la
redirección del stdin y stdout y llama a execvp.

Parser.cpp
Toma los lexemes del Reader y los separa en comandos y caracteres
especiales para después ejecutar los comandos.

CMDException.cpp
Si existe un error en el parseo, este objeto contiene información
que ayude al usuario.


--------------------
Instrucciones de uso
--------------------
Para compilar se utiliza el comando g++ y se llama sobre el 
archivo que contiene al main así:
> g++ driver.cpp

La salida por default es el archivo a.out
Si se desea otro nombre el comando es el siguiente:
> g++ driver.cpp -o shell.exe

para correr simplemente teclee:
> ./shell.exe

El shell acepta comandos con hasta 5 argumentos.
Acepta redirección del stdin y stdout
- "cmd > archivo" redirecciona la salida a archivo
- "cmd < archivo" redirecciona la entrada a archivo
- "cmd >> archivo" redirecciona la salida a archivo, pero
  a diferencia de ">" en vez de sobreescribirlo, concatena
  la salida al final del archivo.

El shell también permite el uso de pipes ilimitados.
Por lo que:
> ls -l | sort -r | wc
es perfectamente válido.

También permite correr programas en el background.
> emacs
se queda esperando a que termines de editar.
> emacs &
corre el proceso fuera del shell.

El único comando implementado dentro del shell es "cd"
para cambiar de directorio mediante el system call "chdir".

Para salir hay 3 opciones:
1. escribir "exit"
2. presionar ctrl + \ (que manda la señal de quit)
3. presionar ctrl + D (que manda el caracter de EOF)

Ctrl-Z y Ctrl-C son atrapados y no terminan el programa.
