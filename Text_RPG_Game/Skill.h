#pragma once
#include <iostream>

#include "Object.h"

#define SKILL_MAX 4
#define SKILL_SUM 5

using std::cout;
using std::endl;

class Object;
class Skill
{
protected:
	char name_[30];		//��ų �̸�
	char desc_[100];	//��ų ����
	void (Skill::*skillFunc)(Object*);
	Object* me_;

public:
	Skill() {  }
	Skill(const char* name, const char* desc, void(Skill::*func)(Object*))
	{
		strcpy_s(name_, name);
		strcpy_s(desc_, desc);
		skillFunc = func;
	}

	/*Set �Լ�*/
	void SetSkillOwner(Object* me)  {	me_ = me;	}

	/*Get �Լ�*/
	const char* GetName();
	const char* GetDescribe();

	/*��ų ���� �Լ�*/
	void UseSkillEffect(Object* target);
	void AttackSkill(Object* target, int damage);

	/*��ų*/
	void Crush(Object* enemy);
	void ManaBullet(Object* target);
	void ManaArrow(Object* target);
	void Smite(Object* target);
	void Ambush(Object* target);
};

class SkillManager
{
public:
	static SkillManager* GetInst()
	{
		static SkillManager skillInst;
		return &skillInst;
	}
	static Skill* skillList[SKILL_SUM];
	void initSkillList()
	{
		skillList[0] = new Skill("�������", "������ ��븦 ���ϰ� ������� 1.5���� ���ظ� �ش�", &Skill::Crush);
		skillList[1] = new Skill("����ź", "�ҷ��� ������ ������ �߻��� 1.5���� ���ظ� �ش�", &Skill::ManaBullet);
		skillList[2] = new Skill("����ȭ��", "ȭ�쿡 ������ �ѷ� 1.5���� ���ظ� �ش�", &Skill::ManaArrow);
		skillList[3] = new Skill("��Ÿ", "���� ����÷� ����� 1.5�� ������ ���� ������ �ѹ��� �ش�.", &Skill::Smite);
		skillList[4] = new Skill("���", "����ġ ���� �������� ����� 1.5�� �� ���� ���ظ� �ش�", &Skill::Ambush);
	}
};
