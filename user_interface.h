//Class provides user interface for player
#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include <QMainWindow>
#include <QFileDialog>
#include <QThread>
#include <QMessageBox>
#include "videostream.h"

namespace Ui {
class user_interface;
}

class user_interface : public QMainWindow {
    Q_OBJECT

public:
    explicit user_interface(QWidget *parent = 0);
    ~user_interface();

private:
    Ui::user_interface *ui;
    videostream* mainVideo;
    QThread* mainVStream;

private slots:
    void on_loadButton_clicked();
    void on_playButton_clicked();
    void updateUI(QImage img);
};
#endif // USER_INTERFACE_H
