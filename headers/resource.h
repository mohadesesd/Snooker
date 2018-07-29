//
// Created by msd on 7/18/18.
//

#ifndef BILLIARD_RESOURCE_H
#define BILLIARD_RESOURCE_H

#include "game.h"
#include <string>

class Resource {
public:
    explicit Resource(Game *game);

    void set(std::string);

    std::string get();

private:
    Game *game;

};


#endif //BILLIARD_RESOURCE_H
