#include "boardstate.h"

BoardState::BoardState(std::vector<GameTilePixMapItem*> solution, std::vector<GameTilePixMapItem*> current) {
    this->current = current;
    this->solution = solution;
}
// BoardState::BoardState() {


void BoardState::setSolution(std::vector<GameTilePixMapItem*> solution) {
    this->solution = solution;
}
void BoardState::setCurrent(std::vector<GameTilePixMapItem*> current) {
    this->current = current;
}

void BoardState::swap(int indexA, int indexB) {
    QPointF tmp = solution[indexA]->pos();

    solution[indexA]->setPos(solution[indexB]->pos());
    solution[indexB]->setPos(tmp);

    GameTilePixMapItem* temp = current[indexA];
    current[indexA] = current[indexB];
    current[indexB] = temp;
}
