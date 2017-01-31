#include <videostream.h>
#include <ctime>
#include <iostream>

videostream::videostream() {
    paused = true;
}

videostream::~videostream() {
    pauseMutex.lock();
    paused = true;
    capture.release();
    isPaused.wakeOne();
    pauseMutex.unlock();
}

bool videostream::loadVideo(string filename) {
    capture.open(filename);
    if (capture.isOpened()) {
        frame_rate = (int) capture.get(CV_CAP_PROP_FPS);
        return true;
    }
    else
        return false;
}

void videostream::playVideo() {
    while (capture.read(frame)){
        Rect second_stream(frame.cols*0.75, frame.rows*0.75, frame.cols*0.25, frame.rows*0.25);
        frame(second_stream) *= 0.5;

        if (!paused) {
            if (frame.channels()== 3){
                cv::cvtColor(frame, RGBframe, CV_BGR2RGB);//, copy image in RGBframe, translate to RGB
                img = QImage((const unsigned char*)(RGBframe.data),
                              RGBframe.cols,RGBframe.rows,QImage::Format_RGB888);//...and to QImage
            }
            else
                img = QImage((const unsigned char*)(frame.data), frame.cols,frame.rows,QImage::Format_Indexed8);

            emit processedFrame(img);//signal for player to show frame
            this->delay();
        }
        else {
            pauseMutex.lock();
            isPaused.wait(&pauseMutex);
            pauseMutex.unlock();
        }
    }
    emit finished();
}

void videostream::delay(){
    int ms = 1000/frame_rate;
    struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
    nanosleep(&ts, NULL);
}
