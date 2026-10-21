#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>

using namespace std;
using namespace sf;
using namespace sfp;

int main()
{
	//create window and world with gravity 0,1
	RenderWindow window(VideoMode(800, 600), "Bounce");
	World world(Vector2f(0, 1));

	//create the ball
	PhysicsCircle ball;
	ball.setCenter(Vector2f(400, 100));
	ball.setRadius(20);
	world.AddPhysicsBody(ball);

	//create floor
	PhysicsRectangle floor;
	floor.setSize(Vector2f(800, 20));
	floor.setCenter(Vector2f(400, 590));
	floor.setStatic(true);
	world.AddPhysicsBody(floor);

	//create ceiling
	PhysicsRectangle ceiling;
	ceiling.setSize(Vector2f(800, 20));
	ceiling.setCenter(Vector2f(400, 10));
	ceiling.setStatic(true);
	world.AddPhysicsBody(ceiling);

	//create left wall
	PhysicsRectangle leftWall;
	leftWall.setSize(Vector2f(20, 600));
	leftWall.setCenter(Vector2f(10, 300));
	leftWall.setStatic(true);
	world.AddPhysicsBody(leftWall);

	//create right wall
	PhysicsRectangle rightWall;
	rightWall.setSize(Vector2f(20, 600));
	rightWall.setCenter(Vector2f(790, 300));
	rightWall.setStatic(true);
	world.AddPhysicsBody(rightWall);

	//create center box
	PhysicsRectangle centerBox;
	centerBox.setSize(Vector2f(50, 50));
	centerBox.setCenter(Vector2f(400, 300));
	centerBox.setStatic(true);
	world.AddPhysicsBody(centerBox);

	//each time the ball collides with the floor, print "thud" to the console
	int thudCount(0);
	floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
		};

	//each time the ball collides with the center box, print "bang" to the console
	int bangCount(0);
	centerBox.onCollision = [&bangCount](PhysicsBodyCollisionResult result) {
		cout << "bang " << bangCount << endl;
		bangCount++;
			if (bangCount == 3) {
				cout << "bang count reached 3" << endl;
				exit(0);
			}
		};

	Clock clock;
	Time lastTime(clock.getElapsedTime());
	while (true) {
		//calculate MS since last frame and update physics
		Time currentTime(clock.getElapsedTime());
		Time deltaTime(currentTime - lastTime);
		int deltaTimeMS(deltaTime.asMilliseconds());
		if (deltaTimeMS > 0)
		{
			world.UpdatePhysics(deltaTimeMS);
			lastTime = currentTime;
		}
		//draws walls and ball in window
		window.clear(Color(0, 0, 0));
		window.draw(ball);
		window.draw(floor);
		window.draw(ceiling);
		window.draw(leftWall);
		window.draw(rightWall);
		window.draw(centerBox);
		window.display();
	}

	ball.applyImpulse(Vector2f(0, -1000));

}
