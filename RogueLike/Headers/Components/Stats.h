#pragma once


struct Stats
{

	Stats()
		:hp(0),
		moveSpeed(0),
		attackSpeed(0),
		damage(0)
	{
	}

	Stats(int hp, float moveSpeed, float attackSpeed, float damage)
		:hp(hp),
		moveSpeed(moveSpeed),
		attackSpeed(attackSpeed),
		damage(damage)
	{

	}

	Stats operator+(const Stats& other) const
	{
		return {hp + other.hp, moveSpeed + other.moveSpeed, attackSpeed + other.attackSpeed, damage + other.damage};
	}

	int hp;
	float moveSpeed;
	float attackSpeed;
	float damage;


};