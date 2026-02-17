#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Floor.h"


class Background
{
public:
	Background();
	void setFloorArray();
	void renderBackground(sf::RenderWindow& window);
		
	

private:
	Floor floorArray[10];
	const int floorSpacing = 64 * 2; // the spacing between each floor object, should be the width of the floor texture times its scale
};
