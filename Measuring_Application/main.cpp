#include "measuring_interface.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication the_application(argc, argv);
    Measuring_Interface the_interface;
    the_interface.show();
    return the_application.exec();
}
