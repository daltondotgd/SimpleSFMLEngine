#pragma once

#include "Sprite.h"

class Frame
{
public:
    sf::IntRect rect;
    int miliseconds;
};
typedef std::vector<Frame> Animation;

class AnimatedSprite
    : public Sprite
{
public:
    AnimatedSprite(const std::string& animationPath, const sf::Vector2f& position = sf::Vector2f());

    void runAnimation(std::string animationName, bool looping = true, bool doNotReset = false);
    void runAnimaion();
    void toggleAnimation();
    void stopAnimation();
    void resetAnimation();
    void nextFrame();

    bool isAnimationFinished();
    std::string getCurrentAnimation();
    int getCurrentFrame();

    virtual void updateNode() override;

    void registerFrameCallback(std::string animation, int frame, std::function<void()> callback);

protected:
    std::map<std::string, Animation> animations;
    std::string currentAnimation;
    int currentFrame{ 0 };
    float currentFrameCounter{ 0 };
    bool loop{ true };
    bool playAnimation{ true };

    std::map<std::string, std::map<int, std::function<void()>>> frameCallbacks;
};