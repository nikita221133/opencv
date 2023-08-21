#include "mainwindow.h"
#include "./ui_mainwindow.h"

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
  //  c = (900 - b_foundation) / 2;
  //  d = 900 - (710 - b_foundation) / 2;
    e = img_raw.rows / 2 + 50 + ui->height_sl->value();

    qDebug() << a << ", " << b << ", " << e;

    dst[0] = cv::Point2f(a, e);
    dst[1] = cv::Point2f(b, e);
    dst[2] = cv::Point2f(1110, 700);
    dst[3] = cv::Point2f(210, 700);

    trans = cv::getPerspectiveTransform(dst, points);


//    cv::blur(img_raw, img_hsv, cv::Size(3, 3));

    cv::cvtColor(img_raw, img_hsv, cv::COLOR_BGR2HSV);
    cv::inRange(img_hsv, cv::Scalar(0, 0, 200), cv::Scalar(255, 255, 255), img_thr);


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
    if (ui->mat_raw->width() < ui->mat_raw->height() * 2)
    {
        image_mat = image_mat.scaledToWidth(ui->mat_raw->width());
    }
    else if (ui->mat_raw->width() >= ui->mat_raw->height() * 2)
    {
        image_mat = image_mat.scaledToHeight(ui->mat_raw->height());
    }
    pixel_mat = QPixmap::fromImage(image_mat);
    ui->mat_raw->setPixmap(pixel_mat);

    cv::line(img_raw, dst[0], dst[1], cv::Scalar(0, 255, 0), 2, 0);
    cv::line(img_raw, dst[1], dst[2], cv::Scalar(0, 255, 0), 2, 0);
    cv::line(img_raw, dst[2], dst[3], cv::Scalar(0, 255, 0), 2, 0);
    cv::line(img_raw, dst[3], dst[0], cv::Scalar(0, 255, 0), 2, 0);

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
    points[0] = cv::Point2f(0, 0);
    points[1] = cv::Point2f(720, 0);
    points[2] = cv::Point2f(720, 720);
    points[3] = cv::Point2f(0, 720);

    dst[0] = cv::Point2f(410, 500);
    dst[1] = cv::Point2f(910, 500);
    dst[2] = cv::Point2f(1110, 700);
    dst[3] = cv::Point2f(210, 700);

    vc.read(img_raw);

    trans = cv::getPerspectiveTransform(dst, points);

}


