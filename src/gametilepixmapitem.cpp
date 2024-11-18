#include "gametilepixmapitem.h"
#include "boardstate.h"

GameTilePixMapItem::GameTilePixMapItem(const QPixmap &pixmap, int initialIndex, BoardState * boardState) : QGraphicsPixmapItem(pixmap), boardState(boardState), initialIndex(initialIndex) {
    currentIndex = initialIndex;
    setAcceptHoverEvents(true);
}

// Mouse press event
void GameTilePixMapItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        boardState->swap(currentIndex);
    } else if (event->button() == Qt::RightButton) {}

    // Call base class handler if needed
    QGraphicsPixmapItem::mousePressEvent(event);
}

// Mouse release event
void GameTilePixMapItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsPixmapItem::mouseReleaseEvent(event);
}

// Mouse move event
void GameTilePixMapItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsPixmapItem::mouseMoveEvent(event);
}

// Hover enter event
void GameTilePixMapItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    QGraphicsPixmapItem::hoverEnterEvent(event);
}

// Hover leave event
void GameTilePixMapItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    QGraphicsPixmapItem::hoverLeaveEvent(event);
}

int GameTilePixMapItem::getCurrentIndex() {
    return currentIndex;
}

int GameTilePixMapItem::getInitialIndex() {
    return initialIndex;
}

void GameTilePixMapItem::setCurrentIndex(int currentIndex) {
    this->currentIndex = currentIndex;
}
