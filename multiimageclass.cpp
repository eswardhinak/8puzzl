#include "multiimageclass.h"
#include "boardstate.h"
#include <QPainter>

MultiImageClass::MultiImageClass(int height, int width):
    scene(new QGraphicsScene(QRectF(0, 0, width, height))) {

}

MultiImageClass::~MultiImageClass() {
    delete scene; // Clean up
}

QGraphicsView * MultiImageClass::startGame(const std::vector<cv::Mat>& images)
{
    int x = 0;
    int y = 0;
    int maxHeight = 0;

    scene->clear();

    for (size_t i = 0; i < images.size()-1; ++i)
    {
        const auto& mat = images[i];
        QImage qimg = matToQImage(mat);
        QImage scaledQImg = qimg.scaled(SQUARE_LEN, SQUARE_LEN, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        GameTilePixMapItem * pixmapItem = new GameTilePixMapItem(QPixmap::fromImage(scaledQImg), i);
        solution.push_back(pixmapItem);	// store the pixmap

        pixmapItem->setFlag(QGraphicsItem::ItemIsSelectable);
        scene->addItem(pixmapItem);
        pixmapItem->setPos(x,y);

        // Add spacing and update locations
        x += scaledQImg.width() + PADDING;
        maxHeight = std::max(maxHeight, scaledQImg.height());
        if (x + scaledQImg.width() > scene->sceneRect().width()) {
            x = 0;
            y += maxHeight + PADDING; // Add spacing and update locations
            maxHeight = 0;
        }
    }
    solution.push_back(nullptr);
    BoardState * boardState = new BoardState(solution, solution);

    QGraphicsView * view = new QGraphicsView(scene);
    view->setRenderHint(QPainter::Antialiasing); // Improve rendering quality
    view->setMinimumSize(900, 900); // Set the minimum size of the view
    return view;
}

void MultiImageClass::swap(int idx_old, int idx_new) {
    int x_old = idx_old % 3;
    int y_old = idx_old / 3;
    int x = idx_new % 3;
    int y = idx_new / 3;
    x_old = x_old == 0 ? x_old : x_old + PADDING;
    y_old = y_old == 0 ? y_old : y_old + PADDING;
    x = x == 0 ? x : x + PADDING;
    y = y == 0 ? y : y + PADDING;
    solution.at(idx_old)->setPos(x*SQUARE_LEN, y*SQUARE_LEN);
    solution.at(idx_new)->setPos(x_old*SQUARE_LEN, y_old*SQUARE_LEN);
}


QImage MultiImageClass::matToQImage(const cv::Mat& mat)
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

