#pragma once

#include <QWidget>
#include "ui_DriverWindow.h"
#include "Service.h"

class DriverWindow : public QWidget, public Observer
{
	Q_OBJECT

public:
	DriverWindow(Service* serv, Driver d, QWidget *parent = Q_NULLPTR);
	~DriverWindow() = default;

	void connectSignalsAndSlots();
	void populateList();
	void update() override;

	void addButtonHandler();
	void selectionHandler();
	void vButtonHandler();

private:
	Ui::DriverWindow ui;
	Service* serv;
	Driver d;
};
