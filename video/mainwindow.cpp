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
//    if (!vc.read(img))
//        return;

    vc >> img;
    if (vc.isOpened())
        qDebug() << vc.getBackendName().c_str();
    if (ui->blur->isChecked())
    {
        cv::blur(img, img, cv::Size(8,8));
        image = QImage(img.data, img.cols, img.rows, QImage::Format_RGB888).rgbSwapped();
        pixel = QPixmap::fromImage(image);
        ui->image->setPixmap(pixel);
    }
    else if (ui->gausian_blur->isChecked())
    {
        cv::GaussianBlur(img, img, cv::Size(5,5), 151);
        image = QImage(img.data, img.cols, img.rows, QImage::Format_RGB888).rgbSwapped();
        pixel = QPixmap::fromImage(image);
        ui->image->setPixmap(pixel);
    }
    else if (ui->gray_scale->isChecked())
    {
        cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
        image = QImage(img.data, img.cols, img.rows, QImage::Format_Grayscale8);
        pixel = QPixmap::fromImage(image);
        ui->image->setPixmap(pixel);
    }
    else if (ui->hsv_color->isChecked())
    {
        cv::Mat hsv_img;
        cv::cvtColor(img, hsv_img, cv::COLOR_BGR2HSV);
        image = QImage(hsv_img.data, hsv_img.cols, hsv_img.rows, QImage::Format_RGB888).rgbSwapped();
        pixel = QPixmap::fromImage(image);
        ui->image->setPixmap(pixel);
    }
    else if (ui->canny->isChecked())
    {
        cv::Mat canny_img, img1;
        cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
        cv::Canny(img, img1, 100, 200);
        canny_img = cv::Scalar::all(0);
        img.copyTo(canny_img, img1);
        image = QImage(canny_img.data, canny_img.cols, canny_img.rows, QImage::Format_Grayscale8).rgbSwapped();
        pixel = QPixmap::fromImage(image);
        ui->image->setPixmap(pixel);
    }
    else
    {
        image = QImage(img.data, img.cols, img.rows, QImage::Format_RGB888).rgbSwapped();
        pixel = QPixmap::fromImage(image);
        ui->image->setPixmap(pixel);
    }
}

void MainWindow::on_openFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Video"), "/desktop", tr("Video Files (*.mp4 *.avi *.wmv)"));

    vc = cv::VideoCapture(fileName.toStdString());
    vc.read(img);
    image = QImage(img.data, img.cols, img.rows, QImage::Format_RGB888).rgbSwapped();
    pixel = QPixmap::fromImage(image);
    ui->image->setPixmap(pixel);
}



void MainWindow::on_video_clicked()
{
//    vc = cv::VideoCapture(0);
    vc.open(0, cv::CAP_DSHOW);

    if (!vc.isOpened())
    {
        qDebug() << "Pizdec";
    }
}
