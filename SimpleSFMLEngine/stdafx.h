// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#define _USE_MATH_DEFINES
#include <cmath>

#include "targetver.h"

#include <SFML/Audio.hpp>
#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/Network.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>

#define RAD(deg) (deg * M_PI / 180.0)
#define DEG(rad) (rad * 180.0 / M_PI)

#ifdef _DEBUG
#define LOG(msg) std::cout << msg << std::endl
#define LOGV(var) std::cout << #var << ": " << var << std::endl
#else
#define LOG(msg) 0
#define LOGV(var) 0
#endif

// TODO: reference additional headers your program requires here
