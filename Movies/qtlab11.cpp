#include "qtlab11.h"
#include <string>
#include "MovieValidator.h"
#include <QtWidgets/QMessageBox>

qtlab11::~qtlab11()
{
}

void qtlab11::initGui()
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    QFont title_font = this->title_widget->font();
    this->title_widget->setText("Welcome to movie department!");
    title_font.setItalic(true);
    title_font.setPointSize(14);
    title_font.setStyleHint(QFont::System);
    this->title_widget->setFont(title_font);

    layout->addWidget(this->title_widget);
    this->admin_button->setText("Admin mode");
    layout->addWidget(this->admin_button);
    this->user_button->setText("User mode");
    layout->addWidget(this->user_button);
    this->setLayout(layout);
    this->setStyleSheet("background - color:#FDEADA");

    this->admin_button->setStyleSheet("*{color: qlineargradient(spread:pad,x1:0 y1:0, x2:1 y2:0, spot:0 purple, stop:1 grey);""background:qlineargradient(x1:0 y1:0, x2:1 y2:0, stop:0 pink, stop:1 magenta);}");
    this->user_button->setStyleSheet("*{color: qlineargradient(spread:pad,x1:0 y1:0, x2:1 y2:0, spot:0 purple, stop:1 purple);""background:qlineargradient(x1:0 y1:0, x2:1 y2:0, stop:0 white, stop:1 purple);}");
}

void qtlab11::showAdmin()
{
    QWidget* admin = new AdminGUI(NULL, this->serv);
    admin->showNormal();
}

void qtlab11::showUser()
{
    QWidget* user= new UserGUI(NULL, this->serv, this->user_sv);
    user->showNormal();
}

void qtlab11::connectSignalAndSlots()
{
    QObject::connect(this->admin_button, &QPushButton::clicked, this, &qtlab11::showAdmin);
    QObject::connect(this->user_button, &QPushButton::clicked, this, &qtlab11::showUser);
}

qtlab11::qtlab11(AdminService* sv, UserService* us_sv)
{
    this->serv = sv;
    this->user_sv = us_sv;
    this->title_widget = new QLabel(this);
    this->admin_button = new QPushButton(this);
    this->user_button = new QPushButton(this);
    this->initGui();
    this->connectSignalAndSlots();
    //ui.setupUi(this);
}

void AdminGUI::initAdminGui()
{
    auto* layout = new QVBoxLayout(this);
    QFont title_font = this->title_widget->font();
    this->title_widget->setText("ADMIN MODE");
    title_font.setItalic(true);
    title_font.setPointSize(14);
    title_font.setStyleHint(QFont::System);
    this->title_widget->setFont(title_font);
    layout->addWidget(this->title_widget);
    layout->addWidget(this->movie_list_widget);

    QFormLayout* movie_details_layout = new QFormLayout{};
    movie_details_layout->addRow("Title", this->titleLineEdit);
    movie_details_layout->addRow("Genre", this->genreLineEdit);
    movie_details_layout->addRow("Year", this->yearLineEdit);
    movie_details_layout->addRow("Likes", this->likesLineEdit);
    movie_details_layout->addRow("Link", this->linkLineEdit);
    layout->addLayout(movie_details_layout);

    auto* buttons_layout = new QGridLayout{};
    buttons_layout->addWidget(this->addButton, 0, 0);
    buttons_layout->addWidget(this->deleteButton, 0, 1);
    buttons_layout->addWidget(this->updateButton, 0, 2);
    buttons_layout->addWidget(this->undoButton, 1, 0);
    buttons_layout->addWidget(this->redoButton, 1, 2);
    layout->addLayout(buttons_layout);
}

void AdminGUI::populateList()
{
    this->movie_list_widget->clear();
    std::vector<Movie> allMovies = this->serv->getAll();
    for (auto& m : allMovies)
    {
        QString stringItem = QString::fromStdString(
            m.GetTitle() + "   " +
            m.GetGenre() + "   " +
            std::to_string(m.GetYear()) + "   " +
            std::to_string(m.GetLikes()) + "   " +
            m.GetTrailer());

        this->movie_list_widget->addItem(stringItem);
    }
}

void AdminGUI::connectSignalAndSlots()
{
    QObject::connect(this->addButton, &QPushButton::clicked, this, &AdminGUI::guiAddMovieHandler);
    QObject::connect(this->deleteButton, &QPushButton::clicked, this, &AdminGUI::guiDeleteMovieHandler);
    QObject::connect(this->updateButton, &QPushButton::clicked, this, &AdminGUI::guiUpdateMovieHandler);
  
    QObject::connect(this, &AdminGUI::updateMoviesSignal, this, &AdminGUI::populateList);
    QObject::connect(this, &AdminGUI::addMovieSignal, this, &AdminGUI::addMovie);
    QObject::connect(this, &AdminGUI::removeMovieSignal, this, &AdminGUI::removeMovie);
    QObject::connect(this, &AdminGUI::updateMovieSignal, this, &AdminGUI::updateMovie);

    QObject::connect(this->undoButton, &QPushButton::clicked, this, &AdminGUI::undo);
    QObject::connect(this->redoButton, &QPushButton::clicked, this, &AdminGUI::redo);
}

void AdminGUI::addMovie(std::string title, std::string genre, size_t year, size_t likes, std::string link)
{
    std::string text = "Movie added succesfully!";

    try
    {
        this->serv->AddMovie(title, genre, year, likes, link);
        emit updateMoviesSignal();

    }
    catch (ValidationException error)
    {
        text = error.getMessage();
    }

    QMessageBox msgBox;
    msgBox.setText(text.c_str());
    msgBox.exec();
}

void  AdminGUI::removeMovie(std::string title)
{
    std::string text = "Movie removed succesfully!";

    try
    {
        this->serv->RemoveMovie(title);
        emit updateMoviesSignal();

    }
    catch (ValidationException error)
    {
        text = error.getMessage();

    }

    QMessageBox msgBox;
    msgBox.setText(text.c_str());
    msgBox.exec();
}

void AdminGUI::updateMovie(std::string t, std::string title, std::string genre, size_t year, size_t likes, std::string link)
{
    std::string text = "Movie updated successfully!";

    try
    {
        if (!title.empty()) this->serv->UpdateMovieTitle(t, title);
        if (!genre.empty()) this->serv->UpdateMovieGenre(t, genre);
        if (year) this->serv->UpdateMovieYear(t, year);
        if (likes) this->serv->UpdateMovieLikes(t, likes);
        if(!link.empty()) this->serv->UpdateMovieTrailer(t, link);

        emit updateMoviesSignal();
    }
    catch (ValidationException error)
    {
        text = error.getMessage();
    }

    QMessageBox msgBox;
    msgBox.setText(text.c_str());
    msgBox.exec();
}

void AdminGUI::guiAddMovieHandler()
{
    int year = atoi(this->yearLineEdit->text().toStdString().c_str());
    int likes = atoi(this->likesLineEdit->text().toStdString().c_str());
    std::string title = this->titleLineEdit->text().toStdString();
    std::string genre = this->genreLineEdit->text().toStdString();
    std::string link = this->linkLineEdit->text().toStdString();


    this->titleLineEdit->clear();
    this->genreLineEdit->clear();
    this->yearLineEdit->clear();
    this->likesLineEdit->clear();
    this->linkLineEdit->clear();

    emit addMovieSignal(title, genre, year, likes, link);
}

void AdminGUI::guiDeleteMovieHandler()
{
    int id = this->getSelectedIndex();
    Movie mov;

    if (id != -1)
    {
        mov = this->serv->getAll()[id];

        std::string title = mov.GetTitle();

        emit removeMovieSignal(title);
    }
    
    else {
        QMessageBox mess;
        mess.setText("Please select the movie you want to remove!");
        mess.exec();
    }
    
}

void AdminGUI::guiUpdateMovieHandler()
{

    int id = this->getSelectedIndex();
    Movie mov;

    if (id != -1)
    {
        mov = this->serv->getAll()[id];

        std::string t = mov.GetTitle();

        std::string title = this->titleLineEdit->text().toStdString();
        std::string genre = this->genreLineEdit->text().toStdString();
        int year = atoi(this->yearLineEdit->text().toStdString().c_str());
        int likes = atoi(this->likesLineEdit->text().toStdString().c_str());
        std::string trailer = this->linkLineEdit->text().toStdString();

        emit updateMovieSignal(t, title, genre, year, likes, trailer);
    }
    else {
    QMessageBox mess;
    mess.setText("Please select the movie you want to remove!");
    mess.exec();
    }
}

void AdminGUI::displayChart()
{
}

int AdminGUI::getSelectedIndex() const
{
    if (this->movie_list_widget->count() == 0)
    {
        return -1;
    }

    QModelIndexList  index = this->movie_list_widget->selectionModel()->selectedRows();

    if (index.size() == 0)
    {
        this->titleLineEdit->clear();
        this->genreLineEdit->clear();
        this->yearLineEdit->clear();
        this->likesLineEdit->clear();
        this->linkLineEdit->clear();

        return -1;
    }

    return index.at(0).row();
}

void AdminGUI::undo()
{
    std::string text = "Undo done successfully!";

    try
    {
        this->serv->undo();
        emit updateMoviesSignal();
    }
    catch (const std::exception&)
    {
        text = "No more undos!";
    }

    QMessageBox mess;
    mess.setText(QString::fromStdString(text));
    mess.exec();
}

void AdminGUI::redo()
{
    std::string text = "Redo done successfully!";

    try
    {
        this->serv->redo();
        emit updateMoviesSignal();
    }
    catch (const std::exception&)
    {
        text = "No more redos!";
    }

    QMessageBox mess;
    mess.setText(QString::fromStdString(text));
    mess.exec();
}

AdminGUI::AdminGUI(QWidget* parent, AdminService* serv)
{
    setParent(parent);
    this->serv = serv;
    this->title_widget = new QLabel(this);
    this->movie_list_widget = new QListWidget();
    this->titleLineEdit = new QLineEdit{};
    this->genreLineEdit = new QLineEdit{};
    this->yearLineEdit = new QLineEdit{};
    this->likesLineEdit = new QLineEdit{};
    this->linkLineEdit = new QLineEdit{};
    this->addButton = new QPushButton("Add");
    this->deleteButton = new QPushButton("Delete");
    this->updateButton = new QPushButton("Update");
    this->undoButton = new QPushButton("UNDO");
    this->redoButton = new QPushButton("REDO");
    this->chartButton = new QPushButton("Display chart");
    this->initAdminGui();
    this->connectSignalAndSlots();
    this->populateList();
}

AdminGUI::~AdminGUI()
{
}

UserGUI::UserGUI(QWidget* parent, AdminService* serv, UserService* us_sv)
{
    setParent(parent);
    this->serv = serv;
    this->user_sv = us_sv;
    this->title_widget = new QLabel(this);
    this->playlist_list_widget = new QListWidget{};
    this->movie_list_widget = new QListWidget();
    this->filter_movie_list_widget = new QListWidget();
    this->titleLineEdit = new QLineEdit{};
    this->genreLineEdit = new QLineEdit{};
    this->yearLineEdit = new QLineEdit{};
    this->likesLineEdit = new QLineEdit{};
    this->linkLineEdit = new QLineEdit{};
    this->filterLineEdit = new QLineEdit{};
    this->titleFilterLineEdit = new QLineEdit{};
    this->genreFilterLineEdit = new QLineEdit{};
    this->addButton = new QPushButton("Add to the watchlist list");
    this->removeButton = new QPushButton("Remove from the watchlist list");
    this->filterButton = new QPushButton("Filter the movies");
    this->nextButton = new QPushButton("Next movie");
    this->openListButton = new QPushButton("Open file");
    this->csvButton = new QRadioButton("CSV");
    this->htmlButton = new QRadioButton("HTML");
    this->repoTypeSelected = false;
    this->filtered = false;
    this->index = -1;

    this->initUserGui();
    this->populateMovieList();
    this->connectingSignalsAndSlots();
    this->nextSignal();
}

UserGUI::~UserGUI()
{
}

void UserGUI::populateMovieList()
{
    this->movie_list_widget->clear();
    std::vector<Movie> allMovies = this->serv->getAll();
    for (auto& m : allMovies)
        this->movie_list_widget->addItem(QString::fromStdString(m.GetTitle()));
}

void UserGUI::populatePlaylistList()
{
    this->playlist_list_widget->clear();
    std::vector<Movie> allMovies = this->user_sv->GetMovieList();
    allMovies.erase(allMovies.begin());
    for (auto& m : allMovies)
    {
        QString stringItem = QString::fromStdString(
            m.GetTitle() + "   " +
            m.GetGenre() + "   " +
            std::to_string(m.GetYear()) + "   " +
            std::to_string(m.GetLikes()) + "   " +
            m.GetTrailer());

        this->playlist_list_widget->addItem(stringItem);
    }
    
}

void UserGUI::populateFilterList()
{
    this->playlist_list_widget->clear();
    std::vector<Movie> allMovies = this->user_sv->getCurrentList();
    allMovies.erase(allMovies.begin());
    for (auto& m : allMovies)
    {
        QString stringItem = QString::fromStdString(
            m.GetTitle() + "   " +
            m.GetGenre() + "   " +
            std::to_string(m.GetYear()) + "   " +
            std::to_string(m.GetLikes()) + "   " +
            m.GetTrailer());

        this->filter_movie_list_widget->addItem(stringItem);
    }
}

void UserGUI::connectingSignalsAndSlots()
{
    QObject::connect(this->addButton, &QPushButton::clicked, this, &UserGUI::AddMovieHandler);
    QObject::connect(this->removeButton, &QPushButton::clicked, this, &UserGUI::RemoveMovieHandler);
    QObject::connect(this->nextButton, &QPushButton::clicked, this, &UserGUI::nextMovieHandler);
    QObject::connect(this->filterButton, &QPushButton::clicked, this, &UserGUI::guiFilterMovies);
    QObject::connect(this->openListButton, &QPushButton::clicked, this, &UserGUI::fileHandler);

    QObject::connect(this, &UserGUI::updateWatchListSignal, this, &UserGUI::populatePlaylistList);
    QObject::connect(this, &UserGUI::updateFilterListSignal, this, &UserGUI::populateFilterList);
    QObject::connect(this, &UserGUI::addMovieSignal, this, &UserGUI::addMovie);
    QObject::connect(this, &UserGUI::removeMovieSignal, this, &UserGUI::removeMovie);
    QObject::connect(this, &UserGUI::nextSignal, this, &UserGUI::nextMovie);
    QObject::connect(this, &UserGUI::filterSignal, this, &UserGUI::filterMovie);
}

void UserGUI::nextMovie()
{
    this->index++;
    this->index %= this->serv->getAll().size();
    this->updateLabels();
    std::string trailer = this->linkLineEdit->text().toStdString();
    char* arr = new char[100];
    strcpy(arr, "start ");
    strcat(arr, trailer.c_str());
    system(arr);
}

void UserGUI::addMovie(std::string title, std::string genre, size_t year, size_t likes, std::string link)
{
    std::string text = "Movie added succesfully!";

    try
    {
        this->user_sv->AddToWatchList(Movie(title, genre, year, likes, link));
        emit updateWatchListSignal();
        emit nextSignal();
      
    }
    catch (ValidationException error)
    {
        text = error.getMessage();
    }

    QMessageBox msgBox;
    msgBox.setText(text.c_str());
    msgBox.exec();

}

void UserGUI::removeMovie(std::string title)
{
    std::string text = "Movie removed succesfully!";

    try
    {
        this->user_sv->DeleteMovieWatchList(title, 200);
        emit updateWatchListSignal();

    }
    catch (ValidationException error)
    {
        text = error.getMessage();

    }

    QMessageBox msgBox;
    msgBox.setText(text.c_str());
    msgBox.exec();
}

void UserGUI::filterMovie(std::string genre)
{
    std::string text = "Please enter genre";

    if (text.size())
    {
        this->user_sv->FilterByGenre(genre);
        emit updateFilterListSignal();
    }
    else {
        QMessageBox msg;
        msg.setText(text.c_str());
        msg.exec();
    }
}

void UserGUI::initUserGui()
{
    auto* layout = new QVBoxLayout(this);
    QFont title_font = this->title_widget->font();
    this->title_widget->setText("Select the type of file you want for saving your watchlist!");
    title_font.setItalic(true);
    title_font.setPointSize(14);
    title_font.setStyleHint(QFont::System);
    this->title_widget->setFont(title_font);
    layout->addWidget(this->title_widget);

    auto* radio_buttons_layout = new QGridLayout(this);
    radio_buttons_layout->addWidget(this->csvButton, 0, 0);
    radio_buttons_layout->addWidget(this->htmlButton, 1, 0);
    radio_buttons_layout->addWidget(this->openListButton, 0, 1);
    layout->addLayout(radio_buttons_layout);

    auto* list_layout = new QGridLayout(this);
    list_layout->addWidget(this->movie_list_widget, 0, 0);
    list_layout->addWidget(this->playlist_list_widget, 1, 0);
    layout->addLayout(list_layout);

    auto* movie_details_layout = new QFormLayout{};
    movie_details_layout->addRow("Title", this->titleLineEdit);
    movie_details_layout->addRow("Genre", this->genreLineEdit);
    movie_details_layout->addRow("Year", this->yearLineEdit);
    movie_details_layout->addRow("Likes", this->likesLineEdit);
    movie_details_layout->addRow("Link", this->linkLineEdit);
    movie_details_layout->addRow(this->nextButton);
    movie_details_layout->addRow(this->addButton);
    movie_details_layout->addRow(this->removeButton);
    layout->addLayout(movie_details_layout);

    /*auto* filter_title1 = new QLabel("Filter the available movies by a substring");
    QFont filter_font1 = filter_title1->font();
    filter_font1.setItalic(true);
    filter_font1.setPointSize(14);
    filter_font1.setStyleHint(QFont::System);
    layout->addWidget(filter_title1);*/

    auto* list_filtered_layout = new QGridLayout(this);
    list_filtered_layout->addWidget(this->filter_movie_list_widget, 0, 0);
    layout->addLayout(list_filtered_layout);

    auto* filter_title = new QLabel("Filter the available movies by genre");
    QFont filter_font = filter_title->font();
    filter_font.setItalic(true);
    filter_font.setPointSize(14);
    filter_font.setStyleHint(QFont::System);
    layout->addWidget(filter_title);

    auto* movie_filter_layout = new QFormLayout{};
    movie_details_layout->addRow(this->filterLineEdit);
    movie_details_layout->addRow(this->filterButton);
    layout->addLayout(movie_filter_layout);
    

   /*auto* filter_details_layout = new QFormLayout{};
    filter_details_layout->addRow("Title", this->titleFilterLineEdit);
    filter_details_layout->addRow("Genre", this->genreFilterLineEdit);
    filter_details_layout->addRow(this->filterButton);
    layout->addLayout(filter_details_layout);*/
}

int UserGUI::getSelectedIndexMovies() const
{
    if (this->movie_list_widget->count() == 0)
    {
        return -1;
    }

    QModelIndexList  index = this->movie_list_widget->selectionModel()->selectedRows();

    if (index.size() == 0)
    {
        this->titleLineEdit->clear();
        this->genreLineEdit->clear();
        this->yearLineEdit->clear();
        this->likesLineEdit->clear();
        this->linkLineEdit->clear();

        return -1;
    }

    return index.at(0).row();
}

int UserGUI::getSelectedIndexPlaylist() const
{
    if (this->playlist_list_widget->count() == 0)
    {
        return -1;
    }

    QModelIndexList  index = this->playlist_list_widget->selectionModel()->selectedRows();

    if (index.size() == 0)
    {
        this->titleLineEdit->clear();
        this->genreLineEdit->clear();
        this->yearLineEdit->clear();
        this->likesLineEdit->clear();
        this->linkLineEdit->clear();

        return -1;
    }

    return index.at(0).row();
}

void UserGUI::AddMovieHandler()
{
    int year = atoi(this->yearLineEdit->text().toStdString().c_str());
    int likes = atoi(this->likesLineEdit->text().toStdString().c_str());
    std::string title = this->titleLineEdit->text().toStdString();
    std::string genre = this->genreLineEdit->text().toStdString();
    std::string link = this->linkLineEdit->text().toStdString();

    emit addMovieSignal(title, genre, year, likes, link);
}

void UserGUI::RemoveMovieHandler()
{
    int id = this->getSelectedIndexPlaylist();
    Movie mov;

    if (id != -1)
    {
        mov = this->user_sv->GetMovieList()[id];

        std::string title = mov.GetTitle();

        emit removeMovieSignal(title);
    }

    else {
        QMessageBox mess;
        mess.setText("Please select the movie you want to remove!");
        mess.exec();
    }
}

void UserGUI::nextMovieHandler()
{
    emit nextSignal();
}

void UserGUI::guiFilterMovies()
{
    std::string genre = this->filterLineEdit->text().toStdString();

    emit filterSignal(genre);
}

void UserGUI::fileHandler()
{
    if (csvButton->isChecked())
    {
        this->user_sv->SetWriteMode("CSV");
    }
    else if (htmlButton->isChecked())
    {
        this->user_sv->SetWriteMode("HTML");
    }
    if (this->user_sv->GetWriteMode() == "CSV")
    {
        this->user_sv->WriteData();

        std::string command = "notepad " + this->user_sv->GetFileName();

        system("C:");
        system("cd Users\\Sorana\\source\\repos\\a8-9\\a8-9");
        system(command.c_str());
    }
    else
    {
        this->user_sv->WriteData();

        system("C:");
        system("cd Users\\Sorana\\source\\repos\\a8-9\\a8-9");
        system(this->user_sv->GetFileName().c_str());
    }
}

void UserGUI::updateLabels()
{
    Movie m = this->serv->getAll()[index];

    this->titleLineEdit->setText(QString::fromStdString(std::string(m.GetTitle())));
    this->genreLineEdit->setText(QString::fromStdString(std::string(m.GetGenre())));
    this->yearLineEdit->setText(QString::fromStdString(std::to_string(m.GetYear())));
    this->likesLineEdit->setText(QString::fromStdString(std::to_string(m.GetLikes())));
    this->linkLineEdit->setText(QString::fromStdString(std::string(m.GetTrailer())));
}
