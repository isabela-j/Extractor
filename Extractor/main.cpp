#include "ExtractorGUI.h"
#include <QtWidgets/QApplication>
//#include <vld.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Extractor w;
    w.show();
    return a.exec();
}
