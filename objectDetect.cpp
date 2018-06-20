#include "objectDetect.h"

objectDetector::objectDetector() {
    mFrame = cv::Mat::zeros(1,1,CV_8U);
    std::cout << "Hello\n";
}

void objectDetector::setFrame() {

}
cv::Point objectDetector::getTarget() {

}