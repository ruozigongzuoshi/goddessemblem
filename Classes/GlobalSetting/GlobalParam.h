/*
    �ļ�����    GlobalParam.h
    �衡����    ȫ�ֲ���
    
*/
#ifndef __GLOBAL_PARAM_H__
#define __GLOBAL_PARAM_H__

#include "cocos2d.h"

using namespace cocos2d;

class GlobalParam : public CCObject {
public:
    /* ����ʱĬ�ϵ���Ļ��С */
    static const int DEFAULT_SCREEN_WIDTH = 1280;
    static const int DEFAULT_SCREEN_HEIGHT = 720;

    /* ���� */
    static const int PublicFontSize = 22;
	static const int PublicFontSizeLarge = 35;
	static const int PublicFontSizeLargest = 60;

    /* Layer��� */
    static const int LayerOrder_LvLLowest = 1;
    static const int LayerOrder_LvL11 = 20;
    static const int LayerOrder_LvL9 = 30;
    static const int LayerOrder_LvL7 = 40;
    static const int LayerOrder_LvLNormal = 50;
    static const int LayerOrder_LvL3 = 60;
    static const int LayerOrder_LvL1 = 70;
    static const int LayerOrder_LvLHighest = 200;

    /* ��ɫID���λ�� */
    static const int ACTOR_ID_MAX_NUM = 8;
};

#endif