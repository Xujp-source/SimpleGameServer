#include "GameSceneManager.h"
#include "GameScene.h"

GameSceneManager::GameSceneManager()
{
}

GameSceneManager::~GameSceneManager()
{
}

GameSceneManager * GameSceneManager::GetInstancePtr()
{
	static GameSceneManager Instance;
	return &Instance;
}

bool GameSceneManager::GameLoop()
{	
	std::map<unsigned long long, GameScene*>::iterator itor = m_scenemap.begin();
	for (; itor != m_scenemap.end(); itor++)
	{
		GameScene* battleScene = itor->second;
		switch (battleScene->Mode)
		{
		case BATTLE_MODE_NONE://δս��
			break;
		case BATTLE_MODE_INIT://ս����ʼ��
			battleScene->Init();
			break;
		case BATTLE_MODE_BATTLE://ս����
			battleScene->BATTLECommand();
			break;
		case BATTLE_MODE_FINISH://ս������
			battleScene->BATTLEFinish();
			break;
		default:
			break;
		}
	}
	return true;
}

GameScene * GameSceneManager::GetSceneObj(unsigned long long uid)
{
	return nullptr;
}

GameScene * GameSceneManager::CreateScene(BattleSide& atk, BattleSide& def)
{
	GameScene* scene = new GameScene;
	scene->Mode = BATTLE_MODE_INIT;
	scene->Side[ATK_TARGET] = atk;
	scene->Side[DEFINE_TARGET] = def;
	scene->RoundEndTime = CELLTime::getNowInSec();
	scene->EndTime = CELLTime::getNowInSec();

	unsigned long long uid = Uuid::GetInstancePtr()->NewGuid();
	scene->SetUid(uid);
	m_scenemap.insert(std::make_pair(uid, scene));
	return scene;
}
