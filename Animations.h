#pragma once


struct Animations
{
	//variabilele din enum fac parte din structura Animations (enum-ul nu e un namespace)
	enum animName { nothing = 0, walkUp, walkLeft, walkDown, walkRight, idleUp, idleLeft, idleDown, idleRight, enemyID1, enemyID2, enemyID3, deathEnemyID1, deathEnemyID2, deathEnemyID3, deathPlayer };
	animName animID;
	int nrFrames;
	int animSpeed;
};
