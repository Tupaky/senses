// tesscv.cpp:
// Using Tesseract API with OpenCV

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <tesseract/baseapi.h>
#include <iostream>
#include <fstream> // To write/read files

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    // Usage: tesscv image.png
    if (argc != 2)
    {
        std::cout << "Please specify the input image!" << std::endl;
        return -1;
    }

    // Load image
    cv::Mat im = cv::imread(argv[1]);
    if (im.empty())
    {
        std::cout << "Cannot open source image!" << std::endl;
        return -1;
    }

    cv::Mat gray;
    cv::cvtColor(im, gray, CV_BGR2GRAY);
    // ...other image pre-processing here...
    resize( gray, gray, cv::Size( 5000, 5000 ) );

    // Pass it to Tesseract API
    tesseract::TessBaseAPI tess;
    tess.Init(NULL, "por", tesseract::OEM_DEFAULT);
    //tess.SetPageSegMode(tesseract::PSM_SINGLE_BLOCK);
    tess.SetImage((uchar*)gray.data, gray.cols, gray.rows, 1, gray.cols);

    // Get the text
    char* out = tess.GetUTF8Text();
    std::cout << out << std::endl;

    ofstream txtfile ("output.txt");
    if (txtfile.is_open())
        txtfile << out << std::endl;
    else
        cout << "Unable to open file :(" << endl;
    return 0;
}
