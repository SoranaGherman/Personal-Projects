#include "ListViewWidget.h"
#include <QSortFilterProxyModel>

ListViewWidget::ListViewWidget(EventTable* model, QWidget *parent)
	:QWidget(parent)
{
	ui.setupUi(this);

	//ui.tableView->setModel(model);
}

ListViewWidget::~ListViewWidget()
{

}
