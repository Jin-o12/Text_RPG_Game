#pragma once
#include <iostream>
#include "Object.h"

#define JOB_NUMBER 5		//���� ����

enum jobType : int;

class Character : public Object
{
private:
	jobType job_;
	int levelUpExp_ = 30;

protected:
public:
	/*GET �Լ�*/
	void GetJobState(jobType job);
	const char* GetJobName();
	jobType GetPlayerJob();
	int Getattack() const { return attack_; }
	int GetDefense() const { return defense_; }

	/*��ų �Լ�*/
	int AddSkill(const char* name);	//��ų �߰�, ����� �����ڵ�� ��� (0 : ���(�̹� ���� ��ų ����), 1 : �߰� ����, -1 : ����(�ڸ�����))
	void UseSkill(int num, Object* enermy);

	/*������ ���� �Լ�*/
	void InputItemToInven(int itemCode, int stack);		//������ �ڵ带 �޾� �κ��丮�� input
	bool IsInvemEmpty();								//�κ��丮�� ������� �� true
	void EquipItem(int invenNum);						//������ ����
	void UseItem(int ItemCode);							//������ ���
	//void equipPessiveOnOff();

	/*�÷��̾� �ൿ�̳� ���� �Լ�*/
	bool BuySometing(int price);			//���� ����

	/*SET �Լ�*/
	void SetName(const char* pName);
	void SetPlayerJob(int type);

	virtual void Kill(const Object* obj);
	virtual void Dead();

	//GET_INTERFACE �Լ� (�� ��ȯ ���� ������ ���Ĵ�� ���� ���)
	void GetInterFace_BattleMenu();
	void GetInterFace_Inventory();
	void GetInterFace_SkillList();
	void GetInterFace_EquipList();
};


