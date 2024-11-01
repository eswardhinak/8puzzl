#include "mainwindow.h"
#include <opencv2/opencv.hpp>
#include <QApplication>
#include <filesystem>
#include <QGraphicsView>
#include "multiimageclass.h"


using namespace cv;
using namespace std;
namespace fs = std::filesystem;

vector<Mat> sliceIntoNineSquares(Mat* imageMatrix)
{
    int rows = imageMatrix->rows;
    int cols = imageMatrix->cols;
    int cell_height = rows / 3;
    int cell_width = cols / 3;

    vector<Mat> puzzlePieces;
    puzzlePieces.reserve(9);

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
            cerr << "Usage: " << argv[0] << " <filepath>\n";
            return 1;
        }
        filepath = argv[1];

        if (!fs::exists(filepath)) {
            cerr << "Error: Path doesn't exist\n";
            return 1;
        }

        std::cout << "Full path: " << filepath << "\n";
    } catch (const std::exception& e) {
        cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    Mat image = imread(filepath.string());
    vector<Mat> puzzlePieces = sliceIntoNineSquares(&image);

    QApplication a(argc, argv); // needs to be instantiated before other Qt objects
    MultiImageClass canvas(900, 900);

    QGraphicsView * view = canvas.startGame(puzzlePieces);
    QMainWindow mainWindow;
    mainWindow.setCentralWidget(view);
    mainWindow.resize(SQUARE_LEN*3, SQUARE_LEN*3);
    mainWindow.show();

    canvas.getBoardState()->shuffle(31);

    // Error Handling
    if (image.empty()) {
        cerr << "Image File "
             << "Not Found" << endl;

        cin.get();
        return -1;
    }

    return a.exec();
}
