#include "stdafx.h"
#include "particle.h"
#include "define.h"

using namespace sf;

Particle::Particle() {
	x = 0;
	y = 0;
	vX = 0;
	vY = 0;
	dist = 0;
}

Particle::Particle(float xx, float yy) {
	x = xx;
	y = yy;
	vX = 0;
	vY = 0;
	dist = 0;
}

void Particle::pull(float& xx, float& yy, float acc, float& dt) {
	dist = distance(xx, yy);

	vX += acc * (xx - x) / dist * dt;
	vY += acc * (yy - y) / dist * dt;
}

void Particle::move(float& dt) {
	int vel = getVel();
	if (vel > FRICTION) {
		vX *= (vel - FRICTION) / vel;
		vY *= (vel - FRICTION) / vel;
	}

	x += vX * dt;
	y += vY * dt;

	if (WALL_BOUNCE) {
		if (x < 0 || x >= W_WIDTH) {
			x -= vX;
			vX = -vX;
		}
		if (y < 0 || y >= W_HEIGHT) {
			y -= vY;
			vY = -vY;
		}
	}
}

float Particle::distance(float& xbis, float& ybis) {
	return sqrt(pow(x - xbis, 2) + pow(y - ybis, 2));
}

float Particle::getX() {
	return x;
}

float Particle::getY() {
	return y;
}

float Particle::getVel() {
	return abs(vX) + abs(vY);
}

float Particle::getDist() {
	return dist;
}