#include "multiimageclass.h"
#include <QPainter>

MultiImageClass::MultiImageClass(int height, int width): scene(new QGraphicsScene(QRectF(0, 0, width, height))) {}

MultiImageClass::~MultiImageClass() {
    delete scene; // Clean up
}


QGraphicsView * MultiImageClass::setImages(const std::vector<cv::Mat>& images)
{
    int x = 0;
    int y = 0;
    int maxHeight = 0;

    // Define the size of the grid and the size of each square (cell)
    int gridRows = 3;
    int gridCols = 3;

    int cellWidth = 300;  // Width of each square
    int cellHeight = 300; // Height of each square

    m_images.clear();
    scene->clear();
    for (const auto& mat : images)
    {
        std::cerr << images.size();
        QImage qimg = matToQImage(mat);
        QImage scaledQImg = qimg.scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        m_images.push_back(scaledQImg);
        QGraphicsPixmapItem * pixmapItem = new QGraphicsPixmapItem(QPixmap::fromImage(scaledQImg));
        pixmapItem->setFlag(QGraphicsItem::ItemIsSelectable);
        scene->addItem(pixmapItem);
        std::cerr << x << " " << y << std::endl;
        pixmapItem->setPos(x,y);
        x += scaledQImg.width() + 10; // Add some spacing between images
        maxHeight = std::max(maxHeight, scaledQImg.height());
        if (x + scaledQImg.width() > scene->sceneRect().width()) {
            x = 0;
            y += maxHeight + 10; // Add some spacing between rows
            maxHeight = 0;
        }
    }
    std::cerr << "Hum";
    QGraphicsView * view = new QGraphicsView(scene);
    view->setRenderHint(QPainter::Antialiasing); // Optional: Improve rendering quality
    view->setMinimumSize(900, 900); // Set the minimum size of the view
    return view;
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
