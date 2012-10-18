#include "ConsoleLibrary/LinuxConsole.h"

int main(int argc, char** argv)
{
  Console* cons = new Console("Title", 20, 50);
  
  cons->printText(5, 5, "Test-Text at 5,5");
  
  getch();
  
  delete cons;
  
  return 0;
}