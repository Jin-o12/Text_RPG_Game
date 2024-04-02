#pragma once
#include <iostream>

#include "Character.h"

using std::cout;
using std::cin;
using std::endl;

enum jobType : int
{
	WARRIOR,
	WIZARD,
	ARCHER,
	FIHGHTER,
	THIEF,
	JOB_END
};

void Character::GetJobState(jobType job)
{
	switch (job)
	{
	case WARRIOR:
		SetStatus(7, 9, 50, 20, 5, 10, 1, 0);
		//AddSkill("내려찍기");
		break;
	case WIZARD:
		SetStatus(7, 9, 50, 20, 5, 10, 1, 0);
		//AddSkill("마나탄");
		break;
	case ARCHER:
		SetStatus(8, 6, 25, 25, 8, 10, 1, 0);
		//AddSkill("마나화살");
		break;
	case FIHGHTER:
		SetStatus(8, 6, 40, 20, 7, 10, 1, 0);
		//AddSkill("강타");
		break;
	case THIEF:
		SetStatus(7, 4, 30, 30, 9, 40, 1, 0);
		//AddSkill("기습");
		break;
	default:
		break;
	}
	level_ = 1;
	exp_ = 0;
}

void Character::SetName(const char* pName)
{
	strcpy_s(name_, pName);
}

void Character::SetPlayerJob(int type)
{
	job_ = static_cast<jobType>(type-1);
	GetJobState(job_);
}


jobType Character::GetPlayerJob()
{
	return job_;
}
const char* Character::GetJobName()
{
	switch (job_)
	{
	case WARRIOR:
		return "전사";
		break;
	case WIZARD:
		return "마법사";
		break;
	case ARCHER:
		return "궁수";
		break;
	case FIHGHTER:
		return "격투가";
		break;
	case THIEF:
		return "도적";
		break;
	default:
		break;
	}
}



void Character::Kill(const Object* obj)
{
	cout << "싸움에서 승리하였습니다." << endl;
	int exp = obj->Getexp();
	cout << exp_ << "의 경험치를 얻었습니다." << endl;
	exp_ += exp;
	if (exp_ >= levelUpExp_)
	{
		level_++;
		exp_ -= levelUpExp_;
		cout << "레벨업! 현재 레벨 : " << level_ << endl;
	}
	int money = obj->Getmoney();
	cout << money << "의 돈을 획득했습니다." << endl;
	money_ = money;
}

void Character::Dead()
{
	cout << "전투에서 패배했습니다. 소지금" << money_ * 0.1f << "와 경험치를 모두 잃고 마을로 복귀합니다.";
	exp_ = 0;
	money_ -= money_ * 0.1f;

	if (money_ < 0)
	{
		money_ = 0;
	}
}



void Character::GetInterFace_BattleMenu()
{
	cout << "┌───────────────────────────────┐" << endl;
	cout << "│1. 공격     2. 방어    3.스킬  │" << endl;
	cout << "│4. 아이템   5. 도망            │" << endl;
	cout << "└───────────────────────────────┘" << endl;
}

