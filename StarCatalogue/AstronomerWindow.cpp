#include "AstronomerWindow.h"
#include "qmessagebox.h"

#include <string>

AstronomerWindow::AstronomerWindow(StarModel* model, Service* serv, Astronomer a, QWidget *parent)
	:model{ model }, serv{ serv }, a{a}, QWidget(parent)
{
	ui.setupUi(this);
	ui.tableView->setModel(model);
	this->connectSignalsAndSlots();
}


void AstronomerWindow::connectSignalsAndSlots()
{
	QObject::connect(this->ui.AddpushButton, &QPushButton::clicked, this, &AstronomerWindow::addButtonHandler);
	QObject::connect(this->ui.VPushButton, &QPushButton::clicked, this, &AstronomerWindow::viewButtonHandler);
	QObject::connect(this->ui.checkBox, &QCheckBox::clicked, this, &AstronomerWindow::checkButtonHandler);
	QObject::connect(this->ui.SearchLineEdit, &QLineEdit::textChanged, this, &AstronomerWindow::searchHandler);

}

void AstronomerWindow::addButtonHandler()
{
	std::string name = this->ui.NameLineEdit->text().toStdString();
	if (name.empty())
	{
		QMessageBox msg;
		msg.setText("Invalid name!");
		msg.exec();
		return;
	}

	std::vector<Star> data = this->serv->getAllStars();
	for (auto obj : data)
		if(obj.getName() == name)
		{
			QMessageBox msg;
			msg.setText("A star with the same name already exists!");
			msg.exec();
			return;
		}
	int RA = stoi(this->ui.RALineEdit->text().toStdString());
	int Dec = stoi(this->ui.DecLineEdit->text().toStdString());
	int diameter = stoi(this->ui.DiamLineEdit->text().toStdString());

	
	if (diameter <= 0)
	{
		QMessageBox msg;
		msg.setText("Invalid diameter!");
		msg.exec();
		return;
	}

	Star s(name, a.getConstellation(), RA, Dec, diameter);
	this->model->addStar(s);
}

void AstronomerWindow::checkButtonHandler()
{
	if (ui.checkBox->isChecked())
	{
		std::vector<Star> v = this->serv->getAllStars();
		for (int i = 0; i < v.size(); i++)
			if (v[i].getConstellation() != a.getConstellation())
				ui.tableView->hideRow(i);
		return;
	}

	std::vector<Star> v = this->serv->getAllStars();
	for (int i = 0; i < v.size(); i++)
		ui.tableView->showRow(i);

}

void AstronomerWindow::viewButtonHandler()
{
	int index = this->ui.tableView->currentIndex().row();

	if (index != -1)
	{
		Star s = this->serv->getAllStars()[index];
		QMessageBox msg;
		QString string = QString::fromStdString(s.getName() + " " + s.getConstellation());
		msg.setText(string);
		msg.exec();

	}

}

void AstronomerWindow::searchHandler()
{
	this->ui.listWidget->clear();
	std::string name = this->ui.SearchLineEdit->text().toStdString();
	std::vector<Star> allData = this->serv->getAllStars();

	for (auto obj : allData)
		if (obj.getName().find(name) != std::string::npos)
			ui.listWidget->addItem(QString::fromStdString(obj.getName() + " " + obj.getConstellation() + " " + std::to_string(obj.getRA()) +
			" " + std::to_string(obj.getDec()) + " " + std::to_string(obj.getDiameter())));

}


