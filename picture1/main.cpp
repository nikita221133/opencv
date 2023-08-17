#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

int main(int argc, char** argv)
{
    cv::Mat img_c = cv::imread("D:/Users/111/Downloads/IMG_20200902_144838.jpg");
    if(img_c.empty())
        return -1;
    cv::Mat img;
 //   cv::pyrDown(img_c, img, cv::Size(img_c.cols/2,img_c.rows/2));
    cv::namedWindow("example", cv::WINDOW_AUTOSIZE);
    cv::imshow("example", img);
    cv::namedWindow("example1", cv::WINDOW_AUTOSIZE);
    cv::Mat img2;
    cv::blur(img, img2, cv::Size(30,30));
    cv::imshow("example1", img2);
    cv::Mat img3;
    cv::namedWindow("example2", cv::WINDOW_AUTOSIZE);
    cv::GaussianBlur(img, img3, cv::Size(5,5), 21);
    cv::imshow("example2", img3);
    cv::Mat img4;
    cv::namedWindow("example3", cv::WINDOW_AUTOSIZE);
    cv::cvtColor(img, img4, cv::COLOR_BGR2GRAY);
    cv::imshow("example3", img4);
    cv::Mat img5, img6;
    cv::namedWindow("example4", cv::WINDOW_AUTOSIZE);
    cv::Canny(img, img5, 1, 3);
    img6 = cv::Scalar::all(0);
    img.copyTo(img6, img5);
    cv::imshow("example4", img6);
    cv::waitKey(0);
    cv::destroyWindow("example");
    cv::destroyWindow("example1");
    cv::destroyWindow("example2");
    cv::destroyWindow("example3");
    return 0;
}
