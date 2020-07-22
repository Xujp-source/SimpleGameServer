#ifndef _GLOBAL_LOG_H_
#define _GLOBAL_LOG_H_
#include "../CELLLog.hpp"

#define ERROR_RETURN_TRUE(P) \
    if((P) == FALSE)\
    {\
        CELLLog::Info("Error : File:%s, Func: %s Line:%d\n", __FILE__ , __FUNCTION__, __LINE__);\
        return TRUE;	\
    }


#define ERROR_RETURN_FALSE(P) \
    if((P) == FALSE)\
    {\
        CELLLog::Info("Error : File:%s, Func: %s Line:%d\n", __FILE__ , __FUNCTION__, __LINE__);\
        return FALSE;	\
    }

#define ERROR_RETURN_NULL(P) \
	if((P) == FALSE)\
{\
	CELLLog::Info("Error : File:%s, Func: %s Line:%d\n", __FILE__ , __FUNCTION__, __LINE__);\
	return NULL;	\
}

#define ERROR_RETURN_NONE(P) \
	if((P) == FALSE)\
{\
	CELLLog::Info("Error : File:%s, Func: %s Line:%d\n", __FILE__ , __FUNCTION__, __LINE__);\
	return ;	\
}

#define ERROR_RETURN_VALUE(P, V) \
	if((P) == FALSE)\
{\
	CELLLog::Info("Error : File:%s, Func: %s Line:%d\n", __FILE__ , __FUNCTION__, __LINE__);\
	return V;	\
}

#define ERROR_CONTINUE_EX(P) \
    if((P) == FALSE)\
{\
	CELLLog::Info("Error : File:%s, Func: %s Line:%d\n", __FILE__ , __FUNCTION__, __LINE__);\
    continue; \
}

#define ERROR_TO_CONTINUE(P) \
    if((P) == FALSE)\
{\
	CELLLog::Info("Error : File:%s, Func: %s Line:%d\n", __FILE__ , __FUNCTION__, __LINE__);\
    continue; \
}

#endif