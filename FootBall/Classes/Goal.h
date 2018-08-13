//
//  Goal.hpp
//  球门类
//

#ifndef Goal_h
#define Goal_h

class Goal : public cocos2d::Node{
public:
    virtual bool init();
    CREATE_FUNC(Goal);
    cocos2d::Rect getGoalRect(cocos2d::Vec2 dir);
private:
    cocos2d::Vec2 goalDirector;//球门方向,左球门(1,0),右球门(-1,0)
    cocos2d::Rect goalRect;//球门范围
};
#endif /* Goal_h */
