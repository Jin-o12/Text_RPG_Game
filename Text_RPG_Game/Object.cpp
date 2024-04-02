#pragma once
#include "Object.h"

const char* Object::GetName()  { return name_; }
int Object::Getattack() const  { return attack_; }
int Object::Getdefense() const  { return defense_; }
int Object::GetHP() const  { return HP_; }
int Object::GetMP() const  { return MP_; }
int Object::Getspeed() const  { return speed_; }
int Object::Getmoney() const  { return money_; }
int Object::Getlevel() const  { return level_; }
int Object::Getexp() const  { return exp_; }

void Object::SetStatus(int attack, int defence, int HP, int MP, int speed, int money, int level, int exp)
{	
	attack_ = attack;
	defense_ = defence;
	HP_ = HP;
	MP_ = MP;
	speed_ = speed;
	money_ = money;
	level_ = level;
	exp_ = exp;
}

/*���º�ȭ& �׼� ���� �Լ�*/
int Object::GetDemage(int atk)
{
	int damage = atk - defense_;
	if (damage > 0)
	{
		HP_ -= damage;
		return damage;
	}
	else
		return 0;
}
void Object::GetDefendedDamage(int atk)
{
	/*���� ���� �� * DEFENSE_PERCENTAGE ��ġ��ŭ �ջ��Ͽ� �� ���*/
	int damage = atk - (defense_ + (defense_ * DEFENSE_PERCENTAGE));
	GetDemage(atk);
}

void Object::HPchange(int getHP) { this->HP_ += getHP; }
void Object::MPchange(int getMP) { this->MP_ += getMP; }
void Object::ATKchange(int getATK) { this->attack_ += getATK; }
void Object::DEFchange(int getDEF) { this->defense_ += getDEF; }
void Object::SPDchange(int getSPD) { this->speed_ += getSPD; }


