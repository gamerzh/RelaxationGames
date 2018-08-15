//
//  Hero.hpp
//  ShootEvil
//

#ifndef Hero_h
#define Hero_h

class Hero : public cocos2d::Sprite{
public:
    virtual bool init();
    CREATE_FUNC(Enemy);
//    bool onContactBegin(cocos2d::PhysicsContact& contact);
};
#endif /* Hero_h */
