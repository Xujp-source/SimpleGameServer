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
	//�����ͷż�������
	BATTLE_COMMAND_SKILL,
	//�����������
	BATTLE_COMMAND_DEFINE,
	//����ʹ�õ�������
	BATTLE_COMMAND_USING,
	//�����л���������
	BATTLE_COMMAND_CHANGECARD,
	//������������
	BATTLE_COMMAND_ESCAPE

};

enum BATTLE_ROUND_LOCK
{
	//��һ�غ�ָ��������
	COMMAND_UNLOCK,
	//��ǰ�غ��յ�ָ���ļ������
	COMMAND_LOCK
};


//��Ӫ��
#define BATTLE_SIDE_COUNT 2
//��ǰ�غ�ѡ�����ָ���ʱ������
#define ROUND_TIME 20
//һ��ս�����������ʱ��
#define BATTLE_MAX_TIME 60*60

#endif