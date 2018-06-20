#pragma once
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>


class objectDetector {
public:
    objectDetector();
    virtual void setFrame();
    virtual cv::Point getTarget();
private:
    cv::Mat mFrame;
};