#ifndef DETECTION_H
#define DETECTION_H

#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp> //boundingRect
#include <opencv2/objdetect/objdetect.hpp>

static const unsigned char NB_FEATURES = 20;

class FaceDetector {

public:


    FaceDetector();

    std::vector<cv::Rect> detect(const cv::Mat& image, int scaledWidth = 200);

private:
    cv::CascadeClassifier frontalface;
};

class FaceTracker {

public:
    FaceTracker(const cv::Mat& image, const std::vector<cv::Point2f>& features);
    std::vector<cv::Point2f> track(const cv::Mat& image);
    void resetFeatures(const cv::Mat& image, const cv::Rect& face);

    static std::vector<cv::Point2f> features(const cv::Mat& image, const cv::Rect& face);

    cv::Point2f centroid() const {return _centroid;}
    cv::Rect boundingBox() const {return cv::boundingRect(prevFeatures);}
private:

    std::vector<cv::Point2f> pruneFeatures(const std::vector<cv::Point2f>& features);

    cv::Mat prevImg;
    std::vector<cv::Point2f> prevFeatures;

    cv::Point2f _centroid;
    double _variance;

};

#endif // DETECTION_H