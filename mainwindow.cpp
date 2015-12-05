#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIcon>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);
    createTrayIcon(this);
}

// Let's remove all traces in our memory, in case Qt doesn't ;)
MainWindow::~MainWindow() {
    delete _ui;
    delete _trayIcon;
}


// Sets the tray icon up
void MainWindow::createTrayIcon(MainWindow *parent) {
    // Add an icon to the system tray
    QIcon icon(":/images/mytrayicon.ico");
    _trayIcon = new QSystemTrayIcon(icon, parent);

    // Create a menu
    QMenu *trayIconMenu = new QMenu(this);

    // Create new, clickable actions
    QAction *closeAction        = new QAction("Close", trayIconMenu);
    QAction *showMessageAction  = new QAction("Show Balloon", trayIconMenu);
    QAction *showAuthor         = new QAction("About", trayIconMenu);

    // Connect the actions so that we can do something when clicked
    trayIconMenu->connect(closeAction, SIGNAL(triggered(bool)), parent, SLOT(close()));
    trayIconMenu->connect(showMessageAction, SIGNAL(triggered(bool)), parent, SLOT(onShowBalloonMessageClicked()));
    trayIconMenu->connect(showAuthor, SIGNAL(triggered(bool)), parent, SLOT(onShowAuthorClicked()));

    // Add the actions to our menu
    trayIconMenu->addAction(closeAction);
    trayIconMenu->addAction(showMessageAction);
    trayIconMenu->addAction(showAuthor);
    _trayIcon->setContextMenu(trayIconMenu);

    // Show the finished trayicon
    _trayIcon->show();
}

// Private Slot -- Shows the Balloon Message
void MainWindow::onShowBalloonMessageClicked() {
    _trayIcon->showMessage("Hi there!", "This is some crazy Balloon Message. Great, isn't it?", QSystemTrayIcon::Information, 2000);
}

// Private Slot -- Shows the original author
void MainWindow::onShowAuthorClicked() {
    _trayIcon->showMessage("Author", "This program was originally created by Philipp Meissner \nGithub.com/PhilippMeissner\n Enjoy :)", QSystemTrayIcon::Information);
}
