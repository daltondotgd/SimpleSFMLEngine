#include "stdafx.h"
#include "AnimatedSprite.h"
#include "Engine.h"

#include <cassert>

AnimatedSprite::AnimatedSprite(const std::string & animationPath, const sf::Vector2f & position)
{
    setPosition(position);

    std::ifstream file("Resources/anims/" + animationPath + ".anim");

    if (file.is_open() && file.good())
    {
        std::string line;
        int widthDivs = 0;
        int heightDivs = 0;
        int frameWidth = 0;
        int frameHeight = 0;

        std::getline(file, line);

        std::string ext = ".png";
        auto textureName = line.substr(0, line.find_last_of(ext) - (ext.length() - 1));
        auto texture = Engine::getInstance().getTextureManager()[textureName];
        setTexture(texture, true);

        std::getline(file, line);
        std::istringstream iss(line);
        iss >> widthDivs >> heightDivs;

        frameWidth = texture->getSize().x / widthDivs;
        frameHeight = texture->getSize().y / heightDivs;

        while (file.good())
        {
            std::getline(file, line);
            if (!line.empty())
            {
                auto name = line;
                int miliseconds = 0;
                int start = 0;
                int end = 0;

                if (currentAnimation == "") currentAnimation = name;

                std::getline(file, line);
                iss = std::istringstream(line);
                iss >> miliseconds >> start >> end;

                Animation animation;

                for (int i = start; i <= end; ++i)
                {
                    int x = (i - 1) % widthDivs;
                    int y = (i - 1) / widthDivs;
                    Frame frame;
                    frame.rect.left = x * frameWidth;
                    frame.rect.top = y * frameHeight;
                    frame.rect.width = frameWidth;
                    frame.rect.height = frameHeight;

                    frame.miliseconds = miliseconds;
                    animation.push_back(frame);
                }

                animations[name] = animation;
            }
        }

        file.close();
        runAnimation(currentAnimation);
        setTextureRect(animations[currentAnimation][currentFrame].rect);
    }
}

void AnimatedSprite::runAnimation(std::string animationName, bool looping, bool doNotReset)
{
    playAnimation = true;
    currentAnimation = animationName;
    if (!doNotReset)
        resetAnimation();
    loop = looping;
}

void AnimatedSprite::runAnimaion()
{
    playAnimation = true;
    if (currentFrame == animations[currentAnimation].size() - 1 && !loop)
        resetAnimation();
}

void AnimatedSprite::toggleAnimation()
{
    playAnimation = !playAnimation;
    if (playAnimation && currentFrame == animations[currentAnimation].size() - 1 && !loop)
        resetAnimation();
}

void AnimatedSprite::stopAnimation()
{
    playAnimation = false;
}

void AnimatedSprite::resetAnimation()
{
    currentFrame = 0;
    currentFrameCounter = animations[currentAnimation][currentFrame].miliseconds;
}

void AnimatedSprite::nextFrame()
{
    ++currentFrame;
    if (currentFrame == animations[currentAnimation].size())
    {
        if (loop)
            currentFrame = 0;
        else
        {
            playAnimation = false;
            currentFrame = animations[currentAnimation].size() - 1;
        }
    }
    auto frame = animations[currentAnimation][currentFrame];
    setTextureRect(frame.rect);
    currentFrameCounter = frame.miliseconds;


    if (frameCallbacks.find(currentAnimation) != frameCallbacks.end())
    {
        auto inner = frameCallbacks[currentAnimation];
        if (inner.find(currentFrame) != inner.end())
            inner[currentFrame]();
    }
}

bool AnimatedSprite::isAnimationFinished()
{
    return currentFrame == animations[currentAnimation].size() - 1;
}

std::string AnimatedSprite::getCurrentAnimation()
{
    return currentAnimation;
}

int AnimatedSprite::getCurrentFrame()
{
    return currentFrame;
}

void AnimatedSprite::updateNode()
{
    if (playAnimation)
    {
        currentFrameCounter -= Engine::getInstance().deltaTime() * 1000;
        if (currentFrameCounter <= 0)
            nextFrame();
    }

    Sprite::updateNode();
}

void AnimatedSprite::registerFrameCallback(std::string animation, int frame, std::function<void()> callback)
{
    frameCallbacks[animation][frame - 1] = callback;
}
