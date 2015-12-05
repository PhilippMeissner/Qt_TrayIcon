#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    private:
        Ui::MainWindow *_ui;
        QSystemTrayIcon *_trayIcon;

        void createTrayIcon(MainWindow *parent);
    private slots:
        void onShowBalloonMessageClicked();
        void onShowAuthorClicked();

};

#endif // MAINWINDOW_H
