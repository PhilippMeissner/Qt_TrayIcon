#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIcon>
#include <QDebug>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QSsl>

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
    QAction *retrieveCommitMessage = new QAction("Check Github", trayIconMenu);


    // Connect the actions so that we can do something when clicked
    trayIconMenu->connect(closeAction, SIGNAL(triggered(bool)), parent, SLOT(close()));
    trayIconMenu->connect(showMessageAction, SIGNAL(triggered(bool)), parent, SLOT(onShowBalloonMessageClicked()));
    trayIconMenu->connect(showAuthor, SIGNAL(triggered(bool)), parent, SLOT(onShowAuthorClicked()));
    trayIconMenu->connect(retrieveCommitMessage, SIGNAL(triggered(bool)), parent, SLOT(onCheckGithubClicked()));

    // Add the actions to our menu
    trayIconMenu->addAction(closeAction);
    trayIconMenu->addAction(showMessageAction);
    trayIconMenu->addAction(showAuthor);
    trayIconMenu->addAction(retrieveCommitMessage);
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

// Private Slot -- If Check Github was clicked
void MainWindow::onCheckGithubClicked() {

    QNetworkAccessManager *networkManager = new QNetworkAccessManager();

    QUrl url("https://api.github.com/repos/philippmeissner/Qt_TrayIcon/commits");
    QNetworkRequest request(url);
    QNetworkReply *reply = networkManager->get(request);

    QSslSocket * sslSocket = new QSslSocket(this);
    QSslConfiguration config = sslSocket->sslConfiguration();
    config.setProtocol(QSsl::SslV2);
    sslSocket->setSslConfiguration(config);
    reply->setSslConfiguration(config);

    connect(reply, SIGNAL(finished()), this, SLOT(onRequestFinished()));
}


void MainWindow::onRequestFinished() {
    // Error: qt.network.ssl: QSslSocket: cannot resolve SSLv2_server_method
    // TODO: Read out JSON from data accordingly

    QNetworkReply *reply = ((QNetworkReply *)sender());
    QByteArray data = reply->readAll();
    showBalloonMessage(data);
}

void MainWindow::showBalloonMessage(QByteArray data) {
    QString completeResponse = "";

    for(int i = 0; i < data.length(); i++) {
        completeResponse += data[i];
    }

    _trayIcon->showMessage("We called the Github API!", completeResponse);
}
