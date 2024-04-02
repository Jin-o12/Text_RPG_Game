#pragma once
#include <iostream>

#define SKILL_MAX 4
#define INVENTORY_SIZE 10
#define DEFENSE_PERCENTAGE 0.5

using std::cout;
using std::endl;

struct ItemObject;
class Skill;
class Item;

class Object
{
private:
protected:
	char name_[20];
	int attack_;
	int defense_;
	int HP_;
	int MP_;
	int speed_;
	int money_;
	int level_;
	int exp_;
	Skill* thisSkillList_[SKILL_MAX] = { nullptr };
	ItemObject* thisInventory_[INVENTORY_SIZE] = { nullptr };
public:
	//GET �Լ�
	const char* GetName();
	int Getattack() const;
	int Getdefense() const;
	int GetHP() const;
	int GetMP() const;
	int Getspeed() const;
	int Getmoney() const;
	int Getlevel() const;
	int Getexp() const;

	/*�ɷ�ġ ���� �Լ�*/
	void SetStatus(int attack, int defence, int HP, int MP, int speed, int money, int level, int exp);

	/*���º�ȭ& �׼� ���� �Լ�*/
	int GetDemage(int atk);				//�������� ����
	void GetDefendedDamage(int atk);	//�߰� ���� ���Ե� ��ŭ�� �������� ����
	void HPchange(int getHP);			//ü�º��� (���� ���� ���� �� �Ҹ�)
	void MPchange(int getMP);			//�������� (���� ���� ���� �� �Ҹ�)
	void ATKchange(int getATK);			//���ݷ� ��ġ
	void DEFchange(int getDEF);			//���� ��ġ
	void SPDchange(int getSPD);			//�ӵ� ��ġ

	virtual void Kill(const Object* obj) {};
	virtual void Dead() {};

	
};