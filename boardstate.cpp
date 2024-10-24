#include "boardstate.h"

BoardState::BoardState(std::vector<GameTilePixMapItem*> solution, std::vector<GameTilePixMapItem*> current) {
    this->current = current;
    this->solution = solution;
}
// BoardState::BoardState() {

// }
void BoardState::setSolution(std::vector<GameTilePixMapItem*> solution) {
    this->solution = solution;
}
void BoardState::setCurrent(std::vector<GameTilePixMapItem*> current) {
    this->current = current;
}
