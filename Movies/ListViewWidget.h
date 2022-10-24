#pragma once

#include <QWidget>
#include "ui_ListViewWidget.h"
#include "WatchListModel.h"

class ListViewWidget : public QWidget
{
	Q_OBJECT

public:
	ListViewWidget(EventTable* model, QWidget *parent = Q_NULLPTR);
	~ListViewWidget();

private:
	Ui::ListViewWidget ui;
};
