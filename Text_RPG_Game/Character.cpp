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
		//AddSkill("�������");
		break;
	case WIZARD:
		SetStatus(7, 9, 50, 20, 5, 10, 1, 0);
		//AddSkill("����ź");
		break;
	case ARCHER:
		SetStatus(8, 6, 25, 25, 8, 10, 1, 0);
		//AddSkill("����ȭ��");
		break;
	case FIHGHTER:
		SetStatus(8, 6, 40, 20, 7, 10, 1, 0);
		//AddSkill("��Ÿ");
		break;
	case THIEF:
		SetStatus(7, 4, 30, 30, 9, 40, 1, 0);
		//AddSkill("���");
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
		return "����";
		break;
	case WIZARD:
		return "������";
		break;
	case ARCHER:
		return "�ü�";
		break;
	case FIHGHTER:
		return "������";
		break;
	case THIEF:
		return "����";
		break;
	default:
		break;
	}
}



void Character::Kill(const Object* obj)
{
	cout << "�ο򿡼� �¸��Ͽ����ϴ�." << endl;
	int exp = obj->Getexp();
	cout << exp_ << "�� ����ġ�� ������ϴ�." << endl;
	exp_ += exp;
	if (exp_ >= levelUpExp_)
	{
		level_++;
		exp_ -= levelUpExp_;
		cout << "������! ���� ���� : " << level_ << endl;
	}
	int money = obj->Getmoney();
	cout << money << "�� ���� ȹ���߽��ϴ�." << endl;
	money_ = money;
}

void Character::Dead()
{
	cout << "�������� �й��߽��ϴ�. ������" << money_ * 0.1f << "�� ����ġ�� ��� �Ұ� ������ �����մϴ�.";
	exp_ = 0;
	money_ -= money_ * 0.1f;

	if (money_ < 0)
	{
		money_ = 0;
	}
}



void Character::GetInterFace_BattleMenu()
{
	cout << "������������������������������������������������������������������" << endl;
	cout << "��1. ����     2. ���    3.��ų  ��" << endl;
	cout << "��4. ������   5. ����            ��" << endl;
	cout << "������������������������������������������������������������������" << endl;
}

