#ifndef _GAME_SCENE_MANAGER_H_
#define _GAME_SCENE_MANAGER_H_
#include "../stdafx.h"
#include "../ServerData/BattleData.h"

class GameScene;
class GameSceneManager
{
private:
	GameSceneManager();
	virtual ~GameSceneManager();

public:
	static GameSceneManager* GetInstancePtr();

public:
	//��Ϸ��ѭ��
	bool GameLoop();

	//��ȡ��������
	GameScene* GetSceneObj(unsigned long long uid);

	//������������
	GameScene* CreateScene(BattleSide& atk, BattleSide& def);

private:
	std::map<unsigned long long, GameScene*> m_scenemap;
};

#endif

