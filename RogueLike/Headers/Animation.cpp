#include "Animation.h"

Animation AnimationManager::animations[(int)AnimationType::MAX_INDEX] = {};


void AnimationManager::Init()
{
    animations[(int)AnimationType::PlayerIdle] = { 24.0f,256,267 };
}

std::pair<uint32_t, TimePoint> AnimationManager::StartAnimation(AnimationType type)
{

    uint32_t texID = animations[(int)type].startID;
    TimePoint now = Time::CurrentTime();
    return {texID,now};
}

uint32_t AnimationManager::ContinueAnimation(AnimationType type, TimePoint startPoint)
{
    Animation& ani = animations[(int)type];
    const float idCount = ani.finID - ani.startID + 1;
    TimePoint now = Time::CurrentTime();
    Duration  dur = now - startPoint;
    float delta = dur.count();
    uint32_t retval = (uint32_t)std::fmod(delta * ani.speed, idCount);
    
    retval += ani.startID;
    return retval;
}

const Animation& AnimationManager::GetAnimation(AnimationType type)
{
    return animations[(int)type];
}
