#include "qtlab11.h"
#include <QtWidgets/QApplication>
#include "ListViewWidget.h"
#include "WatchListModel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FileRepository* repo = new FileRepository("file.txt");
	AdminService* adminService = new AdminService(*repo);
	UserService* userService = new UserService(*repo);
    //UserService user{*repo};
	//Console* console = new Console(*adminService, *userService);

    QTableView* view = new QTableView;
    
    std::vector<Movie> list;
    MovieList tmp;
    for (int i = 0; i < tmp.GetList().size(); i++)
        list.push_back(tmp.GetList()[i]);

    qtlab11 gui{ adminService, userService };
    
    EventTable* model = new EventTable(list);
    ListViewWidget* gui2 = new ListViewWidget{model};

    gui.show();
    view->show();
    return a.exec();
}
