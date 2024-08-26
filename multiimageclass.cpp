#include "multiimageclass.h"
#include <QPainter>

MultiImageClass::MultiImageClass(QWidget *parent) : QWidget(parent) {}

void MultiImageClass::setImages(const std::vector<cv::Mat>& images)
{
    m_images.clear();
    for (const auto& mat : images)
    {
        QImage qimg = matToQImage(mat);
        m_images.push_back(qimg);
    }
    update(); // Trigger a repaint
}

void MultiImageClass::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    int x = 0;
    int y = 0;
    int maxHeight = 0;

    for (const auto& img : m_images)
    {
        painter.drawImage(x, y, img);
        x += img.width() + 10; // Add some spacing between images
        maxHeight = std::max(maxHeight, img.height());

        // Move to next row if we're running out of width
        if (x + img.width() > width())
        {
            x = 0;
            y += maxHeight + 10; // Add some spacing between rows
            maxHeight = 0;
        }
    }
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
