#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>

int main()
{
	RenderWindow window(VideoMode(800, 600), "Bounce");
	World world(Vector2f(0, 1));

	PhysicsCircle ball;
	ball.setCenter(Vector2f(400, 300));
	ball.setRadius(20);
	world.AddPhysicsBody(ball);

	PhysicsRectangle floor;
	floor.setSize(Vector2f(800, 20));
	floor.setCenter(Vector2f(400, 590));
	floor.setStatic(true);
	world.AddPhysicsBody(floor);

	int thudCount(0);
	floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
		};
	Clock clock;
	Time lastTime(clock.getElapsedTime());
	while (true) {
		Time currentTime(clock.getElapsedTime());
		Time deltaTime(currentTime - lastTime);
		int deltaTimeMS(deltaTime.asMilliseconds());
		if (deltaTimeMS > 0)
		{
			world.UpdatePhysics(deltaTimeMS);
			lastTime = currentTime;
		}
		window.clear(Color(0, 0, 0));
		window.draw(ball);
		window.draw(floor);
		window.display();
	}

}
