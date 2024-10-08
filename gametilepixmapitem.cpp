
#include "gametilepixmapitem.h"

GameTilePixMapItem::GameTilePixMapItem(const QPixmap &pixmap) : QGraphicsPixmapItem(pixmap) {
    setAcceptHoverEvents(true);
}

// Mouse press event
void GameTilePixMapItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    std::cout << "Mouse press" << std::endl;
    if (event->button() == Qt::LeftButton) {
        qDebug() << "Left mouse button clicked on the item!";
    } else if (event->button() == Qt::RightButton) {
        qDebug() << "Right mouse button clicked on the item!";
    }

    // Call base class handler if needed
    QGraphicsPixmapItem::mousePressEvent(event);
}

// Mouse release event
void GameTilePixMapItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    qDebug() << "Mouse button released!";
    QGraphicsPixmapItem::mouseReleaseEvent(event);
}

// Mouse move event
void GameTilePixMapItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    qDebug() << "Mouse moved over the item!";
    QGraphicsPixmapItem::mouseMoveEvent(event);
}

// Hover enter event
void GameTilePixMapItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    qDebug() << "Mouse entered the item!";
    QGraphicsPixmapItem::hoverEnterEvent(event);
}

// Hover leave event
void GameTilePixMapItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    qDebug() << "Mouse left the item!";
    QGraphicsPixmapItem::hoverLeaveEvent(event);
}
