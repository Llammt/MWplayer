#include "user_interface.h"
#include "ui_user_interface.h"
#include <iostream>

user_interface::user_interface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::user_interface) {
    mainVideo = new videostream();
    mainVStream = new QThread;
    mainVideo->moveToThread(mainVStream);

    QObject::connect(mainVideo, SIGNAL(processedFrame(QImage)), this, SLOT(updateUI(QImage)));
    QObject::connect(mainVStream, SIGNAL(started()), mainVideo, SLOT(playVideo()));
    QObject::connect(mainVideo, SIGNAL(finished()), mainVideo, SLOT(deleteLater()));
    QObject::connect(mainVStream, SIGNAL(finished()), mainVideo, SLOT(deleteLater()));

    ui->setupUi(this);
}

void user_interface::updateUI(QImage img) {
    if (!img.isNull()) {
        ui->label->setAlignment(Qt::AlignCenter);
        ui->label->setPixmap(QPixmap::fromImage(img).scaled(ui->label->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
    }
}

user_interface::~user_interface() {
    delete ui;
    mainVideo->deleteLater();
    mainVStream->deleteLater();
}

//выбрать файл, который будет проигрываться в главном окне
void user_interface::on_loadButton_clicked() {
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Video"), ".", tr("Video Files (*.avi *.mpg *.mp4)"));
    if (!filename.isEmpty()){
        if (!mainVideo->loadVideo(filename.toUtf8().data())) {
            QMessageBox msgBox;
            msgBox.setText("The selected video could not be opened!");
            msgBox.exec();
        }
        else
            ui->label->setText(filename);
    }
    mainVStream->start();
}

void user_interface::on_playButton_clicked() {
    if (mainVideo->paused == true) {
        mainVideo->isPaused.wakeOne();
        mainVideo->paused = false;
        ui->playButton->setText(tr("Pause"));
    }
    else {
        mainVideo->paused = true;
        ui->playButton->setText(tr("Play"));
    }
}

