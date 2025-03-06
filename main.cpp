#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <math.h>

#define WIDTH 900
#define HEIGHT 600
#define WHITE 0xffffffff
#define YELLOW 0xffffff00
#define BLACK 0x00000000

class Circle {
	public: 
	double x;
	double y;
	double radius;
	void logCircleInfo() {
		printf("X: %f, Y: %f, Radius: %f\n", x, y, radius);
	}
};

void FillCircle(SDL_Surface* surface, struct Circle circle, Uint32 color) {
	double radiusSquared = pow(circle.radius, 2);
	for (double x=circle.x-circle.radius; x<=circle.x+circle.radius; x++) {
		for (double y=circle.y - circle.radius; y<=circle.y+circle.radius; y++) {
			double distanceSquared = pow(x-circle.x, 2) + pow(y-circle.y,2);
			if (distanceSquared < radiusSquared) {
				SDL_Rect pixel = (SDL_Rect) {(int) x,(int) y, 1, 1 };
				SDL_FillRect(surface, &pixel, color);
			}
		}
	}
}

bool collisionDetection(Circle circleA, Circle circleB) {
	if ((circleA.x - (circleA.radius + circleB.radius) < circleB.x &&
			circleA.x + (circleA.radius + circleB.radius) > circleB.x) &&
			circleA.y - (circleA.radius + circleB.radius) < circleB.y &&
			circleA.y + (circleA.radius + circleB.radius) > circleB.y){
		printf("true");
		return true;
	}
	printf("false");
	return false;
}

int main() {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("RayTracing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);

	SDL_Surface* surface = SDL_GetWindowSurface(window);

	struct Circle circle = { 200, 200, 80 };
	struct Circle shadowCircle { 650, 300, 140 };

	SDL_Rect eraseRect = (SDL_Rect) { 0, 0, WIDTH, HEIGHT };

	int isSimulationRunning = 1;
	SDL_Event event;

	while (isSimulationRunning) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				isSimulationRunning = 0;
			}
			if (event.motion.type == SDL_MOUSEMOTION && event.motion.state != 0) {
				circle.x = event.motion.x;
				circle.y = event.motion.y;
			}
		}

		SDL_FillRect(surface, &eraseRect, BLACK);
		FillCircle(surface, circle, YELLOW);
		FillCircle(surface, shadowCircle, WHITE);

		circle.logCircleInfo();
		shadowCircle.logCircleInfo();
		collisionDetection(shadowCircle, circle);

		SDL_UpdateWindowSurface(window);
		SDL_Delay(5);
	}
}

