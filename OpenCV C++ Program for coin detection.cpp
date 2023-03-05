#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    // Load image
    Mat img = imread("coins.jpg");

    // Convert image to grayscale
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);

    // Apply a blur to the image to reduce noise
    GaussianBlur(gray, gray, Size(5, 5), 0);

    // Apply a Canny edge detection algorithm to the image
    Mat edges;
    Canny(gray, edges, 100, 200);

    // Find contours in the image
    vector<vector<Point>> contours;
    findContours(edges, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // Loop over all contours to find coins
    for (size_t i = 0; i < contours.size(); i++)
    {
        // Compute the area of the contour
        double area = contourArea(contours[i]);

        // If the area is too small or too large, skip the contour
        if (area < 100 || area > 10000)
            continue;

        // Compute the perimeter of the contour
        double perimeter = arcLength(contours[i], true);

        // Compute the circularity of the contour
        double circularity = 4 * CV_PI * area / (perimeter * perimeter);

        // If the circularity is too low, skip the contour
        if (circularity < 0.6)
            continue;

        // Draw a bounding box around the contour
        Rect bbox = boundingRect(contours[i]);
        rectangle(img, bbox, Scalar(0, 255, 0), 2);
    }

    // Display the result
    imshow("Coins", img);
    waitKey(0);
    destroyAllWindows();

    return 0;
}
