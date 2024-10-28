#include <cmath>
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

bool BoardState::swap(int index) {
    std::cout<<"Current Index: " << index << ", Whitespace index: "  << whiteSpaceIndex << std::endl;
    // need to make it so it swaps the correct index. indexB is always passed in as 8.
    if (index == whiteSpaceIndex) {
        return false;
    }

    auto tmp = current[index];

    int index_x = index / 3;
    int index_y = index % 3;
    int whitespace_x = whiteSpaceIndex / 3;
    int whitespace_y = whiteSpaceIndex % 3;

    std::cout << index_x << " "  << index_y << " " <<  whitespace_x << " " << whitespace_y << std::endl;

    if (abs(index_x - whitespace_x) + abs(index_y - whitespace_y) == 1) {
        std::cout << "Valid move" << std::endl;

        QPointF tmp = current[index]->pos();
        current[index]->setPos(current[whiteSpaceIndex]->pos());
        current[whiteSpaceIndex]->setPos(tmp);

        int temp_current_index = current[index]->getCurrentIndex();
        current[index]->setCurrentIndex(whiteSpaceIndex);
        current[whiteSpaceIndex]->setCurrentIndex(temp_current_index);


        GameTilePixMapItem* temp = current[index];
        current[index] = current[whiteSpaceIndex];
        current[whiteSpaceIndex] = temp;

        std::cout<<whiteSpaceIndex<<std::endl;
        whiteSpaceIndex = index;

    }
    else {
        std::cout << "Not valid move." << std::endl;
    }


    // for (size_t i = 0; i < solution.size(); ++i) {
    //     std::cout << solution[i]->getInitialIndex() << " " << current[i]->getInitialIndex() << std::endl;
    // }
    // std::cout << std::endl;

    // std::cout<< "address of solution: " << &solution << std::endl;
    // std::cout<< "address of solution[0]: " << &solution[0] <<  "   address of solution[5]: " << &solution[5] << std::endl;
    // std::cout <<"address of current: " << &current << std::endl;

}
