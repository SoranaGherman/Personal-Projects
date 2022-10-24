#include "WatchListModel.h"
#include <QFont>
#include <QBrush>

EventTable::EventTable(std::vector<Movie> r, QObject* parent) : QAbstractTableModel{ parent }, arr{ r }{}

EventTable::~EventTable()
{
}

int EventTable::rowCount(const QModelIndex& parent) const
{
	int rowCount = arr.size();
	return rowCount;
}

int EventTable::columnCount(const QModelIndex& parent) const
{
	return 5;
}

QVariant EventTable::data(const QModelIndex& index, int role) const
{

	int row = index.row();
	int column = index.column();

	// get the genes
	std::vector<Movie> events = arr;

	// Allow adding in the table
	// this is to show an empty row at the end of the table - to allow adding new genes
	if (row == events.size())
	{
		return QVariant();
	}

	// get the gene from the current row
	Movie e = events[row];
	
	if (role == Qt::DisplayRole || role == Qt::EditRole)
	{
		switch (column)
		{
		case 0:
			return QString::fromStdString(e.GetTitle());
		case 1:
			return QString::fromStdString(e.GetGenre());
		case 2:
			return QString::number(e.GetYear());
		case 3:
			return QString::number(e.GetLikes());
		case 4:
			return QString::fromStdString(e.GetTrailer());

		default:
			break;
		}
	}
	if (role == Qt::FontRole)
	{
		QFont font("Times", 15, 10, true);
		font.setItalic(false);
		return font;
	}
	if (role == Qt::BackgroundRole)
	{
		if (row % 2 == 1)
		{
			return QBrush{ QColor{0, 250, 154} };
		}
	}

	return QVariant{};

}

QVariant EventTable::headerData(int section, Qt::Orientation orientation, int role) const
{

	if (role == Qt::DisplayRole)
	{
		if (orientation == Qt::Horizontal)
		{
			switch (section)
			{
			case 0:
				return QString{ "Title" };
			case 1:
				return QString{ "Genre" };
			case 2:
				return QString{ "Year" };
			case 3:
				return QString{ "Likes" };
			case 4:
				return QString{ "Trailer" };
			default:
				break;
			}
		}
	}
	if (role == Qt::FontRole)
	{
		QFont font("Times", 15, 10, true);
		font.setBold(true);
		font.setItalic(false);
		return font;
	}

	return QVariant{};
}

bool EventTable::setData(const QModelIndex& index, const QVariant& value, int role)
{
	if (!index.isValid() || role != Qt::EditRole)
		return false;

	// set the new data to the gene
	int eventIndex = index.row();

	// get the genes
	std::vector<Movie> events = arr;

	// Allow adding in the table
	//if the index is >= number of genes => a new gene is added
	if (eventIndex == events.size())
	{
		this->endInsertRows();
		return true;
	}

	Movie& currentEvent = events[eventIndex];
	switch (index.column())
	{
	case 0:
		currentEvent.SetTitle(value.toString().toStdString());
		break;
	case 1:
		currentEvent.SetGenre(value.toString().toStdString());
		break;
	case 2:
		currentEvent.SetYear(value.toString().toInt());
		break;
	case 3:
		currentEvent.SetLikes(value.toString().toInt());
		break;
	case 4:
		currentEvent.SetTrailer(value.toString().toStdString());
	}

	// emit the dataChanged signal
	emit dataChanged(index, index);

	return true;

}

Qt::ItemFlags EventTable::flags(const QModelIndex& index) const
{
	return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}
