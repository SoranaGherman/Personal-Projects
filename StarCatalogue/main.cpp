#include "AstronomerWindow.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::string filePathA = "astronomers.txt";
    std::string filePathS = "star.txt";

    std::ifstream finA(filePathA);

    Repository<Astronomer>* aR = new Repository<Astronomer>{filePathA};
    Repository<Star>* sR = new Repository<Star>{filePathS};
    Service* serv = new Service{ aR, sR };
    StarModel* model = new StarModel{serv};
    Astronomer as;

    while (finA >> as)
    {
        AstronomerWindow* window = new AstronomerWindow{model, serv, as};
        window->setWindowTitle(QString::fromStdString(as.getName()));
        window->show();
    }

    return a.exec();
}
