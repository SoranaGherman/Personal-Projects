#include "DriverWindow.h"
#include <QtWidgets/QApplication>
#include "DriverWindow.h"
#include "MapWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::string filePathD = "drivers.txt";
    std::string filePathR = "reports.txt";

    Repository<Driver>* dR = new Repository<Driver>{filePathD};
    Repository<Road>* rR = new Repository<Road>{filePathR};
    Service* serv = new Service{rR, dR};

    std::ifstream finD(filePathD);
    Driver d;
    while (finD >> d)
    {
        DriverWindow* window = new DriverWindow{serv, d};
        window->setWindowTitle(QString::fromStdString(d.getName() + "     " + d.getLocation() + "   " + std::to_string(d.getScore())+
        "   " + d.getStatus()));
        if (d.getStatus() == "baby")
            window->setStyleSheet("background-color: green");
        else if (d.getStatus() == "grown-up")
            window->setStyleSheet("background-color: yellow");
        else
            if (d.getStatus() == "knight")
                window->setStyleSheet("background-color: pink");
        serv->addObserver(window);
        window->show();
    }
   
    MapWindow* map = new MapWindow{serv};
    serv->addObserver(map);
    map->show();

    return a.exec();
}
