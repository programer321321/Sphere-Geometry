#include <QApplication>
#include "Sketch.h"

int main(int argc, char *argv[]) {
    QApplication program(argc, argv);
    Sketch sketch;
    return QApplication::exec();
}