//
//  Bullet.hpp
//  ShootEvil
//
//  Created by gamerzh on 2018/8/16.
//

#ifndef Bullet_hpp
#define Bullet_hpp
class Bullet : public cocos2d::Sprite{
public:
    virtual bool init();
    CREATE_FUNC(Bullet);
private:
    void update(float dt);
};
#endif /* Bullet_hpp */
