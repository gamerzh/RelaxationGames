//
//  Enemy.hpp
//  ShootEvil
//   怪物的基类
//

#ifndef Enemy_h
#define Enemy_h

class Enemy : public cocos2d::Node{
public:
    virtual bool init();
    CREATE_FUNC(Enemy);
};
#endif /* Enemy_h */
