#include <opencv2/opencv.hpp>
#include <memory>
namespace VisionPipeline
{
    class Pipeline {
    public:
        //Pipeline();
        virtual cv::Point getTarget() = 0;
    };
    namespace CubePipeline
    {
        class BlobPipe : public VisionPipeline::Pipeline {
            public:
                struct parameters {
                    double hsvThresholdHue[2];
                    double hsvThresholdSaturation[2];
                    double hsvThresholdValue[2];
                    double findBlobsMinArea;
                    double findBlobsCircularity[2];
                    bool findBlobsDarkBlobs;
                };
                BlobPipe();
                BlobPipe(const parameters&p);
                void Process(cv::Mat& source0);
                cv::Mat* GetHsvThresholdOutput();
                std::vector<cv::KeyPoint>* GetFindBlobsOutput();
                cv::Point getTarget();
                void setParams(const parameters& p);
            private:
                cv::Mat hsvThresholdOutput;
                std::vector<cv::KeyPoint> findBlobsOutput;
                void hsvThreshold(cv::Mat &, double [], double [], double [], cv::Mat &);
                void findBlobs(cv::Mat &, double , double [], bool , std::vector<cv::KeyPoint> &);
                parameters defaultParams_ = {
                    {22.66187050359712, 57.27272727272727},
                    {176.57374100719426, 255.0},
                    {141.936677589483, 243.73469372203152},
                    200.0,  // default Double
                    {0.0, 1.0},
                    false  // default Boolean
                };
                std::shared_ptr<parameters> currentParams_;
        };
    }
}
    
