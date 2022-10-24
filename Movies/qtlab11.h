#pragma once

#include <QtWidgets/QWidget>
#include "ui_qtlab11.h"
#include "AdministratorService.h"
#include "UserService.h"
#include <qlabel.h>
#include <qpushbutton.h>
#include <QLineEdit>
#include <QListWidget>
#include <QBoxLayout>
#include <QFormLayout>
#include <qlistwidget.h>
#include <qradiobutton.h>

class qtlab11 : public QWidget
{
    Q_OBJECT
private:
    AdminService* serv;
    UserService* user_sv;
    void initGui();
    QLabel* title_widget;
    QPushButton* admin_button;
    QPushButton* user_button;
    void showAdmin();
    void showUser();
    void connectSignalAndSlots(); 
    Ui::qtlab11Class ui;

public:
    qtlab11(AdminService* sv, UserService* us_sv);

    ~qtlab11();
};

class AdminGUI : public QWidget {
   Q_OBJECT

private:
    AdminService* serv;
    void initAdminGui();
    QLabel* title_widget;
    QListWidget* movie_list_widget;
    QLineEdit* titleLineEdit, * genreLineEdit, * yearLineEdit, * likesLineEdit, * linkLineEdit;
    QPushButton* addButton, * deleteButton, * updateButton, * chartButton, *undoButton, *redoButton;

    void populateList();
    void connectSignalAndSlots();
    void guiAddMovieHandler();
    void guiDeleteMovieHandler();
    void guiUpdateMovieHandler();
    void displayChart();
    int  getSelectedIndex() const;

    void undo();
    void redo();

    QWidget* chart_window;

public:
    AdminGUI(QWidget* parent, AdminService* serv);
    ~AdminGUI();

public:
signals: void updateMoviesSignal();
signals: void addMovieSignal(std::string title, std::string genre, size_t year, size_t likes, std::string link);
signals: void removeMovieSignal(std::string title);
signals: void updateMovieSignal(std::string t, std::string title, std::string genre, size_t year, size_t likes, std::string link);

public slots: void addMovie(std::string title, std::string genre, size_t year, size_t likes, std::string link);
public slots: void removeMovie(std::string title);
public slots: void updateMovie(std::string t, std::string title, std::string genre, size_t year, size_t likes, std::string link);
};

class UserGUI : public QWidget {
   Q_OBJECT
private:
    UserService* user_sv;
    AdminService* serv;
    QLabel* title_widget;
    QListWidget* movie_list_widget, * playlist_list_widget, * filter_movie_list_widget;
    QLineEdit* titleLineEdit, * genreLineEdit, * yearLineEdit, * likesLineEdit, * linkLineEdit, * titleFilterLineEdit, * genreFilterLineEdit, * filterLineEdit;
    QPushButton* addButton, * removeButton, * filterButton, * openListButton, *nextButton;
    QRadioButton* csvButton, * htmlButton;
    bool repoTypeSelected, filtered;
    void populateMovieList();
    void populatePlaylistList();
    void populateFilterList();
    void connectingSignalsAndSlots();
    void initUserGui();
    int getSelectedIndexMovies() const;
    int getSelectedIndexPlaylist() const;
    void AddMovieHandler();
    void RemoveMovieHandler();
    void nextMovieHandler();
    void guiFilterMovies();
    void fileHandler();
    void updateLabels();

    int index;

signals: void nextSignal();
signals: void updateWatchListSignal();
signals: void addMovieSignal(std::string title, std::string genre, size_t year, size_t likes, std::string link);
signals: void removeMovieSignal(std::string title);
signals: void filterSignal(std::string genre);
signals: void updateFilterListSignal();

public slots: void nextMovie();
public slots: void addMovie(std::string title, std::string genre, size_t year, size_t likes, std::string link);
public slots: void removeMovie(std::string title);
public slots: void filterMovie(std::string genre);

public:
    UserGUI(QWidget* parent, AdminService* serv, UserService* us_sv);
    ~UserGUI();
};

