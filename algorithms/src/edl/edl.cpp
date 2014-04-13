#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>

EDL::EDL()
{   private:
        int threshold;
        cv::Mat src;
        int ksize;
        double scale;
        double delta;
    public:
        EDL(int ksize, double scale, double delta) : ksize(3), scale(1), delta(0), threshold(36)
        {
            cv::cvtColor((cv::imread(path, CV_LOAD_IMAGE_COLOR)), src, CV_RGB2GRAY);
        }
}

EDL::~EDL()
{

}

void EDL::calculate()
{
    //Definitions for sobel
    cv::Mat dx;
    cv::Mat dy;
    cv::Mat adx;
    cv::Mat ady;

    //Definitions for grad, angle and anchor calculation
    cv::Mat grad = cv::Mat::zeros(src.rows, src.cols, CV_8U);
    cv::Mat angle = cv::Mat::zeros(src.rows, src.cols, CV_32F);
    std::vector<cv::Point> anchors;

    // ####
    // use a filter algorithm to suppress noise
    // ####


    // ####
    // run the edge operator
    // ####

    cv::Sobel(src, dx, CV_16S, 1, 0, ksize, scale, delta, cv::BORDER_DEFAULT);
    cv::Sobel(src, dy, CV_16S, 0, 1, ksize, scale, delta, cv::BORDER_DEFAULT);
    convertScaleAbs( dx, adx ); //decrease to CV_8U again
    convertScaleAbs( dy, ady ); //always use adx, ady to proceed!

    // ####
    // create gradient and direction output including the anchorpoints
    // ####

    calcGradAngleAnchors(adx, ady, grad, angle, anchors, threshold);

    // ####
    // run the routing algorithm
    // ####

    // Save result
}

bool EDL::isAnchor(cv::Mat& src, int x, int y, int threshold){
    bool isanchor = false;
    if (x > 0 && y > 0 && x < src.rows && y < src.cols) { //skip the first row of pixels
        int center = src.at<uchar>(x,y);
        int top = src.at<uchar>(x,y+1);
        int bottom = src.at<uchar>(x,y-1);
        int right = src.at<uchar>(x+1,y);
        int left = src.at<uchar>(x-1,y);
        if (center - top >= threshold && center - bottom >= threshold) {
            isanchor = true;
        }
        if (center - right >= threshold && center - left >= threshold) {
            isanchor = true;
        }
    }
    return isanchor;
}

void EDL::calcGradAngleAnchors(cv::InputArray gradientX, cv::InputArray gradientY, cv::OutputArray gradientMagnitude, cv::OutputArray gradientAngle, std::vector<cv::Point> anchors, int threshold ){
    cv::Mat X = gradientX.getMat();
    cv::Mat Y = gradientY.getMat();
    cv::Mat Ang = gradientAngle.getMat();
    cv::Mat Mag = gradientMagnitude.getMat();
    int nRows = Mag.rows;
    int nCols = Mag.cols;

    for(int i = 0; i < nRows; ++i){
        const uchar *x = X.ptr<uchar>(i);
        const uchar *y = Y.ptr<uchar>(i);
        uchar* p_mag = Mag.ptr<uchar>(i);
        float* p_ang = Ang.ptr<float>(i);

        for (int j = 0; j < nCols; ++j){
            float x0 = x[j], y0 = y[j];
            p_mag[j] = std::sqrt(x0*x0 + y0*y0);
            p_ang[j] = (M_PI/180) * cv::fastAtan2(y0, x0);
                if(isAnchor(Mag, i, j, threshold))
                {
                    anchors.push_back(cv::Point(i,j));
                }
        }
    }
}


void EDL::routeAnchors(cv::InputArray magnitudes, cv::InputArray angles, std::vector<cv::Point2i*>& anchorPoints, std::vector<Line*> result)
{

}
