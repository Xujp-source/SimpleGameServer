#ifndef __SERVER_DEFINE_H__
#define __SERVER_DEFINE_H__


enum 
{
	SQL_BEGIN,
	//��ȡ
	SQL_READ,
	//ִ��
	SQL_EXECUTE,
	//����
	SQL_TRANSACTION,
	//replace
	SQL_REPLACE
};

enum BATTLE_MODE
{
	//δս��
	BATTLE_MODE_NONE,
	//ս����ʼ��
	BATTLE_MODE_INIT,
	//����ս����
	BATTLE_MODE_BATTLE,
	//ս������
	BATTLE_MODE_FINISH
};

enum BATTLE_TARGET
{
	//������
	ATK_TARGET,
	//���ط�
	DEFINE_TARGET
};

enum BATTLE_COMMAND
{
	//��ʼ��������
	BATTLE_COMMAND_NONE,
	//������ͨ��������
	BATTLE_COMMAND_ATK,
	//�����ͷż�������
	BATTLE_COMMAND_SKILL,
	//�����������
	BATTLE_COMMAND_DEFINE,
	//����ʹ�õ�������
	BATTLE_COMMAND_USING,
	//������������
	BATTLE_COMMAND_ESCAPE

};

enum BATTLE_ROUND_LOCK
{
	BATTLE_COMMAND_LOCK,
	BATTLE_COMMAND_UNLOCK
};


//��Ӫ��
#define BATTLE_SIDE_COUNT 2


#endif