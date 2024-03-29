// platform game.....
//

#include "stdafx.h"

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h> 
#include <time.h> 
class Player
{
public:
	sf::RectangleShape shape;
	sf::Vector2f velocity;
	sf::Vector2f lookDirection;
	int waitToFireCounter;
	float angle = 0.0f;
	float speed = 8;
	sf::RectangleShape topBit;
	 float friction = -1.0;

	Player();

};

Player::Player()
{
	shape.setSize(sf::Vector2f(10, 10));
	shape.setPosition(160, -20);
	float velocityX = 0, velocityY = 0, gravity = 0.3;
	int maxSpeed = 10;

	waitToFireCounter = 10;
	velocity = { 0,0 };
	lookDirection = { 0,-1 };

	shape.setOrigin(7.5, 2.5);

	shape.setSize(sf::Vector2f(20, 10));
	shape.setFillColor(sf::Color::Magenta);
	shape.setPosition(rand() % 780, rand() % 580);

	topBit.setSize(sf::Vector2f(5, 5));
	topBit.setFillColor(sf::Color::Cyan);
}

class Bullet
{
public:
	sf::RectangleShape shape;
	sf::Vector2f velocity;


};
class Apple
{
public:
	sf::RectangleShape shape;
	int health = 3;
};
int main()
{



	//create Window
	sf::RenderWindow window(sf::VideoMode(800, 600), "platform game");
	//do this once to "seed" the random number generator
	srand(time(NULL));
	sf::View view = window.getDefaultView();
	float randomNum;

	const int numOfApples = 10;
	Apple apples[numOfApples];
	Player player;
	Player playerTwo;

	playerTwo.shape.setFillColor(sf::Color::Blue);

	sf::Sprite backgroundSprite;
	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("ASSETS/IMAGES/grass.png"))
	{
		std::cout << "error with grass image file";
	}
	backgroundSprite.setTexture(backgroundTexture);

	sf::Sprite trackSprite;
	sf::Texture trackTexture;
	if (!trackTexture.loadFromFile("ASSETS/IMAGES/track.png"))
	{
		std::cout << "error with grass image file";
	}
	trackSprite.setTexture(trackTexture);
	

	
	

	const int numBullets = 10;

	sf::RectangleShape onScreenArea;
	onScreenArea.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));

	Bullet bullets[numBullets];
	for (int i = 0; i < numBullets; i++)
	{
		bullets[i].shape.setSize(sf::Vector2f(10, 10));
		bullets[i].shape.setPosition(-2000, -2000);
		bullets[i].shape.setFillColor(sf::Color::Yellow);

		bullets[i].velocity.x = 0;
		bullets[i].velocity.y = 0;
	}


	for (int i = 0; i < numOfApples; i++)
	{
		apples[i].shape.setSize(sf::Vector2f(20, 20));
		apples[i].shape.setPosition(rand() % 780, rand() % 580);
		apples[i].shape.setFillColor(sf::Color::Blue);
	}

	
	bool rotatingView = false;
	randomNum = rand() % 750 + 0;
	const int numRows = 15;
	const int numCols = 20;
	int levelData[numRows][numCols] = {
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0 },
	{ 0,0,1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0 },
	{ 0,1,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0 },
	{ 0,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0 },
	{ 0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0 },
	{ 0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0 },
	{ 0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0 },
	{ 0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0 },
	{ 0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0 },
	{ 0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0 },
	{ 0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 } };

	sf::Sprite level[numRows][numCols]; //rectangle shape
	sf::Vector2f vector{ -32,-32 };
	for (int row = 0; row < numRows; row++)
	{
		vector.x = -16;
		for (int col = 0; col < numCols; col++)
		{
			std::cout << levelData[row][col];
			level[row][col].setPosition(vector.x+16,vector.y + 16
			);
			vector.x += 32;
			if (levelData[row][col] == 1)
			{

				level[row][col].setTexture(trackTexture);
			}
			if (levelData[row][col] == 0)
			{
				level[row][col].setTexture(backgroundTexture);

			}

		}
		vector.y += 23;
		std::cout << std::endl;
	}


	// set timePerFrame to 1 60th of a second. 60 frames per second

	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);


	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	// the clock object keeps the time.
	sf::Clock clock;

	clock.restart();

	while (window.isOpen())
	{
		// check if the close window button is clicked on.
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//add to the time since last update and restart the clock
		timeSinceLastUpdate += clock.restart();

		//update every 60th of a second
		//only when the time since last update is greater than 1/60 update the world.

		if (timeSinceLastUpdate > timePerFrame)
		{


			// get keyboard input.

			// get keyboard input.
			for (int i = 0; i < 2; i++)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					//player.angle = player.shape.getRotation() * (3.14159 / 100);
					player.angle -= .1;

				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				{
					player.angle += .1;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				{
					//player.velocity.y = -5;
					player.shape.move(player.velocity);
					player.topBit.move(player.velocity);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
					player.shape.move(-player.velocity);
					player.topBit.move(-player.velocity);

				}
				for (int row = 0; row < numRows; row++)
				{
					for (int col = 0; col < numCols; col++)
					{
						if (levelData[row][col] == 0)
						{
							if (player.shape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
							{
								player.friction = { 1.0 };

								break;
							}
						}
						
						if (levelData[row][col] == 0)
						{
							if (playerTwo.shape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
							{

								playerTwo.friction = { 1.0 };

								break;
							}
						}
						else
						{
							playerTwo.speed = 8;
						}
					}
				}

				player.velocity *= player.friction;
				playerTwo.velocity *= playerTwo.friction;

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					//player.angle = player.shape.getRotation() * (3.14159 / 100);
					playerTwo.angle -= .1;

				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					playerTwo.angle += .1;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					//player.velocity.y = -5;
					playerTwo.shape.move(playerTwo.velocity);
					playerTwo.topBit.move(playerTwo.velocity);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					playerTwo.shape.move(-playerTwo.velocity);
					playerTwo.topBit.move(-playerTwo.velocity);

				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					if (player.waitToFireCounter == 0)
					{
						for (int i = 0; i < numBullets; i++)
						{
							if (bullets[i].shape.getPosition().x == -2000)
							{
								bullets[i].shape.setPosition(player.topBit.getPosition());
								bullets[i].velocity = player.velocity;
								bullets[i].velocity.x *= 2;
								bullets[i].velocity.y *= 2;

								player.waitToFireCounter = 10;
								break;
							}

						}
					}

				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
				{
					if (playerTwo.waitToFireCounter == 0)
					{
						for (int i = 0; i < numBullets; i++)
						{
							if (bullets[i].shape.getPosition().x == -2000)
							{
								bullets[i].shape.setPosition(playerTwo.topBit.getPosition());
								bullets[i].velocity = playerTwo.velocity;
								bullets[i].velocity.x *= 2;
								bullets[i].velocity.y *= 2;

								playerTwo.waitToFireCounter = 10;
								break;
							}

						}
					}

				}

				player.topBit.setPosition(player.shape.getPosition());

				player.lookDirection.x = cos(player.angle);
				player.lookDirection.y = sin(player.angle);

				player.velocity = player.lookDirection * 3.0f;


				player.shape.setRotation(player.angle * (180 / 3.14159));
				player.topBit.setRotation(player.angle * (180 / 3.14159));
				player.velocity *= player.friction;

				playerTwo.topBit.setPosition(playerTwo.shape.getPosition());

				playerTwo.lookDirection.x = cos(playerTwo.angle);
				playerTwo.lookDirection.y = sin(playerTwo.angle);

				playerTwo.velocity = playerTwo.lookDirection * 3.0f;
				playerTwo.velocity *= playerTwo.friction;


				playerTwo.shape.setRotation(playerTwo.angle * (180 / 3.14159));
				playerTwo.topBit.setRotation(playerTwo.angle * (180 / 3.14159));

				for (int i = 0; i < numBullets; i++)
				{
					if (bullets[i].shape.getPosition().x != -2000)
					{
						bullets[i].shape.move(bullets[i].velocity);
						if (!onScreenArea.getGlobalBounds().intersects(bullets[i].shape.getGlobalBounds()))
						{
							bullets[i].shape.setPosition(-2000, -2000);
							bullets[i].velocity.x = 0;
							bullets[i].velocity.y = 0;


						}
					}
				}



				if (player.waitToFireCounter > 0)
				{
					player.waitToFireCounter--;

				}
				if (playerTwo.waitToFireCounter > 0)
				{
					playerTwo.waitToFireCounter--;

				}
			}
			for (int i = 0; i < numOfApples; i++)
			{
				if (apples[i].shape.getPosition().x != -1000)
				{
					apples[i].shape.move(rand() % 7 - 3, rand() % 7 - 3);
				}
			}

			//collision detection
			for (int appleIndex = 0; appleIndex < numOfApples; appleIndex++)
			{
				if (apples[appleIndex].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
				{

					apples[appleIndex].shape.setPosition(-1000, -1000);
				}
				for (int bulletIndex = 0; bulletIndex < numBullets; bulletIndex++)
				{
					if (apples[appleIndex].shape.getGlobalBounds().intersects(bullets[bulletIndex].shape.getGlobalBounds()))
					{
						apples[appleIndex].health--;
						if (apples[appleIndex].health <= 0)
						{
							apples[appleIndex].shape.setPosition(-1000, -1000);
						}
						bullets[bulletIndex].shape.setPosition(-2000, -2000);
						bullets[bulletIndex].velocity.x = 0;
						bullets[bulletIndex].velocity.y = 0;
						//score++;

					}
				}


			}

			

			//velocityY = velocityY + gravity;
			//player.shape.move(0, velocityY);


			/*gravity = 0.3;
			if (velocityY >= 0)
			{
				for (int row = 0; row < numRows; row++)
				{
					for (int col = 0; col < numCols; col++)
					{
						if (levelData[row][col] == 1)
						{
							if (player.shape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
							{
								gravity = 0;
								velocityY = 0;
								player.shape.setPosition(player.shape.getPosition().x, level[row][col].getPosition().y);
								player.shape.move(0, -player.shape.getGlobalBounds().height);
								break;
							}
						}
					}
				}
			}*/
		

			//clear the screen and draw the shapes.
			window.clear();


			for (int row = 0; row < numRows; row++)
			{
				for (int col = 0; col < numCols; col++)
				{
					window.draw(level[row][col]);

				}
			}
			window.draw(player.shape);
			window.draw(player.topBit);
			window.draw(playerTwo.shape);
			window.draw(playerTwo.topBit);
			window.draw(bullets->shape);
			/*for (int i = 0; i < numOfApples; i++)
			{
				window.draw(apples[i].shape);
			}*/
			for (int i = 0; i < numBullets; i++)
			{
				window.draw(bullets[i].shape);
			}
			//tell SFML  to display everything 
			window.display();

			// reset the timeSinceLastUpdate to 0 
			timeSinceLastUpdate = sf::Time::Zero;
		}
	}

	return 0;
}


