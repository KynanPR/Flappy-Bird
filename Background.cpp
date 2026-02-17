#include "Background.h"

Background::Background()
{
	setFloorArray();
}

void Background::setFloorArray()
{
	sf::Vector2f floorPosition = { 64, static_cast<float>(WINDOW_HEIGHT - floorArray[0].getFloorTexRect().height)};
	for (Floor &floor : floorArray)
	{
		floor.SetPosition(floorPosition);
		floorPosition.x += floorSpacing;

	}
}

void Background::renderBackground(sf::RenderWindow& window)
{
	for (Floor &floor : floorArray)
	{
		floor.render(window);
	}
}
