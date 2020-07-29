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
	//游戏主循环
	bool GameLoop();

	//获取场景对象
	GameScene* GetSceneObj(unsigned long long uid);

	//创建场景对象
	GameScene* CreateScene(BattleSide& atk, BattleSide& def);

private:
	std::map<unsigned long long, GameScene*> m_scenemap;
};

#endif

