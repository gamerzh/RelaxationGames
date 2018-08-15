//
//  Enemy.hpp
//  ShootEvil
//   怪物的基类
//

#ifndef Enemy_h
#define Enemy_h

class Enemy : public cocos2d::Sprite{
public:
    virtual bool init();
    CREATE_FUNC(Enemy);
//    bool onContactBegin(cocos2d::PhysicsContact& contact);
    std::string getTextureName();
};
#endif /* Enemy_h */
