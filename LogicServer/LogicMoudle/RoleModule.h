//#ifndef __ROLE_MODULE_H__
//#define __ROLE_MODULE_H__
//#include "BaseModule.h"
//
//struct RoleDataObject;
//class CRoleModule  : public CBaseModule
//{
//public:
//	CRoleModule(CPlayerObject* pOwner);
//
//	virtual ~CRoleModule();
//
//public:
//	//*********************模块通用方法定义开始**************************
//	virtual void RegisterMessageHanler();
//	//virtual BOOL ReadFromDBLoginData(DBRoleLoginAck& Ack);
//	//virtual BOOL SaveToClientLoginData(RoleLoginAck& Ack);
//	virtual bool NotifyChange();
//	//*********************模块通用方法定义结束**************************
//
//public:
//	//*********************模块自定义方法定义开始*************************
//	//*********************模块自定义方法定义结束*************************
//
//public:
//	//*********************消息处理定义开始******************************
//	//bool OnMsgRoleGetRandNameReq(NetPacket* pNetPacket);  //获取随机姓名请求
//	//*********************消息处理定义结束******************************
//
//public:
//	std::map<unsigned long long, RoleDataObject*> m_mapRoleData;
//
//};
//
//#endif //__STORE_MODULE_H__
