#include "StarModel.h"

StarModel::StarModel(Service* serv) :
	serv{ serv }
{
}

int StarModel::rowCount(const QModelIndex& parent) const
{
	return this->serv->getStarsRepo();
}

int StarModel::columnCount(const QModelIndex& parent) const
{
	return 4;
}

QVariant StarModel::data(const QModelIndex& index, int role) const
{
    int row = index.row();
    int column = index.column();
    auto star = this->serv->getAllStars()[row];

    if (role == Qt::DisplayRole) {
        switch (column) {
        case 0: return QString::fromStdString(star.getName());
        case 1: return QString::fromStdString(std::to_string(star.getRA()));
        case 2: return QString::fromStdString(std::to_string(star.getDec()));
        case 3: return QString::fromStdString(std::to_string(star.getDiameter()));
        default: break;
        }
    }

    return QVariant();
}

QVariant StarModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
        case 0: return QString{ "Name" };
        case 1: return QString{ "RA" };
        case 2: return QString{ "Dec" };
        case 3: return QString{ "Diameter" };
        default: break;
        }
    }

    return QVariant();
}

void StarModel::addStar(Star& s)
{
    int n = this->serv->getStarsRepo();

    this->beginInsertRows(QModelIndex{}, n, n);

    this->serv->addStar(s);

    this->endInsertRows();
}


