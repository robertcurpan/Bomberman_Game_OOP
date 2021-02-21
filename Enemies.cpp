#include "Enemies.h"
#include "Game.h"
#include "Collision.h"
#include "Level.h"


Enemy::Enemy(const char* path, float theScale, bool breakable, int enemyID, bool verticalMovement, float xpos, float ypos, int h, int w): SpriteComponent(path,theScale,breakable,xpos,ypos,h,w)
{
	this->enemyID = enemyID;
	this->verticalMovement = verticalMovement;
}

void Enemy::setMovement()
{
	switch (enemyID)
	{
	case 1:
		animation.animID = Animations::enemyID1;
		break;
	case 2:
		animation.animID = Animations::enemyID2;
		break;
	case 3:
		animation.animID = Animations::enemyID3;
		break;
	default:
		break;
	}

	if (verticalMovement == true)
	{
		velocity.x = 0;
		velocity.y = 1;
		
		if (Level::level == 1)
			speed = 2;
		if (Level::level == 2)
			speed = 3;
		if (Level::level == 3)
			speed = 4;
	}
	else
	{
		velocity.x = 1;
		velocity.y = 0;
		if (Level::level == 1)
			speed = 2;
		if (Level::level == 2)
			speed = 3;
		if (Level::level == 3)
			speed = 4;
	}
}


void Enemy::collideWithBlocksAndBombs()
{
	if (isDead == false)
	{
		bool willCollide = false;
		futurePosition.h = collider.h;
		futurePosition.w = collider.w;
		futurePosition.x = collider.x + velocity.x * speed;
		futurePosition.y = collider.y + velocity.y * speed;

		for (int i = 0; i < Game::dim && willCollide == false; i++)
		{
			Game::collidingBlocks[i]->update();
			if (Collision::AABB(futurePosition, Game::collidingBlocks[i]->smallerCollider))
				willCollide = true;
		}
		if (Game::bomb->bombActive == true && Collision::AABB(futurePosition, Game::bomb->smallerCollider))
			willCollide = true;

		if (willCollide == false)
			update();
		else
		{
			velocity.x = -velocity.x;
			velocity.y = -velocity.y;
		}
	}
}

void Enemy::collideWithBlocksAndBombsV2()
{
	bool willCollide = false;
	futurePosition.h = collider.h;
	futurePosition.w = collider.w;
	futurePosition.x = collider.x + velocity.x * speed;
	futurePosition.y = collider.y + velocity.y * speed;

	for (int i = 0; i < Game::dim && willCollide == false; i++)
	{
		Game::collidingBlocks[i]->update();
		if (Collision::AABB(futurePosition, Game::collidingBlocks[i]->smallerCollider))
			willCollide = true;
	}
	if (Game::bomb->bombActive == true && Collision::AABB(futurePosition, Game::bomb->smallerCollider))
		willCollide = true;

	if (willCollide == false)
		update();
	else
	{   
		//exista coliziune
		willCollide = false;
		if (velocity.x == 1 && willCollide == false)
		{
			velocity.x = 0;
			velocity.y = 1;
			willCollide = true; //sa nu putem intra si in celelalte if-uri
		}
		if (velocity.x == -1 && willCollide == false)
		{
			velocity.x = 0;
			velocity.y = -1;
			willCollide = true;
		}
		if (velocity.y == 1 && willCollide == false)
		{
			velocity.x = -1;
			velocity.y = 0;
			willCollide = true;
		}
		if (velocity.y == -1 && willCollide == false)
		{
			velocity.x = 1;
			velocity.y = 0;
			willCollide = true;
		}

	}
}


void collideEnemiesWithExplosion()
{
	if (Game::bomb->explosionActive == true)
	{
		for (int i = 0; i < Game::nrEnemies; i++)
		{
			for (int j = 0; j < Game::bomb->dimExplosion; j++)
			{
				if (Collision::AABB(Game::enemies[i]->smallerCollider, Game::bomb->explosionBlocks[j]))
				{
					if (Game::enemies[i]->getEnemyID() == 1)
						Game::enemies[i]->animation.animID = Animations::deathEnemyID1;
					if (Game::enemies[i]->getEnemyID() == 2)
						Game::enemies[i]->animation.animID = Animations::deathEnemyID2;
					if (Game::enemies[i]->getEnemyID() == 3)
						Game::enemies[i]->animation.animID = Animations::deathEnemyID3;

					Game::enemies[i]->startDeathAnimation = true;
				}
			}
		}
	}
}

void enemiesDeathAnimation()
{
	for (int i = 0; i < Game::nrEnemies; i++)
	{
		if (Game::enemies[i]->startDeathAnimation == true)
		{
			Game::enemies[i]->deathTimer++;
			Game::enemies[i]->velocity.x = 0;
			Game::enemies[i]->velocity.y = 0;

			if (Game::enemies[i]->deathTimer > 60)
			{
				Game::enemies[i]->deathTimer = 0;
				Game::enemies[i]->startDeathAnimation = false;
				Game::enemies[i]->isDead = true;
			}
		}
	}
}

void collideEnemiesWithOtherEnemies()
{
	for (int i = 0; i < Game::nrEnemies; i++)
	{
		bool willCollide = false;
		if (Game::enemies[i]->isDead == false && Game::enemies[i]->startDeathAnimation == false) //daca e mort sau si-a inceput animatia de moarte nu poate realiza coliziuni
		{
			for (int j = 0; j < Game::nrEnemies; j++)
			{
				if (i != j && Game::enemies[j]->isDead == false && Collision::AABB(Game::enemies[i]->getFuturePosition(), Game::enemies[j]->collider))
					willCollide = true;
			}

			if (willCollide == true)
			{
				Game::enemies[i]->velocity.x = -Game::enemies[i]->velocity.x;
				Game::enemies[i]->velocity.y = -Game::enemies[i]->velocity.y;
			}
		}
	}
}

void updateEnemies()
{
	for (int i = 0; i < Game::nrEnemies; i++)
	{
		if(Level::level == 1)
			Game::enemies[i]->collideWithBlocksAndBombs();
		if(Level::level == 2)
			Game::enemies[i]->collideWithBlocksAndBombsV2();
		if(Level::level == 3)
			Game::enemies[i]->collideWithBlocksAndBombsV2();
		
	}
	enemiesDeathAnimation();
	collideEnemiesWithOtherEnemies(); //future Position-ul e calculat in for-ul de mai sus
	collideEnemiesWithExplosion();
}