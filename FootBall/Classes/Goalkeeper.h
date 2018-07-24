//
//  Goalkeeper.hpp
//  FootBall
//  守门员
//

#ifndef Goalkeeper_hpp
#define Goalkeeper_hpp
#include "cocos2d.h"

class Goalkeeper : public cocos2d::Node{
public:
    static Goalkeeper* create(int teamId,cocos2d::Camera* camera = nullptr);
    virtual bool init(int teamId, cocos2d::Camera* camera);
    
};
#endif /* Goalkeeper_hpp */
