#ifndef BASERECORDER_H
#define BASERECORDER_H

#include <QObject>
#include <QTimer>
#include "opencv2\opencv.hpp"

class BaseRecorder : public QObject
{
    Q_OBJECT
    QTimer* timer;
    QTime timestarted;
    QString m_file;
    double m_fps;

	std::unique_ptr<cv::VideoWriter> writer;
public:
    explicit BaseRecorder(QObject *parent = 0);
    ~BaseRecorder();

	cv::Mat frame;
	cv::Size frameSize;

signals:
    void timestatus(const QString&);

public slots:
    virtual void initRecorder(const QString& video_file, double frame_rate = 25.0);
    virtual void timeout();

    virtual void start();
    virtual void pause();
    virtual void stop();
};

#endif // BASERECORDER_H
