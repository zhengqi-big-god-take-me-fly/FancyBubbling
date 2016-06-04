
#ifndef __FB_UTILS_H__
#define __FB_UTILS_H__

/*
@def CUSTOM_CREATE_FUNC_DEFINATION(__TYPE__, __ARGS__)
Define a create function for a specific type, such as Layer.
@param __TYPE__  class type to add create(), such as Layer.
@param __ARGS__  argument list in init
*/
/*
#define CUSTOM_CREATE_FUNC_DEFINATION(__TYPE__, __ARGS__) \
static __TYPE__* create(__ARGS__) { \
    __TYPE__ *pRet = new(std::nothrow) __TYPE__(); \
    if (pRet && pRet->init(__ARGS__)) { \
        pRet->autorelease(); \
        return pRet; \
    } else { \
        delete pRet; \
        pRet = nullptr; \
        return nullptr; \
    } \
}

#define CUSTOM_INIT_FUNC_DECLARATION(__ARGS__) \
virtual bool init(__ARGS__);
*/
#endif // !__FB_UTILS_H__
