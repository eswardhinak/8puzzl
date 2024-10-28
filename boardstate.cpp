#include "boardstate.h"

BoardState::BoardState(std::vector<GameTilePixMapItem*> solution, std::vector<GameTilePixMapItem*> current) {
    this->current = current;
    this->solution = solution;
}

BoardState::BoardState() {}

// BoardState::BoardState() {


void BoardState::setSolution(std::vector<GameTilePixMapItem*> solution) {
    this->solution = solution;
}
void BoardState::setCurrent(std::vector<GameTilePixMapItem*> current) {
    this->current = current;
}

// bool BoardState::solutionReached() {

// }
bool BoardState::swap(int indexA, int indexB) {

    // need to make it so it swaps the correct index. indexB is always passed in as 8.

    QPointF tmp = solution[indexA]->pos();

    solution[indexA]->setPos(solution[indexB]->pos());
    solution[indexB]->setPos(tmp);

    GameTilePixMapItem* temp = current[indexA];
    current[indexA] = current[indexB];
    current[indexB] = temp;

    for (size_t i = 0; i < solution.size(); ++i) {
        std::cout << solution[i]->getInitialIndex() << " " << current[i]->getInitialIndex() << std::endl;
    }
    std::cout << std::endl;

    std::cout<< "address of solution: " << &solution << std::endl;
    std::cout<< "address of solution[0]: " << &solution[0] <<  "   address of solution[5]: " << &solution[5] << std::endl;
    std::cout <<"address of current: " << &current << std::endl;
    return true;
}
