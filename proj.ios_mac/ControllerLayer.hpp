//
//  Controller.hpp
//  HunterAndSnake
//
//  Created by zeyong shan on 7/7/17.
//
//

#ifndef Controller_hpp
#define Controller_hpp


class Controller: public cocos2d::Layer
{
public:
    CREATE_FUNC(Controller);
    virtual bool init();
private:
    void initListener();
    void initItems();
    void initScheduler();
    void initTouchBeginForDirectionController();
    void initTouchMovedForDirectionController();
    void initTouchEndedForDirectionController();
    void initScheduleToCheckTheMovementDirection();
    
    
    std::function<bool(cocos2d::Touch*, cocos2d::Event*)> begin;
    std::function<void(cocos2d::Touch*, cocos2d::Event*)> moved;
    std::function<void(cocos2d::Touch*, cocos2d::Event*)> ended;
    std::function<void(float)> scheduleToCheckTheMovementDirection;
    cocos2d::EventListenerTouchOneByOne* listener;
    cocos2d::Sprite* button;
    cocos2d::Point originalTouchPosition;
    cocos2d::Vec2 direction;
    std::mutex mutex;
};

#endif /* Controller_hpp */
