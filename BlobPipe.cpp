//#include "BlobPipe.h"
#include "VisionPipelines.h"

namespace VisionPipeline {
	namespace CubePipeline {
		BlobPipe::BlobPipe() {
			//Use default params
			currentParams_ = std::make_shared<BlobPipe::parameters>(defaultParams_);
		}
		BlobPipe::BlobPipe(const BlobPipe::parameters& p) {
			setParams(p);
		}
		/**
		* Runs an iteration of the pipeline and updates outputs.
		*/
		void BlobPipe::Process(cv::Mat& source0){
			//Step HSV_Threshold0:
			//input
			cv::Mat hsvThresholdInput = source0;
			
			hsvThreshold(hsvThresholdInput, defaultParams_.hsvThresholdHue, defaultParams_.hsvThresholdSaturation, defaultParams_.hsvThresholdValue, this->hsvThresholdOutput);
			//Step Find_Blobs0:
			//input
			cv::Mat findBlobsInput = hsvThresholdOutput;
			findBlobs(findBlobsInput, defaultParams_.findBlobsMinArea, defaultParams_.findBlobsCircularity, defaultParams_.findBlobsDarkBlobs, this->findBlobsOutput);
		}

		/**
		 * This method is a generated getter for the output of a HSV_Threshold.
		 * @return Mat output from HSV_Threshold.
		 */
		cv::Mat* BlobPipe::GetHsvThresholdOutput(){
			return &(this->hsvThresholdOutput);
		}
		/**
		 * This method is a generated getter for the output of a Find_Blobs.
		 * @return BlobsReport output from Find_Blobs.
		 */
		std::vector<cv::KeyPoint>* BlobPipe::GetFindBlobsOutput(){
			return &(this->findBlobsOutput);
		}
		/**
		 * Segment an image based on hue, saturation, and value ranges.
		 *
		 * @param input The image on which to perform the HSL threshold.
		 * @param hue The min and max hue.
		 * @param sat The min and max saturation.
		 * @param val The min and max value.
		 * @param output The image in which to store the output.
		 */
		void BlobPipe::hsvThreshold(cv::Mat &input, double hue[], double sat[], double val[], cv::Mat &out) {
			cv::cvtColor(input, out, cv::COLOR_BGR2HSV);
			cv::inRange(out,cv::Scalar(hue[0], sat[0], val[0]), cv::Scalar(hue[1], sat[1], val[1]), out);
			cv::imshow("HSV", out);
		}

		/**
		 * Detects groups of pixels in an image.
		 *
		 * @param input The image on which to perform the find blobs.
		 * @param minArea The minimum size of a blob that will be found.
		 * @param circularity The minimum and maximum circularity of blobs that will be found.
		 * @param darkBlobs The boolean that determines if light or dark blobs are found.
		 * @param blobList The output where the MatOfKeyPoint is stored.
		 */
		//void findBlobs(Mat *input, double *minArea, double circularity[2],
			//bool *darkBlobs, vector<KeyPoint> *blobList) {
		void BlobPipe::findBlobs(cv::Mat &input, double minArea, double circularity[], bool darkBlobs, std::vector<cv::KeyPoint> &blobList) {
			blobList.clear();
			cv::SimpleBlobDetector::Params params;
			params.filterByColor = 1;
			params.blobColor = (darkBlobs ? 0 : 255);
			params.minThreshold = 10;
			params.maxThreshold = 220;
			params.filterByArea = true;
			params.minArea = minArea;
			params.filterByCircularity = true;
			params.minCircularity = circularity[0];
			params.maxCircularity = circularity[1];
			params.filterByConvexity = false;
			params.filterByInertia = false;
			cv::Ptr<cv::SimpleBlobDetector> detector = cv::SimpleBlobDetector::create(params);
			detector->detect(input, blobList);
		}

		//Select biggest blob
		cv::Point BlobPipe::getTarget() {
			cv::KeyPoint target(cv::Point(0,0), 0);
			for(auto i = findBlobsOutput.begin(); i!=findBlobsOutput.end(); i++) {
				if (i->size>target.size) target = *i;
			};
			return target.pt;
		};

		//Set the params pointer
		void BlobPipe::setParams(const BlobPipe::parameters& p) {
			currentParams_ = std::make_shared<BlobPipe::parameters>(p);
		}
	}
} // end grip namespace

