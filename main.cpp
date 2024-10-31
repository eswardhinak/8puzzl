#include "mainwindow.h"
#include <opencv2/opencv.hpp>
#include <QApplication>
#include <filesystem>
#include <QGraphicsView>
#include "multiimageclass.h"


using namespace cv;
using namespace std;
namespace fs = std::filesystem;


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
        }}
    return puzzlePieces;
}


int main(int argc, char *argv[]) {
    fs::path filepath;
    try {
        if (argc != 2) {
            std::cerr << "Usage: " << argv[0] << "<filepath>\n";
            return 1;
        }
        fs::path filepath = argv[1];

        if (!fs::exists(filepath)) {
            std::cerr << "Error: Path doesn't exist\n";
            return 1;
        }

        std::cout << "Full path: " << filepath << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    // Read the image file as
    // imread("default.jpg");
    QApplication a(argc, argv);

    Mat image = imread(filepath.string());
    cout << "Image type: " << image.type() << endl;
    cout << "Rows: " << image.rows << "\nCols: " << image.cols << endl;
    vector<Mat> puzzlePieces = sliceIntoNineSquares(&image);


    MultiImageClass canvas(900, 900);
    QGraphicsView * view = canvas.startGame(puzzlePieces);

    // Create a QMainWindow to contain the QGraphicsView
    QMainWindow mainWindow;
    mainWindow.setCentralWidget(view); // Set the QGraphicsView as the central widget
    mainWindow.resize(SQUARE_LEN*3, SQUARE_LEN*3); // Resize the window
    mainWindow.show(); // Show the window

    // shuffle
    canvas.getBoardState()->shuffle(31);

    // Error Handling
    // swars world
    if (image.empty()) {
        cout << "Image File "
             << "Not Found" << endl;

        // wait for any key press
        cin.get();
        return -1;
    }

    return a.exec();
}
