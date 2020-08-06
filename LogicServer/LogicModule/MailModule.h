#ifndef __MAIL_MODULE_H__
#define __MAIL_MODULE_H__
#include "BaseModule.h"

struct MailDataObject;
class CMailModule  : public CBaseModule
{
public:
	CMailModule(CPlayerObject* pOwner);

	virtual ~CMailModule();

public:
	//*********************模块通用方法定义开始*************************
	virtual void RegisterMessageHanler();
	virtual void RegisterEventHanler();
	virtual bool ReadFromDBLoginData();
	virtual bool SaveChangeData();
	//******************************************************************

public:
	//*********************模块自定义方法定义开始***********************
	bool SendMail(int descid, int itemid);
	//******************************************************************

public:
	//*********************消息处理定义开始*****************************
	//bool OnMsgLoadMailReq(NetPacket* pNetPacket);         //请求加载邮件
	bool OnMsgReadMailReq(NetPacket* pNetPacket);         //读邮件
	bool OnMsgAcquireMailReq(NetPacket* pNetPacket);      //领取邮件奖励
	bool OnMsgDeleteMailReq(NetPacket* pNetPacket);       //删除邮件
	//******************************************************************

public:
	std::map<unsigned long long, MailDataObject*> m_mapMailData;

};

#endif //__MAIL_MODULE_H__
