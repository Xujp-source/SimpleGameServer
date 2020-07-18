//#ifndef __MAIL_MODULE_H__
//#define __MAIL_MODULE_H__
//#include "BaseModule.h"
//
//struct MailDataObject;
//class CMailModule  : public CBaseModule
//{
//public:
//	CMailModule(CPlayerObject* pOwner);
//
//	~CMailModule();
//
//public:
//	//*********************模块通用方法定义开始**************************
//	virtual void RegisterMessageHanler();
//	//virtual BOOL ReadFromDBLoginData(DBRoleLoginAck& Ack);
//	//virtual BOOL SaveToClientLoginData(RoleLoginAck& Ack);
//	virtual bool NotifyChange();
//	//******************************************************************
//
//public:
//	//*********************模块自定义方法定义开始*************************
//	bool AddMail();
//	bool DeleteMail();
//	//******************************************************************
//
//public:
//	//*********************消息处理定义开始******************************
//	//bool OnMsgMailSendReq(NetPacket* pNetPacket);  //玩家给玩家发邮件
//	//bool OnMsgGuildMailSendReq(NetPacket* pNetPacket);  //玩家给公会群发邮件
//	//******************************************************************
//
//public:
//	std::map<unsigned long long, MailDataObject*> m_mapMailData;
//
//};
//
//#endif //__MAIL_MODULE_H__
