#include "stdafx.h"
#include <omp.h>
#include "define.h"
#include "cloud.h"

using namespace sf;

Cloud::Cloud() {
	x = 0;
	y = 0;

	p = new Particle[CLOUD_SIZE];

	float originX = W_WIDTH / 2 - CLOUD_W / 2;
	float originY = W_HEIGHT / 2 - CLOUD_H / 2;

	#pragma omp parallel for
	for (int i = 0; i < CLOUD_SIZE; i++) {
		p[i] = Particle((float)(originX + i % SIDE * CLOUD_W / SIDE), (float)(originY + i / SIDE * CLOUD_H / SIDE));
	}

	pixels = new Uint8[W_WIDTH * W_HEIGHT * 4];
	post_prod = new Uint8[W_WIDTH * W_HEIGHT * 4];
	img.create(W_WIDTH, W_HEIGHT, pixels);
	txt.loadFromImage(img);
	sprt.setTexture(txt);
}

Cloud::~Cloud() {
	delete pixels;
	delete p;
}

void Cloud::main(RenderWindow& win, bool mousePressed, sf::Vector2i& mPos, float& dt) {
	float mPosX = (float)mPos.x;
	float mPosY = (float)mPos.y;

	memset(pixels, 0, W_WIDTH * W_HEIGHT * 4 * sizeof(*pixels));
	computeGravityCenter();



	#pragma omp parallel for
	for (int i = 0; i < CLOUD_SIZE; i++) {
		if (mousePressed)
			p[i].pull(mPosX, mPosY, ACC, dt);
		
		p[i].pull(x, y, CLOUD_ACC, dt);
		p[i].move(dt);

		int px = (int)p[i].getX();
		int py = (int)p[i].getY();

		if (px >= 0 && py >= 0 && px < W_WIDTH && py < W_HEIGHT) {
			int index = 4 * ((int)p[i].getX() + W_WIDTH * (int)p[i].getY());
			if(pixels[index] == 0)
				pixels[index] = 75;
			else if(pixels[index] < 200 - COLOR)
				pixels[index] += COLOR;

			if (pixels[index + 1] < 170 - COLOR)
				pixels[index + 1] += COLOR;
			//pixels[index + 2] = 200;

			if (pixels[index + 3] == 0)
				pixels[index + 3] = 50;
			if (pixels[index + 3] < 225 - OPACITY)
				pixels[index + 3] += OPACITY;
		}
	}

	img.create(W_WIDTH, W_HEIGHT, pixels);
	txt.loadFromImage(img);
	sprt.setTexture(txt);
	win.draw(sprt);
}

void Cloud::computeGravityCenter() {
	x = 0;
	y = 0;
	for (int i = 0; i < CLOUD_SIZE; i++) {
		x += p[i].getX();
		y += p[i].getY();
	}
	x /= CLOUD_SIZE;
	y /= CLOUD_SIZE;
}