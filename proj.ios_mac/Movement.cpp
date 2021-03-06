//
//  Movement.cpp
//  HunterAndSnake
//
//  Created by zeyong shan on 7/9/17.
//
//

#include "Movement.hpp"
#include "BackgroundLayer.hpp"
#include "HunterLayer.hpp"
#include "Defines.h"
#include "InstructionQueue.hpp"
#include "DataBufferPool.hpp"
#include <math.h>
USING_NS_CC;

HunterStatus* Movement:: mainRoleStatus;
std::string   Movement:: id;
WebManager*   Movement:: webManager;

void Movement::init(Scene* gameScene)
{
    mainRoleStatus = HunterStatus::create(Point(16, 21), Vec2(0, 0));
    gameScene -> addChild(mainRoleStatus);
    webManager = WebManager::create();
    webManager -> signUpPosition([](std::string tid){
        log("the new position is: %s", tid.c_str());
        id = tid;
    }, [](){
        log("game start!!!!!");
    });
}

void Movement::moveHunter(Vec2 direction, Scene* gameScene)
{
    direction.x *=2;
    direction.y *=2;
    auto background = (BackgroundLayer*) gameScene -> getChildByTag(BACKGROUND_LAYER);
    auto hunter = (HunterLayer*) gameScene -> getChildByTag(HUNTER_LAYER);
    hunter -> setDirection(direction);
    
    if(((mainRoleStatus -> getPosition().x > 5674.5 && direction.x > 0)\
        ||(mainRoleStatus -> getPosition().x < 16 && direction.x < 0)))
    {
        direction.x = 0;
        if(direction.y > 0)
            direction.y = 30;
        else if(direction.y < 0)
            direction.y = -30;
        else
            direction.y = 0;
    }
    
    if((mainRoleStatus -> getPosition().y > 5809 && direction.y > 0)\
       || (mainRoleStatus -> getPosition().y < 21 && direction.y < 0))
    {
        direction.y = 0;
        if(direction.x > 0)
            direction.x = 30;
        else if(direction.x < 0)
            direction.x = -30;
        else
            direction.x = 0;
    }
    std::string inst = "1 ";
    std::string x_str = std::to_string(mainRoleStatus -> getPosition().x);
    std::string y_str = std::to_string(mainRoleStatus -> getPosition().y);
    inst += id + " " + x_str + " " + y_str;
  //  InstructionQueue::enqueue(inst);
    background -> move(Vec2(direction.x * -1 * 0.05, direction.y * -1 * 0.05));
    mainRoleStatus ->setDirection(direction);
    Point temp = mainRoleStatus -> getPosition();
    temp.add(Vec2(direction.x * 0.05, direction.y * 0.05));
    mainRoleStatus -> setPosition(temp);
}


void Movement::moveSnake(Vec2 direction, Scene* gameScene)
{
    auto background = (BackgroundLayer*) gameScene -> getChildByTag(BACKGROUND_LAYER);
    background -> move(Vec2(direction.x * -1 * 0.05, direction.y * -1 * 0.05));
}
//5693.348145, 5830.480957   Iphone 5
//5691.214355, 5809.899902   Iphone 7 Plus
//5680.570801, 5817.456543   Ipad Pro 12.9inch
//5674.5, 5809.29 --16, 21
