#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <opencv2/videoio.hpp>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(25);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update()
{
    if (!vc.read(img_raw))
        return;

    a = (img_raw.cols / 2 - 450) + ui->width_sl->value();
    b = img_raw.cols / 2 + 450 - ui->width_sl->value();
    c = img_raw.cols / 2 - 450 - ui->width_bot_sl->value();
    d = img_raw.cols / 2 + 450 + ui->width_bot_sl->value();
    e = img_raw.rows / 2 + 50 + ui->height_sl->value();

    dst[0] = cv::Point2f(a, e);
    dst[1] = cv::Point2f(b, e);
    dst[2] = cv::Point2f(d, 700);
    dst[3] = cv::Point2f(c, 700);

    trans = cv::getPerspectiveTransform(dst, points);

    cv::cvtColor(img_raw, img_hsv, cv::COLOR_BGR2HSV);
    cv::inRange(img_hsv, cv::Scalar(0, 0, 190), cv::Scalar(255, 255, 255), img_thr);


    image_thr = QImage(img_thr.data, img_thr.cols, img_thr.rows, QImage::Format_Grayscale8).rgbSwapped();
    if (ui->video_debug->width() < ui->video_debug->height() * 2)
    {
        image_thr = image_thr.scaledToWidth(ui->video_debug->width());
    }
    else if (ui->video_debug->width() >= ui->video_debug->height() * 2)
    {
        image_thr = image_thr.scaledToHeight(ui->video_debug->height());
    }
    pixel_thr = QPixmap::fromImage(image_thr);
    ui->video_debug->setPixmap(pixel_thr);

    cv::warpPerspective(img_raw, img_trans, trans, cv::Size(img_raw.rows, img_raw.rows));

    image_mat = QImage(img_trans.data, img_trans.cols, img_trans.rows, QImage::Format_RGB888).rgbSwapped();

    image_mat = image_mat.scaledToHeight(ui->mat_raw->height());
    pixel_mat = QPixmap::fromImage(image_mat);
    ui->mat_raw->setPixmap(pixel_mat);

    cv::cvtColor(img_trans, img_mat_thr, cv::COLOR_BGR2HSV);
    cv::inRange(img_mat_thr, cv::Scalar(0, 0, 190), cv::Scalar(255, 255, 255), img_mat_thr);


    image_mat_thr = QImage(img_mat_thr.data, img_mat_thr.cols, img_mat_thr.rows, QImage::Format_Grayscale8).rgbSwapped();
    image_mat_thr = image_mat_thr.scaledToHeight(ui->mat_debug->height());
    pixel_mat_thr = QPixmap::fromImage(image_mat_thr);
    ui->mat_debug->setPixmap(pixel_mat_thr);

    cv::line(img_raw, dst[0], dst[1], cv::Scalar(0, 255, 0), 2, 0);
    cv::line(img_raw, dst[1], dst[2], cv::Scalar(0, 255, 0), 2, 0);
    cv::line(img_raw, dst[2], dst[3], cv::Scalar(0, 255, 0), 2, 0);
    cv::line(img_raw, dst[3], dst[0], cv::Scalar(0, 255, 0), 2, 0);


    if (ui->FPS->isChecked())
        cv::putText(img_raw, QString::number(vc.get(cv::VideoCaptureProperties::CAP_PROP_FPS)).toStdString(), cv::Point2f(10, 50), cv::FONT_HERSHEY_SIMPLEX, 2, cv::Scalar(0, 255, 0), 2, cv::LINE_AA);

    if (ui->num_frame->isChecked())
    {
        cv::putText(img_raw, QString::number(vc.get(cv::VideoCaptureProperties::CAP_PROP_POS_FRAMES)).toStdString(), cv::Point2f(10, 100), cv::FONT_HERSHEY_SIMPLEX, 2, cv::Scalar(0, 255, 0), 2, cv::LINE_AA);
        cv::putText(img_raw, QString::number(vc.get(cv::VideoCaptureProperties::CAP_PROP_FRAME_COUNT)).toStdString(), cv::Point2f(300, 100), cv::FONT_HERSHEY_SIMPLEX, 2, cv::Scalar(0, 255, 0), 2, cv::LINE_AA);
    }

    image = QImage(img_raw.data, img_raw.cols, img_raw.rows, QImage::Format_RGB888).rgbSwapped();
    if (ui->video_raw->width() < ui->video_raw->height() * 2)
    {
        image = image.scaledToWidth(ui->video_raw->width());
    }
    else if (ui->video_raw->width() >= ui->video_raw->height() * 2)
    {
        image = image.scaledToHeight(ui->video_raw->height());
    }
    pixel = QPixmap::fromImage(image);
    ui->video_raw->setPixmap(pixel);
}


void MainWindow::on_openFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Video"), "/desktop", tr("Video Files (*.mp4 *.avi *.wmv)"));

    vc = cv::VideoCapture(fileName.toStdString());

    vc.read(img_raw);

    points[0] = cv::Point2f(0, 0);
    points[1] = cv::Point2f(img_raw.rows, 0);
    points[2] = cv::Point2f(img_raw.rows, img_raw.rows);
    points[3] = cv::Point2f(0, img_raw.rows);

    trans = cv::getPerspectiveTransform(dst, points);

}


