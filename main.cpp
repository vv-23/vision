#include "VisionPipelines.h"
#include <iostream>


int main(int argc, char **argv) {
    std::string video_file(argv[1]);
    std::cout << video_file;
    bool playVideo = true;
    char key;
    VisionPipeline::CubePipeline::BlobPipe::parameters params;
    VisionPipeline::CubePipeline::BlobPipe pipe;
    while (1) {
        cv::VideoCapture capture(video_file);
        while(capture.get(1/*CAP_PROP_POS_FRAMES*/)<capture.get(7/*CAP_PROP_FRAME_COUNT*/)-1) {
            //we can loop the video by re-opening the capture every time the video reaches its last frame

            if (!capture.isOpened()) {
            std::cout << "ERROR ACQUIRING VIDEO FEED\n";
            getchar();
            return -1;
            }
            if (playVideo) {
                cv::Mat frame(cv::Scalar(capture.get(cv::CAP_PROP_FRAME_WIDTH), capture.get(cv::CAP_PROP_FRAME_HEIGHT)));
                //read first frame
                capture >> frame;
                //std::cout << frame.cols;
                //std::cout << frame.rows << std::endl;
                pipe.Process(frame);
                cv::Point target = pipe.getTarget();
                cv::circle(frame, target, 20, cv::Scalar(0, 255, 0), 2);
                cv::line(frame, target, cv::Point(target.x, target.y + 25), cv::Scalar(0, 255, 0), 2);
                cv::line(frame, target, cv::Point(target.x, target.y - 25), cv::Scalar(0, 255, 0), 2);
                cv::line(frame, target, cv::Point(target.x - 25, target.y), cv::Scalar(0, 255, 0), 2);
                cv::line(frame, target, cv::Point(target.x + 25, target.y), cv::Scalar(0, 255, 0), 2);
                    //cv::imshow("Camera", frame);
                    //cv::imshow("Video", frame);*/
                cv::imshow("Targets", frame);
                key = cv::waitKey(10);
                //if (key == 'p') playVideo = !playVideo;
            } 
        }
        capture.release();
    }
    return 0;
}