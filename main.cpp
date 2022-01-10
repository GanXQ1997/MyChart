#include "MyChart.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyChart w;
    w.show();
    return a.exec();
}
