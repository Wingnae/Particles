#ifndef __CLOUD_H__
#define __CLOUD_H__

#include <SFML/Graphics.hpp>
#include "particle.h"

class Cloud {
	private:
		float x, y;
		sf::Uint8* pixels;
		sf::Uint8* post_prod;
		Particle* p;
		sf::Image img;
		sf::Texture txt;
		sf::Sprite sprt;

	public:
		Cloud();
		~Cloud();
		void main(sf::RenderWindow& win, bool mousePressed, sf::Vector2i& mPos, float& dt);
		void computeGravityCenter();
};

#endif