#pragma once

#include "Text.h"

class FPSCounter :
    public Text
{
public:
    FPSCounter(int frameRateLimit, std::string fontName = "04B_03__");
    
    virtual void init() override;
    virtual void update() override;

};

