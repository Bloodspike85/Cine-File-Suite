#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <QWidget>

#include "GAMES/Snake/snake.h"
#include "GAMES/Snake/fruit.h"

#include <QTimer>

class Snake_Game : public QWidget
{
    Q_OBJECT
public:
    explicit Snake_Game();

    void Game_update();
    void Game_draw();


    void paintEvent(QPaintEvent *Event);


    void keyPressEvent(QKeyEvent *Event);

public slots:

    void Tick();

private :

    QTimer Delta_time;

    snake *Player;
    fruit *Fruit;



};

#endif // SNAKE_GAME_H
