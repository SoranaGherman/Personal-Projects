#pragma once

#include <QWidget>
#include "ui_AstronomerWindow.h"
#include "Service.h"
#include "StarModel.h"

class AstronomerWindow : public QWidget
{
	Q_OBJECT

public:
	AstronomerWindow(StarModel* model, Service* serv, Astronomer a, QWidget *parent = Q_NULLPTR);
	~AstronomerWindow() = default;

	void connectSignalsAndSlots();
	void addButtonHandler();
	void checkButtonHandler();
	void viewButtonHandler();
	void searchHandler();

private:
	Ui::AstronomerWindow ui;
	StarModel* model;
	Service* serv;
	Astronomer a;
};
