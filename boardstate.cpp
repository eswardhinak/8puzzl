#include <cmath>
#include <utility>
#include "boardstate.h"
#include <random>


BoardState::BoardState(std::vector<GameTilePixMapItem*> solution, std::vector<GameTilePixMapItem*> current) {
    this->current = current;
    this->solution = solution;
}

BoardState::~BoardState() {
    // delete all gamepix items and delete current and solution
}

BoardState::BoardState() {}


void BoardState::setSolution(std::vector<GameTilePixMapItem*> solution) {
    this->solution = solution;
}
void BoardState::setCurrent(std::vector<GameTilePixMapItem*> current) {
    this->current = current;
}

bool BoardState::solutionReached() {
    for (int i = 0; i < solution.size(); i++) {
        if (solution.at(i)->getCurrentIndex() != i) {
            return false;
        }
    }
    return true;
}

int BoardState::getShuffleIndex() {
    int whitespace_x = whiteSpaceIndex / 3;
    int whitespace_y = whiteSpaceIndex % 3;
    std::cout<<"We out here"<<std::endl;
    std::vector<int> valid_shuffles;
    for (int i = 0; i < this->current.size(); i++) {
        int index_x = i / 3;
        int index_y = i % 3;
        if (abs(index_x - whitespace_x) + abs(index_y - whitespace_y) == 1) {
            valid_shuffles.push_back(i);
        }
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, valid_shuffles.size()-1);  // Range: [1, 100]
    int random_number = distrib(gen);

    std::cout<<"Valid shuffles size: " << valid_shuffles.size();
    std::cout<<"Random: "<<random_number<<std::endl;

    return valid_shuffles.at(random_number);
}

void BoardState::shuffle(int moves) {
    if (moves < 0) {
        throw std::runtime_error("Negative number of moves not allowed in shuffle");
    }
    for (int i = 0; i < moves; i++) {
        this->swap(this->getShuffleIndex(), false);
    }
}

void BoardState::setHiddenTile(QPixmap hiddenTile) {
    this->hiddenTile = hiddenTile;
}

void BoardState::placeHiddenTileIfGameOver() {
    if (this->solutionReached()) {
        current.at(whiteSpaceIndex)->setPixmap(this->hiddenTile);
        whiteSpaceIndex = -100; // hacky, sets this to a really high negative value so nothing can be swapped
    }
}

bool BoardState::swap(int index, bool checkSolution) {
    std::cout<<"Current Index: " << index << ", Whitespace index: "  << whiteSpaceIndex << std::endl;
    // need to make it so it swaps the correct index. indexB is always passed in as 8.


    if (whiteSpaceIndex < 0) {
        //hacky to stop swapping after game over
        return false;
    }
    if (index == whiteSpaceIndex) {
        return false;
    }


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
    if (checkSolution){
        placeHiddenTileIfGameOver();
    }
    return true;
}

bool BoardState::swap(int index) {
    return this->swap(index, true);
}
