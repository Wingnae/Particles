#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include <SFML/Graphics.hpp>

class Particle {
	private:
		float x, y;
		float vX, vY;
		float dist;

	public:
		Particle();
		Particle(float xx, float yy);
		void pull(float& xx, float& yy, float acc, float& dt);
		void move(float& dt);
		float distance(float& xbis, float& ybis);
		float getX();
		float getY();
		float getVel();
		float getDist();
};

#endif

