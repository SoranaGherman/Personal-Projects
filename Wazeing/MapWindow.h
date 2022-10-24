#pragma once

#include <QWidget>
#include "ui_MapWindow.h"
#include "Observer.h"
#include "Service.h"

class MapWindow : public QWidget, public Observer
{
	Q_OBJECT

public:
	MapWindow(Service* s, QWidget *parent = Q_NULLPTR);
	~MapWindow();
	void update();
	void populateList();

private:
	Ui::MapWindow ui;
	Service* s;
};
