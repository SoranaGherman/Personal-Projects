#pragma once

#include <QAbstractTableModel>
#include "Service.h"

class StarModel : public QAbstractTableModel
{
private:
	Service* serv;

public:
	StarModel(Service* serv);

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	void addStar(Star& s);
};