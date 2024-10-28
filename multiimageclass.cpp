#include "multiimageclass.h"
#include "boardstate.h"
#include <QPainter>
#include <QPointF>

MultiImageClass::MultiImageClass(int height, int width):
    scene(new QGraphicsScene(QRectF(0, 0, width, height))) {

}

MultiImageClass::~MultiImageClass() {
    delete scene; // Clean up
}

QPixmap MultiImageClass::createEmptyItem(int width, int height) {
    // Step 1: Create a white QPixmap
    QPixmap whitePixmap = QPixmap(width, height);
    whitePixmap.fill(Qt::white);  // Fill with white color
    return whitePixmap;
}
QGraphicsView * MultiImageClass::startGame(const std::vector<cv::Mat>& images)
{
    int x = 0;
    int y = 0;
    int maxHeight = 0;

    int width = 0;
    int height = 0;

    scene->clear();

    for (size_t i = 0; i < images.size(); ++i)
    {
        GameTilePixMapItem * pixmapItem = nullptr;

        if (i < images.size()-1){
            const auto& mat = images[i];
            QImage qimg = matToQImage(mat);
            QImage scaledQImg = qimg.scaled(SQUARE_LEN, SQUARE_LEN, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            if (i == 0) {
                width = scaledQImg.width();
                height = scaledQImg.height();
            }
            std::cout << scaledQImg.width() << " " << scaledQImg.height() << std::endl;
            pixmapItem = new GameTilePixMapItem(QPixmap::fromImage(scaledQImg), i);
        } else {
            pixmapItem = new GameTilePixMapItem(this->createEmptyItem(width, height), images.size()-1);
        }
        solution.push_back(pixmapItem);	// store the pixmap

        pixmapItem->setFlag(QGraphicsItem::ItemIsSelectable);
        scene->addItem(pixmapItem);
        pixmapItem->setPos(x,y);


        x += width + PADDING;
        maxHeight = std::max(maxHeight,height);
        if (x + width > scene->sceneRect().width()) {
            x = 0;
            y += maxHeight + PADDING; // Add spacing and update locations
            maxHeight = 0;
        }
    }
    BoardState * boardState = new BoardState(solution, solution);

    QGraphicsView * view = new QGraphicsView(scene);
    view->setRenderHint(QPainter::Antialiasing); // Improve rendering quality
    view->setMinimumSize(900, 900); // Set the minimum size of the view
    return view;
}

void MultiImageClass::swap(int idx_old, int idx_new)
{

    QPointF tmp = solution[idx_old]->pos();

    solution[idx_old]->setPos(solution[idx_new]->pos());
    solution[idx_new]->setPos(tmp);
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

