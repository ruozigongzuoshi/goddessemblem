/*
    文件名：    PosLoadUtil.h
    描　述：    坐标对象加载工具
    
*/
#ifndef _PosLoadUtil_H_
#define _PosLoadUtil_H_

#include "cocos2d.h"
#include "EnumPosType.h"
USING_NS_CC;

class PosLoadUtil : public CCNode {
public:
	static PosLoadUtil* sharedPosLoadUtil();
	virtual bool init();

	/* 
		根据坐标类型从plist配置文件中读取坐标对象 
		sFilePath：配置文件路径
		enPosType：坐标对象类型
		container：存放坐标对象的容器
		iLevel：如果存在container，该参数表示坐标对象在容器中的层次
		isDebug：是否开启调试模式
	*/
	CCArray* loadPosWithFile(
		const char* sFilePath,
		EnumPosType enPosType, 
		CCNode* container, 
		int iLevel, 
		bool isDebug);
private:
	static PosLoadUtil* m_posLoadUtil;
};

#endif