#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QtNetwork>
#include <QTimer>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();
        void showBalloonMessage(QByteArray data);

    private:
        Ui::MainWindow *_ui;
        QSystemTrayIcon *_trayIcon;
        QTimer *_timer;
        bool _timerStarted;

        void createTrayIcon(MainWindow *parent);

    private slots:
        void onShowBalloonMessageClicked();
        void onShowAuthorClicked();
        void onCheckGithubClicked();
        void onRequestFinished();
        void onWatchGithubClicked();
        void onIntervalFinished();
};

#endif // MAINWINDOW_H
