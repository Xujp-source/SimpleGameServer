#include "GameService.h"
#include "stdafx.h"

int main()
{
	CELLLog::Instance().setLogPath("serverLog.txt", "w");
	//初始化
	if (!CGameService::GetInstancePtr()->Init())
	{
		CELLLog::Info("logic server init failed!\n");
		return -1;
	}
	//初始化网络服务
	CGameService::GetInstancePtr()->InitSocket();
	CGameService::GetInstancePtr()->Bind(nullptr, 9897);
	CGameService::GetInstancePtr()->Listen(64);
	CGameService::GetInstancePtr()->Start(1);

	//在主线程中等待用户输入命令
	while (true)
	{
		char cmdBuf[256] = {};
		scanf("%s", cmdBuf);
		if (0 == strcmp(cmdBuf, "exit"))
		{
			CGameService::GetInstancePtr()->Close();
			break;
		}
		else {
			CELLLog::Info("undefine cmd\n");
		}
	}

	CELLLog::Info("exit.\n");
	return 0;
}