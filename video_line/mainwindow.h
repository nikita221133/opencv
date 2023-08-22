#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <string.h>
#include <opencv2/opencv.hpp>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_openFile_clicked();

    void update();

private:
    Ui::MainWindow *ui;
    cv::Mat img_thr, img_raw, img_hsv, trans, img_trans, img_mat_thr;
    QImage image, image_thr, image_mat, image_mat_thr;
    QPixmap pixel, pixel_thr, pixel_mat, pixel_mat_thr;
    cv::VideoCapture vc;
    QTimer* timer;
    cv::Point2f points[4];
    cv::Point2f dst[4];
    double a,b,c,d,e;
};
#endif // MAINWINDOW_H
