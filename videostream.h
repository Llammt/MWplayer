//class provides an Qt-friendly interface for working with opencv functions

#ifndef VIDEOSTREAM_H
#define VIDEOSTREAM_H
#include <QObject>
#include <QImage>
#include <QMutex>
#include <QWaitCondition>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

class videostream : public QObject{
    Q_OBJECT

public:
    videostream();
   ~videostream();
   bool loadVideo(string filename);
   bool paused;
   QWaitCondition isPaused;


private:
   Mat frame;
   int frame_rate;
   VideoCapture capture;
   Mat RGBframe;
   QImage img;
   QMutex pauseMutex;

   void delay();

signals:
   void processedFrame(const QImage &image);
   void finished();

public slots:
   void playVideo();

};

#endif // VIDEOSTREAM_H
