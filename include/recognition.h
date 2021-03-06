#ifndef RECOGNITION_H
#define RECOGNITION_H

#include <vector>
#include <map>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/contrib/contrib.hpp>

#include "detection.h"

// max nb of image per user we want to train the models on.
static const int MAX_TRAINING_IMAGES = 5;

static const int FACE_WIDTH = 200;

class Recognizer {

public:
    Recognizer(const FaceDetector& detector);

    /** Add data to the training set, and train the model as soon as enough images
     * are available for a given label.
     *
     * Returns true if enough images are already collected for this label.
     */
    bool addPictureOf(const cv::Mat& image, const std::string& label);

    /** Returns a pair {label, confidence}
     */
    std::pair<std::string, double> whois(const cv::Mat& image);


    cv::Mat reconstructFace(const cv::Mat preprocessedFace);
    bool preprocessFace(const cv::Mat& inputImage, cv::Mat& outputImage);

    std::vector<cv::Mat> eigenfaces();

private:
    void train(int label);

    const FaceDetector& _detector;

    cv::Ptr<cv::FaceRecognizer> model;

    std::map<int, std::vector<cv::Mat>> trainingSet;
    std::map<int, bool> trained_labels;
    std::map<int, std::string> human_labels;
};

#endif // RECOGNITION_H
