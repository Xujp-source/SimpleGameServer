#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_
#include "../ServerData/BattleData.h"
#include "../ServerEngine/MessageHeader.hpp"
#include "../ServerDefine.h"

class GameScene
{
private:
	//����uid
	unsigned long long m_uid;

public:
	GameScene();

	virtual ~GameScene();

	void RegisterMessageHanler();

	//��ʼ����������
	bool Init();

	//����ս��״̬
	bool BATTLECommand();

	//ս������
	bool BATTLEFinish();

	//ս���Ƿ�ʱ���
	bool BATTLETimeOutCheck();

	//�Ƿ������һ�غϼ��
	bool BATTLENextRoundCheck();

	//ִ��ս��ָ��
	bool ExecBATTLECommand();

public:
	//��ȡ����uid
	inline int GetUid() { return m_uid; }

	//���ó���uid
	inline void SetUid(int uid) { m_uid = uid; }

public:
	//*******************��Ϣ��������**************************
	bool OnMsgCommandAtkReq(NetPacket* pack);	  //��ͨ��������
	//*********************************************************

public:
	//��ǰ��ģʽ
	int Mode;
	//������Ӫ
	BattleSide Side[BATTLE_SIDE_COUNT];
	//��ǰս���غ���
	int RoundCount;
	//��ǰ�غ�ָ��Ĳ�������ʱ���
	unsigned long long RoundEndTime;
	//ս�����������ʱ��(����ʱ���)
	unsigned long long EndTime;
	//��ǰ�غ�ָ����
	int CmdLock;

};

#endif