#include "state/ShotState.h"
#include <iostream>

void ShotState::film(Shot*) {
    std::cout << "Invalid transition: film() is not allowed from this state." << std::endl;
}

void ShotState::submitForReview(Shot*) {
    std::cout << "Invalid transition: submitForReview() is not allowed from this state." << std::endl;
}

void ShotState::approve(Shot*) {
    std::cout << "Invalid transition: approve() is not allowed from this state." << std::endl;
}

void ShotState::reject(Shot*) {
    std::cout << "Invalid transition: reject() is not allowed from this state." << std::endl;
}
