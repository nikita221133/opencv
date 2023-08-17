#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_openFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "/desktop", tr("Image Files (*.png *.jpg *.bmp)"));

    img = cv::imread(fileName.toStdString());
    image = QImage(img.data, img.cols, img.rows, QImage::Format_RGB888).rgbSwapped();
    pixel = QPixmap::fromImage(image);
    ui->image->setPixmap(pixel);
}


void MainWindow::on_blur_toggled(bool checked)
{
    cv::Mat blur_img;
    cv::blur(img, blur_img, cv::Size(3,3));
    image = QImage(blur_img.data, blur_img.cols, blur_img.rows, QImage::Format_RGB888).rgbSwapped();
    pixel = QPixmap::fromImage(image);
    ui->image->setPixmap(pixel);
}


void MainWindow::on_normal_toggled(bool checked)
{
    image = QImage(img.data, img.cols, img.rows, QImage::Format_RGB888).rgbSwapped();
    pixel = QPixmap::fromImage(image);
    ui->image->setPixmap(pixel);
}


void MainWindow::on_gausian_blur_toggled(bool checked)
{
    cv::Mat g_blur_img;
    cv::GaussianBlur(img, g_blur_img, cv::Size(3,3), 151);
    image = QImage(g_blur_img.data, g_blur_img.cols, g_blur_img.rows, QImage::Format_RGB888).rgbSwapped();
    pixel = QPixmap::fromImage(image);
    ui->image->setPixmap(pixel);
}


void MainWindow::on_gray_scale_toggled(bool checked)
{
    cv::Mat gray_img;
    cv::cvtColor(img, gray_img, cv::COLOR_BGR2GRAY);
    image = QImage(gray_img.data, gray_img.cols, gray_img.rows, QImage::Format_Grayscale8);
    pixel = QPixmap::fromImage(image);
    ui->image->setPixmap(pixel);
}


void MainWindow::on_hsv_color_toggled(bool checked)
{
    cv::Mat hsv_img;
    cv::cvtColor(img, hsv_img, cv::COLOR_BGR2HSV);
    image = QImage(hsv_img.data, hsv_img.cols, hsv_img.rows, QImage::Format_RGB888).rgbSwapped();
    pixel = QPixmap::fromImage(image);
    ui->image->setPixmap(pixel);
}


void MainWindow::on_canny_toggled(bool checked)
{
    cv::Mat canny_img, img1;
    cv::Canny(img, img1, 100, 200);
    canny_img = cv::Scalar::all(0);
    img.copyTo(canny_img, img1);
    image = QImage(canny_img.data, canny_img.cols, canny_img.rows, QImage::Format_RGB888).rgbSwapped();
    pixel = QPixmap::fromImage(image);
    ui->image->setPixmap(pixel);
}

