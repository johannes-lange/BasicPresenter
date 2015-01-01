#include "Controller.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
   QApplication app(argc, argv);
   QApplication::setApplicationName("BasicPresenter");

   Controller contr;

   int exitValue = app.exec();

   return exitValue;
}
