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
	char name_[30];		//스킬 이름
	char desc_[100];	//스킬 설명
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

	/*Set 함수*/
	void SetSkillOwner(Object* me)  {	me_ = me;	}

	/*Get 함수*/
	const char* GetName();
	const char* GetDescribe();

	/*스킬 구현 함수*/
	void UseSkillEffect(Object* target);
	void AttackSkill(Object* target, int damage);

	/*스킬*/
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
		skillList[0] = new Skill("내려찍기", "검으로 상대를 강하게 내려찍어 1.5배의 피해를 준다", &Skill::Crush);
		skillList[1] = new Skill("마나탄", "소량의 마나를 적에게 발사해 1.5배의 피해를 준다", &Skill::ManaBullet);
		skillList[2] = new Skill("마나화살", "화살에 마나를 둘러 1.5배의 피해를 준다", &Skill::ManaArrow);
		skillList[3] = new Skill("강타", "힘을 끌어올려 평소의 1.5배 가량의 더욱 강력한 한방을 준다.", &Skill::Smite);
		skillList[4] = new Skill("기습", "예상치 못한 공격으로 평소의 1.5배 더 많은 피해를 준다", &Skill::Ambush);
	}
};
