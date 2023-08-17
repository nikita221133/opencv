#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <string.h>
#include <opencv4/opencv2/opencv.hpp>

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

    void on_blur_toggled(bool checked);

    void on_normal_toggled(bool checked);

    void on_gausian_blur_toggled(bool checked);

    void on_gray_scale_toggled(bool checked);

    void on_hsv_color_toggled(bool checked);

    void on_canny_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    cv::Mat img;
    QImage image;
    QPixmap pixel;
};
#endif // MAINWINDOW_H
