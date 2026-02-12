#pragma once
#include "GameObject.h"

static const std::string PIPE_TEX_PATH = "assets/Tiles/Style 1/PipeStyle1.png";
static const sf::Vector2i PIPE_TEX_SIZE = { 32, 64 };

class Pipe : public GameObject
{
public:
	Pipe(bool isDownFacing = false);
};

