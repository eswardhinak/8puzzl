#include "mainwindow.h"
#include <opencv2/opencv.hpp>
#include <QApplication>
#include "multiimageclass.h"

using namespace cv;
using namespace std;

int* constructRanges(int maxNumber, int bucketSize) {
    int * buckets = new int[maxNumber/bucketSize];
    int counter=0;
    for (int i=0; i<=maxNumber; i+=bucketSize) {
        if (i > maxNumber) {
            break;
        }
        if (i == 0) {
            continue;
        }
        buckets[counter] = i;
        counter += 1;
    }
    return buckets;
}

QImage matToQImage(const cv::Mat& mat)
{
    // Convert Mat to QImage
    if (mat.type() == CV_8UC3)
    {
        cv::Mat rgb;
        cv::cvtColor(mat, rgb, cv::COLOR_BGR2RGB);
        return QImage(rgb.data, rgb.cols, rgb.rows, rgb.step, QImage::Format_RGB888).copy();
    }
    else if (mat.type() == CV_8UC1)
    {
        return QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Grayscale8).copy();
    }
    // Add more conversions as needed
    return QImage();
}

vector<Mat> sliceIntoNineSquares(Mat* imageMatrix)
{
    int rows = imageMatrix->rows;
    int cols = imageMatrix->cols;
    int cell_height = rows / 3;
    int cell_width = cols / 3;

    vector<Mat> puzzlePieces;
    puzzlePieces.reserve(9);  // Reserve space for 9 elements

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int y1 = i * cell_height;
            int y2 = (i < 2) ? (i + 1) * cell_height : rows;
            int x1 = j * cell_width;
            int x2 = (j < 2) ? (j + 1) * cell_width : cols;

            puzzlePieces.push_back((*imageMatrix)(Range(y1, y2), Range(x1, x2)));

        }
    }

    return puzzlePieces;
}




int main(int argc, char *argv[])
{
    // Read the image file as
    // imread("default.jpg");
    QApplication a(argc, argv);

    Mat image = imread("/Users/eswar/desktop/india_passport.jpeg");
    cout << "Image type: " << image.type() << endl;
    cout << "Rows: " << image.rows << "\nCols: " << image.cols << endl;
    vector<Mat> puzzlePieces = sliceIntoNineSquares(&image);


    MultiImageClass canvas;
    canvas.setImages(puzzlePieces);
    canvas.resize(800, 900);
    canvas.show();

    // Error Handling
    if (image.empty()) {
        cout << "Image File "
             << "Not Found" << endl;

        // wait for any key press
        cin.get();
        return -1;
    }

    return a.exec();
}
