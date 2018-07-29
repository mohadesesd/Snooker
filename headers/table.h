//
// Created by msd on 7/18/18.
//

#ifndef BILLIARD_TABLE_H
#define BILLIARD_TABLE_H

#include "game.h"
#include "ball.h"
#include "hole.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Table {
public:
    Table(sf::RenderWindow *window, Game *game);

    Table(Game *game);

    int get_flag();

    void set_flag(int i);


private:
    int flag = 0;
};
#endif //BILLIARD_TABLE_H