#include "VisionPipelines.h"

namespace VisionPipeline {
    Pipeline::Pipeline() {
        
    };
    void Pipeline::readImage(cv::Mat img) {
        img.copyTo(image_);
    }
}