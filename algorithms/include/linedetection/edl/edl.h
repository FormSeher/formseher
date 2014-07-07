#ifndef FS_EDL_H
#define FS_EDL_H

/*#ifndef M_PI
#define M_PI 3.141592654
#endif*/

#include "linedetection/linedetectionalgorithm.h"

#include "line.h"

#include "mathutil.h"

#include <opencv2/core/core.hpp>
#include <vector>
#include <list>

#define HORIZONTAL 0
#define VERTICAL   1

namespace formseher
{

class EDL : public LineDetectionAlgorithm
{
public:
    /**
     * @brief Constructor of EDL.
     *
     *  This method initializes the EDL algorithm with given (or default) parameters.
     *
     * @param sobelKernelSize Kernel size used by sobel operator.
     * @param sobelScale Scale used by sobel operator.
     * @param sobelDelta Delta used by sobel operator.
     * @param gaussianKernelSize Kernel size for gaussian blur.
     * @param anchorThreshold Minimum threshold for anchor computation.
     * @param angleTolerance Used to split line into line segments if gradient angle differs too much.
     * @param minLineLength Minimum line length.
     */
    EDL(int sobelKernelSize = 3, double sobelScale = 1.9, double sobelDelta = 0.0, int gaussianKernelSize = 3,
        int anchorThreshold = 36, double angleTolerance = 22.5 *  math::m_pi / 180.0, unsigned int minLineLength = 30);
    ~EDL();

    /*! @copydoc LineDetectionAlgorithm::calculate()
     */
    std::vector<Line> calculate(cv::InputArray _image);

private:
    /**
     * @brief Calculate gradient magnitudes and angles and anchor points.
     *
     * Calculate angles and magnitudes of gradients and anchor points.
     *
     * @param _gradientX x-component of gradient vector calculated by sobel operator.
     * @param _gradientY y-component of gradient vector calculated by sobel operator.
     * @param _gradientMagnitudes Matrix the calculated magnitudes are saved into.
     * @param _gradientAngles Matrix the calculated angles are saved into.
     * @param anchors Vector of all anchor points.
     */
    void calcGradAngleAnchors(cv::InputArray _gradientX, cv::InputArray _gradientY, cv::OutputArray _gradientMagnitudes, cv::OutputArray _gradientAngles, std::vector<cv::Point>& anchors);

    /**
     * @brief Checks if a given point is an anchor point.
     *
     * Checks if given point is an anchor point by calculating a delta to its neighbours which lie on the line (@see getDirection()). If the
     * delta is higher than anchorThreshold, this method returns true.
     *
     * @param src Matrix holding the gradient magnitudes of the image.
     * @param row Row of the point being checked.
     * @param column Column of the point being checked.
     * @return True if the given point is an anchor point, false otherwise.
     */
    bool isAnchor(cv::Mat& src, int row, int column);

    /**
     * @brief Routing algorithm which creates the lines.
     *
     * Iterates through all anchor points calculated by calcGradAngleAnchors() and calls walkFromAnchor().
     *
     * @param angleTolerance The angle tolerance used.
     * @param magnitudes Matrix of gradient magnitudes of the image.
     * @param angles Matrix of gradient angles of the image.
     * @param anchorPoints Vector of anchor points
     * @param result Reference to vector of Lines found.
     */
    void routeAnchors(double angleTolerance, cv::InputArray magnitudes, cv::InputArray angles, std::vector<cv::Point>& anchorPoints, std::vector<Line>& result);

    /**
     * @brief Routes one anchor point.
     *
     * This method is called by routeAnchors() for each anchor point and creates line segments. It walks along the direction of the line passing through
     * this point. It adds all points which are on the line to a line segment. New line segments are created if angle of gradients exceed the
     * given threshold (@see isAligned()).
     *
     * @param anchorPoint The anchor point currently examined.
     * @param angleTolerance The angle tolerance used.
     * @param gradientMagnitudes Matrix of gradient magnitudes of the image.
     * @param gradientAngles Matrix of gradient angles of the image.
     * @param edgels Matrix which saves all image points which where already examined by walkFromAnchor.
     * @param lineSegments Vector which holds lists forming line segments.
     */
    void walkFromAnchor(cv::Point& anchorPoint, double angleTolerance, cv::Mat_<uchar>& gradientMagnitudes, cv::Mat_<double>& gradientAngles, cv::Mat_<uchar> &edgels, std::vector<std::list<cv::Point*>*>& lineSegments);

    /**
     * @brief Calculates the line direction for given angle.
     *
     * The line direction is assumed to be perpendicular to the gradient angle.
     *
     * @param angle Gradient angle which is perpendicular to line direction.
     * @return 0 if direction is horizontal, 1 otherwise.
     */
    bool getDirection(double angle);

    /**
     * @brief Calculates which point is examined next by walkFromAnchor().
     *
     * Calculates the next point for the walkFromAnchor() iteration.
     *
     * @param currentPoint The currently examined point.
     * @param mainDirection The main direction of the line.
     * @param subDirection The direction currently examined (left/right or up/down of line direction).
     * @param gradientMagnitudes Matrix of gradient magnitudes of the image.
     * @return Pointer to next cv::Point or null if line segment ended here.
     */
    cv::Point* findNextPoint(cv::Point* currentPoint, int mainDirection, int subDirection, cv::Mat_<uchar>& gradientMagnitudes);

    /**
     * @brief Checks if angles are aligned by certain tolerance.
     * @param compare The angle which is compared.
     * @param angle The reference angle with wich compare is compared.
     * @param tolerance The maximal tolerance to see compare aligned to angle.
     * @return True if angles are aligned, false otherwise.
     */
    bool isAligned(double compare, double angle, double tolerance);

    /**
     * @brief Check if a point is out of image bounds.
     * @param point Point being checked.
     * @param matrix Matrix which is checked.
     * @return True if point is in bounds of matrix, false otherwise.
     */
    bool isOutOfBounds(cv::Point* point, cv::InputArray matrix);

    int sobelKernelSize;
    double sobelScale;
    double sobelDelta;
    int gaussianKernelSize;
    int anchorThreshold;
    double angleTolerance;
    unsigned int minLineLength;
};

} // namespace formseher

#endif // FS_EDL_H
