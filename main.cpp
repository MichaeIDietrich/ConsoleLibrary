#include "ConsoleLibrary/LinuxConsole.h"

int main(int argc, char** argv)
{
  Console* cons = new Console("Title", 20, 50);
  
  //cons->printText(5, 5, "Testgfrgdf-Text at 5,5");
  cons->setTile(5,5,'o');
  cons->setTile(6,5,'o');
  cons->setTile(7,5,'o');
  cons->setTile(8,5,'o');
  cons->setTile(8,6,'o');
  cons->setTile(8,7,'o');
  cons->setTile(8,8,'o');
  cons->setTile(8,9,'o');
  
  getch();
  
  delete cons;
  
  return 0;
}