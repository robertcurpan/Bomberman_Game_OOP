#include "Player.h"
#include "Game.h"
#include "Collision.h"
#include "Enemies.h"


Player::Player(const char* path, float theScale, bool breakable, float xpos, float ypos, int h, int w) :SpriteComponent(path, theScale, breakable, xpos, ypos, h, w) 
{
	this->stopPlayerAnimationFromKeyboard = false;
	collidedWithOpenDoor = false;
}

void Player::KeyboardControllerPlayer() //calculeaza si pozitia viitoare in fct de tasta apasata
{
	if (stopPlayerAnimationFromKeyboard == false)
	{
		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				velocity.y = -1;
				animation.animID = animation.walkUp;
				lastKeyPressed = 'w';
				break;
			case SDLK_a:
				velocity.x = -1;
				animation.animID = animation.walkLeft;
				lastKeyPressed = 'a';
				break;
			case SDLK_d:
				velocity.x = 1;
				animation.animID = animation.walkRight;
				lastKeyPressed = 'd';
				break;
			case SDLK_s:
				velocity.y = 1;
				animation.animID = animation.walkDown;
				lastKeyPressed = 's';
				break;
			default:
				break;
			}
		}
		if (Game::event.type == SDL_KEYUP)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				velocity.y = 0;
				break;
			case SDLK_a:
				velocity.x = 0;
				break;
			case SDLK_d:
				velocity.x = 0;
				break;
			case SDLK_s:
				velocity.y = 0;
				break;
			default:
				break;
			}
		}
		if (velocity.x == 0 && velocity.y == 0)
		{
			switch (lastKeyPressed)
			{
			case 'w':
				animation.animID = animation.idleUp;
				break;
			case 'a':
				animation.animID = animation.idleLeft;
				break;
			case 's':
				animation.animID = animation.idleDown;
				break;
			case 'd':
				animation.animID = animation.idleRight;
				break;
			default:
				break;
			}
		}
	}
	else
	{
		velocity.x = 0;
		velocity.y = 0;
		animation.animID = Animations::deathPlayer;
	}
	
}

void Player::collidePlayerWithBlocks()
{
	if (isDead == false)
	{
		bool willCollide = false;
		futurePosition.h = collider.h;
		futurePosition.w = collider.w;
		futurePosition.x = collider.x + velocity.x * speed;
		futurePosition.y = collider.y + velocity.y * speed;

		for (int i = 0; i<Game::dim; i++)
		{
			Game::collidingBlocks[i]->update();
			if (Collision::AABB(futurePosition, Game::collidingBlocks[i]->smallerCollider))
				willCollide = true;
		}

		if (willCollide == false)
			SpriteComponent::update();
		else
		{
			//daca in directia in care am vrea sa ne miscam va urma o coliziune, atunci nu
			//mai miscam caracterul.
		}
	}
}

void Player::collidePlayerWithExplosion()
{
	if (Game::bomb->explosionActive == true)
	{
		if (startDeathAnimation == false)
			for (int i = 0; i < Game::bomb->dimExplosion; i++)
				if (Collision::AABB(smallerCollider, Game::bomb->explosionBlocks[i]))
				{
					stopPlayerAnimationFromKeyboard = true;
					startDeathAnimation = true;
				}
	}
}

void Player::playerDeathAnimation()
{
	if (startDeathAnimation == true)
	{
		deathTimer++;
		velocity.x = 0;
		velocity.y = 0;

		if (deathTimer > 60)
		{
			deathTimer = 0;
			startDeathAnimation = false;
			stopPlayerAnimationFromKeyboard = false;
			isDead = true;
		}
	}
}

void Player::collidePlayerWithEnemies()
{
	if (startDeathAnimation == false && isDead == false) //daca playerul a murit din cauza exploziei, nu poate muri inca o data din cauza unui inamic
	{
		for (int i = 0; i < Game::nrEnemies; i++)
		{
			if (Collision::AABB(smallerCollider, Game::enemies[i]->collider) && Game::enemies[i]->isDead == false && Game::enemies[i]->startDeathAnimation == false)
			{//daca inamicul se afla in animatia de death sau este mort, atunci playerul nu poate realiza coliziune cu acesta
				startDeathAnimation = true;
				stopPlayerAnimationFromKeyboard = true;
			}
		}
	}
}

void Player::collidePlayerWithOpenDoor()
{
	if (Collision::AABB(collider, Game::exitDoor->smallerCollider) == true && Game::exitDoor->doorOpen == true)
	{
		std::cout << "Level finished.\n";
		collidedWithOpenDoor = true;
	}
}

void Player::collidePlayerWithPickups()
{
	for (int i = 0; i < Game::nrPickups; i++)
	{
		if (Game::pickups[i]->isDead == false && Collision::AABB(collider, Game::pickups[i]->smallerCollider) == true)
		{
			//pickups[i]->isDead == false -> pickupul nu a fost luat de player
			Game::pickups[i]->isDead = true;
			if(Game::pickups[i]->pickupType == 'r')
				Game::bomb->setRadius(Game::bomb->getRadius() + 1);
			if (Game::pickups[i]->pickupType == 's')
				speed++;
		}
	}
}


void Player::update()
{
	playerDeathAnimation();

	KeyboardControllerPlayer(); //aici se calculeaza urmatoarea pozitie
	collidePlayerWithBlocks();
	collidePlayerWithEnemies();
	collidePlayerWithExplosion();
	collidePlayerWithOpenDoor();
	collidePlayerWithPickups();
}

void Player::draw()
{
	if (isDead == false)
		SpriteComponent::draw();
}