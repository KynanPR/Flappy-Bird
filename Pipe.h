#pragma once
#include "GameObject.h"

static const std::string PIPE_TEX_PATH = "assets/Tiles/Style 1/LongerPipe.png";
static const sf::Vector2i PIPE_TEX_SIZE = { 32, 360 };

class Pipe : public GameObject
{
public:
	Pipe(bool isDownFacing = false);
};

