#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

static const std::string floorTexPath = "assets/Tiles/Style 1/SimpleStyle1.png";

class Floor : public GameObject
{
public:
	Floor();
	sf::IntRect getFloorTexRect() { return floorTexRect; }

private:
	const sf::IntRect floorTexRect = { 0, 80, 64, 32 };

};

