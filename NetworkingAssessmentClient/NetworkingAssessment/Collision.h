#pragma once
#include "SFML\Graphics.hpp"
#include "GameSprite.h"


// Static class provide collision detection functions.
class Collision
{
public:
	//AABB
	static bool checkBoundingBox(GameSprite* sp1, GameSprite* sp2);
	// Bounding circle
	static bool checkBoundingSphere(GameSprite* sp1, GameSprite* sp2);

	static const bool top = true;
	static const bool bottom = true;
	static const bool left = true;
	static const bool right = true;



};