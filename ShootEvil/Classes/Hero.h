//
//  Hero.hpp
//  ShootEvil
//

#ifndef Hero_h
#define Hero_h
#include "Bullet.h"

class Hero : public cocos2d::Sprite{
public:
    enum Direction{
        null,
        left,
        right
    };
    virtual bool init();
    CREATE_FUNC(Hero);
    void controlHero(bool move,Direction dir);
private:
    Direction moveDir;
    bool isMoveing;
    void update(float dt);
};
#endif /* Hero_h */
