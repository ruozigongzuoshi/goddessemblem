/*
 * Copyright (c) 2012 cocos2d-x.org
 * http://www.cocos2d-x.org
 *
 * Copyright 2011 Yannick Loriot.
 * http://yannickloriot.com
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */
#include "GWScale9Button.h"
#include "support/CCPointExtension.h"
#include "label_nodes/CCLabelTTF.h"
#include "label_nodes/CCLabelBMFont.h"
#include "actions/CCAction.h"
#include "actions/CCActionInterval.h"
#include "FileLoad/I18N.h"

using namespace std;

enum
{
    kZoomActionTag = 0xCCCB0001,
};

GWScale9Button::GWScale9Button()
: m_currentTitle(NULL)
, m_currentTitleColor(ccWHITE)
, m_doesAdjustBackgroundImage(false)
, m_titleLabel(NULL)
, m_backgroundSprite(NULL)
, m_zoomOnTouchDown(false)
, m_isPushed(false)
, m_bParentInited(false)
, m_titleDispatchTable(NULL)
, m_titleColorDispatchTable(NULL)
, m_titleLabelDispatchTable(NULL)
, m_backgroundSpriteDispatchTable(NULL)
, m_marginH(CCControlButtonMarginLR)
, m_marginV(CCControlButtonMarginTB)
{

}

GWScale9Button::~GWScale9Button()
{
    CC_SAFE_RELEASE(m_backgroundSpriteDispatchTable);
    CC_SAFE_RELEASE(m_titleLabelDispatchTable);
    CC_SAFE_RELEASE(m_titleColorDispatchTable);
    CC_SAFE_RELEASE(m_titleDispatchTable);
    CC_SAFE_RELEASE(m_backgroundSprite);
}

//initialisers

bool GWScale9Button::init()
{
    return this->initWithLabelAndBackgroundSprite(CCLabelTTF::create("", "Helvetica", 12), CCScale9Sprite::create());
}

bool GWScale9Button::initWithLabelAndBackgroundSprite(CCNode* node, CCScale9Sprite* backgroundSprite)
{
    if (CCControl::init())
    {
        CCAssert(node != NULL, "Label must not be nil.");
        CCLabelProtocol* label = dynamic_cast<CCLabelProtocol*>(node);
        CCRGBAProtocol* rgbaLabel = dynamic_cast<CCRGBAProtocol*>(node);
        CCAssert(backgroundSprite != NULL, "Background sprite must not be nil.");
        CCAssert(label != NULL || rgbaLabel!=NULL || backgroundSprite != NULL, "");
        
        m_bParentInited = true;

        // Initialize the button state tables
        this->setTitleDispatchTable(CCDictionary::create());
        this->setTitleColorDispatchTable(CCDictionary::create());
        this->setTitleLabelDispatchTable(CCDictionary::create());
        this->setBackgroundSpriteDispatchTable(CCDictionary::create());

        setTouchEnabled(true);
        m_isPushed = false;
        m_zoomOnTouchDown = true;

        m_currentTitle=NULL;

        // Adjust the background image by default
        setAdjustBackgroundImage(true);
        setPreferredSize(CCSizeZero);
        // Zooming button by default
        m_zoomOnTouchDown = true;
        
        // Set the default anchor point
        ignoreAnchorPointForPosition(false);
        setAnchorPoint(ccp(0.5f, 0.5f));
        
        // Set the nodes
        setTitleLabel(node);
        setBackgroundSprite(backgroundSprite);

        // Set the default color and opacity
        setColor(ccc3(255.0f, 255.0f, 255.0f));
        setOpacity(255.0f);
        setOpacityModifyRGB(true);
        
        // Initialize the dispatch table
        
        CCString* tempString = CCString::create(label->getString());
        //tempString->autorelease();
        setTitleForState(tempString, CCControlStateNormal);
        setTitleColorForState(rgbaLabel->getColor(), CCControlStateNormal);
        setTitleLabelForState(node, CCControlStateNormal);
        setBackgroundSpriteForState(backgroundSprite, CCControlStateNormal);
        
        setLabelAnchorPoint(ccp(0.5f, 0.5f));

        // Layout update
        needsLayout();

        return true;
    }
    //couldn't init the CCControl
    else
    {
        return false;
    }
}

GWScale9Button* GWScale9Button::buttonWithLabelAndBackgroundSprite(CCNode* label, CCScale9Sprite* backgroundSprite)
{
    return GWScale9Button::create(label, backgroundSprite);
}

GWScale9Button* GWScale9Button::create(CCNode* label, CCScale9Sprite* backgroundSprite)
{
    GWScale9Button *pRet = new GWScale9Button();
    pRet->initWithLabelAndBackgroundSprite(label, backgroundSprite);
    pRet->autorelease();
    return pRet;
}

bool GWScale9Button::initWithTitleAndFontNameAndFontSize(string title, const char * fontName, float fontSize)
{
    CCLabelTTF *label = CCLabelTTF::create(title.c_str(), fontName, fontSize);
    return initWithLabelAndBackgroundSprite(label, CCScale9Sprite::create());
}

GWScale9Button* GWScale9Button::buttonWithTitleAndFontNameAndFontSize(string title, const char * fontName, float fontSize)
{
    return GWScale9Button::create(title, fontName, fontSize);
}

GWScale9Button* GWScale9Button::create(string title, const char * fontName, float fontSize)
{
    GWScale9Button *pRet = new GWScale9Button();
    pRet->initWithTitleAndFontNameAndFontSize(title, fontName, fontSize);
    pRet->autorelease();
    return pRet;
}

bool GWScale9Button::initWithBackgroundSprite(CCScale9Sprite* sprite)
{
    CCLabelTTF *label = CCLabelTTF::create("", "Arial", 30);//
    return initWithLabelAndBackgroundSprite(label, sprite);
}

GWScale9Button* GWScale9Button::buttonWithBackgroundSprite(CCScale9Sprite* sprite)
{
    return GWScale9Button::create(sprite);
}

GWScale9Button* GWScale9Button::create(CCScale9Sprite* sprite)
{
    GWScale9Button *pRet = new GWScale9Button();
    pRet->initWithBackgroundSprite(sprite);
    pRet->autorelease();
    return pRet;
}


void GWScale9Button::setMargins(int marginH, int marginV)
{
    m_marginV=marginV;
    m_marginH=marginH;
    needsLayout();
}

void GWScale9Button::setEnabled(bool enabled)
{
    CCControl::setEnabled(enabled);
    needsLayout();
}

void GWScale9Button::setSelected(bool enabled)
{
    CCControl::setSelected(enabled);
    needsLayout();
}

void GWScale9Button::setHighlighted(bool enabled)
{
    CCControl::setHighlighted(enabled);

    CCAction *action =getActionByTag(kZoomActionTag);
    if (action)
    {
        stopAction(action);        
    }
    needsLayout();
    if( m_zoomOnTouchDown )
    {
        float scaleValue = (isHighlighted() && isEnabled() && !isSelected()) ? 1.1f : 1.0f;
        CCAction *zoomAction =CCScaleTo::create(0.05f, scaleValue);
        zoomAction->setTag(kZoomActionTag);
        runAction(zoomAction);
    }
}

void GWScale9Button::setZoomOnTouchDown(bool zoomOnTouchDown)
{
    m_zoomOnTouchDown = zoomOnTouchDown;
}

bool GWScale9Button::getZoomOnTouchDown()
{
    return m_zoomOnTouchDown;
}

void GWScale9Button::setPreferredSize(CCSize size)
{
    if(size.width == 0 && size.height == 0)
    {
        m_doesAdjustBackgroundImage = true;
    }
    else
    {
        m_doesAdjustBackgroundImage = false;
        CCDictElement * item = NULL;
        CCDICT_FOREACH(m_backgroundSpriteDispatchTable, item)
        {
            CCScale9Sprite* sprite = (CCScale9Sprite*)item->getObject();
            sprite->setPreferredSize(size);
        }
    }

    m_preferredSize = size;
    needsLayout();
}

CCSize GWScale9Button::getPreferredSize()
{
    return m_preferredSize;
}

void GWScale9Button::setAdjustBackgroundImage(bool adjustBackgroundImage)
{
    m_doesAdjustBackgroundImage=adjustBackgroundImage;
    needsLayout();
}

bool GWScale9Button::doesAdjustBackgroundImage()
{
    return m_doesAdjustBackgroundImage;
}

CCPoint GWScale9Button::getLabelAnchorPoint()
{
    return this->m_labelAnchorPoint;
}

void GWScale9Button::setLabelAnchorPoint(CCPoint labelAnchorPoint)
{
    this->m_labelAnchorPoint = labelAnchorPoint;
    if (m_titleLabel != NULL)
    {
        this->m_titleLabel->setAnchorPoint(labelAnchorPoint);
    }
}

CCString* GWScale9Button::getTitleForState(CCControlState state)
{
    if (m_titleDispatchTable != NULL)
    {
        CCString* title=(CCString*)m_titleDispatchTable->objectForKey(state);    
        if (title)
        {
            return title;
        }
        return (CCString*)m_titleDispatchTable->objectForKey(CCControlStateNormal);
    }
    return CCString::create("");
}

void GWScale9Button::setTitleForState(CCString* title, CCControlState state)
{
    m_titleDispatchTable->removeObjectForKey(state);

    if (title)
    {
		CCString* dst = CCString::create("");
		
		/* 判断是否要从配置文件中获取字符串 */
		dst->m_sString = title->m_sString.substr(0, 1);
		if(dst->m_sString.compare("@") == 0) {
			title->m_sString = title->m_sString.substr(1, title->length());
		
			int strKey = title->intValue();

			CCString* src = CCString::create(I18N::shareI18N()->getcStringByKey(strKey));
			m_titleDispatchTable->setObject(src, state);
		}
		else {
			m_titleDispatchTable->setObject(title, state);
		}

    }
    
    // If the current state if equal to the given state we update the layout
    if (getState() == state)
    {
        needsLayout();
    }
}


const ccColor3B GWScale9Button::getTitleColorForState(CCControlState state)
{
    ccColor3B returnColor = ccWHITE;
    do 
    {
        CC_BREAK_IF(NULL == m_titleColorDispatchTable);
        CCColor3bObject* colorObject=(CCColor3bObject*)m_titleColorDispatchTable->objectForKey(state);    
        if (colorObject)
        {
            returnColor= colorObject->value;
            break;
        }

        colorObject=(CCColor3bObject*)m_titleColorDispatchTable->objectForKey(CCControlStateNormal);   
        if (colorObject)
        {
            returnColor=colorObject->value;
        }
    } while (0);

    return returnColor;
}

void GWScale9Button::setTitleColorForState(ccColor3B color, CCControlState state)
{
    //ccColor3B* colorValue=&color;
    m_titleColorDispatchTable->removeObjectForKey(state); 
    CCColor3bObject* pColor3bObject = new CCColor3bObject(color);
    pColor3bObject->autorelease();
    m_titleColorDispatchTable->setObject(pColor3bObject, state);
      
    // If the current state if equal to the given state we update the layout
    if (getState() == state)
    {
        needsLayout();
    }
}

CCNode* GWScale9Button::getTitleLabelForState(CCControlState state)
{
    CCNode* titleLabel=(CCNode*)m_titleLabelDispatchTable->objectForKey(state);    
    if (titleLabel)
    {
        return titleLabel;
    }
    return (CCNode*)m_titleLabelDispatchTable->objectForKey(CCControlStateNormal);
}

void GWScale9Button::setTitleLabelForState(CCNode* titleLabel, CCControlState state)
{
    CCNode* previousLabel = (CCNode*)m_titleLabelDispatchTable->objectForKey(state);
    if (previousLabel)
    {
        removeChild(previousLabel, true);
        m_titleLabelDispatchTable->removeObjectForKey(state);        
    }

    m_titleLabelDispatchTable->setObject(titleLabel, state);
    titleLabel->setVisible(false);
    titleLabel->setAnchorPoint(ccp(0.5f, 0.5f));
    addChild(titleLabel, 1);

    // If the current state if equal to the given state we update the layout
    if (getState() == state)
    {
        needsLayout();
    }
}

void GWScale9Button::setTitleTTFForState(const char * fntFile, CCControlState state)
{
    CCString * title = this->getTitleForState(state);
    if (!title)
    {
        title = CCString::create("");
    }
    this->setTitleLabelForState(CCLabelTTF::create(title->getCString(), fntFile, 12), state);
}

const char * GWScale9Button::getTitleTTFForState(CCControlState state)
{
    CCLabelProtocol* label = dynamic_cast<CCLabelProtocol*>(this->getTitleLabelForState(state));
    CCLabelTTF* labelTTF = dynamic_cast<CCLabelTTF*>(label);
    if(labelTTF != 0)
    {
        return labelTTF->getFontName();
    }
    else
    {
        return "";
    }
}

void GWScale9Button::setTitleTTFSizeForState(float size, CCControlState state)
{
    CCLabelProtocol* label = dynamic_cast<CCLabelProtocol*>(this->getTitleLabelForState(state));
    if(label)
    {
        CCLabelTTF* labelTTF = dynamic_cast<CCLabelTTF*>(label);
        if(labelTTF != 0)
        {
            return labelTTF->setFontSize(size);
        }
    }
}

float GWScale9Button::getTitleTTFSizeForState(CCControlState state)
{
    CCLabelProtocol* label = dynamic_cast<CCLabelProtocol*>(this->getTitleLabelForState(state));
    CCLabelTTF* labelTTF = dynamic_cast<CCLabelTTF*>(label);
    if(labelTTF != 0)
    {
        return labelTTF->getFontSize();
    }
    else
    {
        return 0;
    }
}

void GWScale9Button::setTitleBMFontForState(const char * fntFile, CCControlState state)
{
    CCString * title = this->getTitleForState(state);
    if (!title)
    {
        title = CCString::create("");
    }
    this->setTitleLabelForState(CCLabelBMFont::create(title->getCString(), fntFile), state);
}

const char * GWScale9Button::getTitleBMFontForState(CCControlState state)
{
    CCLabelProtocol* label = dynamic_cast<CCLabelProtocol*>(this->getTitleLabelForState(state));
    CCLabelBMFont* labelBMFont = dynamic_cast<CCLabelBMFont*>(label);
    if(labelBMFont != 0)
    {
        return labelBMFont->getFntFile();
    }
    else
    {
        return "";
    }
}


CCScale9Sprite* GWScale9Button::getBackgroundSpriteForState(CCControlState state)
{
    CCScale9Sprite* backgroundSprite=(CCScale9Sprite*)m_backgroundSpriteDispatchTable->objectForKey(state);    
    if (backgroundSprite)
    {
        return backgroundSprite;
    }
    return (CCScale9Sprite*)m_backgroundSpriteDispatchTable->objectForKey(CCControlStateNormal);
}


void GWScale9Button::setBackgroundSpriteForState(CCScale9Sprite* sprite, CCControlState state)
{
    CCSize oldPreferredSize = m_preferredSize;

    CCScale9Sprite* previousBackgroundSprite = (CCScale9Sprite*)m_backgroundSpriteDispatchTable->objectForKey(state);
    if (previousBackgroundSprite)
    {
        removeChild(previousBackgroundSprite, true);
        m_backgroundSpriteDispatchTable->removeObjectForKey(state);
    }

    m_backgroundSpriteDispatchTable->setObject(sprite, state);
    sprite->setVisible(false);
    sprite->setAnchorPoint(ccp(0.5f, 0.5f));
    addChild(sprite);

    if (this->m_preferredSize.width != 0 || this->m_preferredSize.height != 0)
    {
        if (oldPreferredSize.equals(m_preferredSize))
        {
            // Force update of preferred size
            sprite->setPreferredSize(CCSizeMake(oldPreferredSize.width+1, oldPreferredSize.height+1));
        }
        
        sprite->setPreferredSize(this->m_preferredSize);
    }

    // If the current state if equal to the given state we update the layout
    if (getState() == state)
    {
        needsLayout();
    }
}

void GWScale9Button::setBackgroundSpriteFrameForState(CCSpriteFrame * spriteFrame, CCControlState state)
{
    CCScale9Sprite * sprite = CCScale9Sprite::createWithSpriteFrame(spriteFrame);
    this->setBackgroundSpriteForState(sprite, state);
}


void GWScale9Button::needsLayout()
{
    if (!m_bParentInited) {
        return;
    }
    // Hide the background and the label
    if (m_titleLabel != NULL) {
        m_titleLabel->setVisible(false);
    }
    if (m_backgroundSprite) {
        m_backgroundSprite->setVisible(false);
    }
    // Update anchor of all labels
    this->setLabelAnchorPoint(this->m_labelAnchorPoint);
    
    // Update the label to match with the current state
    CC_SAFE_RELEASE(m_currentTitle);
    m_currentTitle = getTitleForState(m_eState);
    CC_SAFE_RETAIN(m_currentTitle);

    m_currentTitleColor=getTitleColorForState(m_eState);

    this->setTitleLabel(getTitleLabelForState(m_eState));

    CCLabelProtocol* label = dynamic_cast<CCLabelProtocol*>(m_titleLabel);
    if (label && m_currentTitle)
    {
        label->setString(m_currentTitle->getCString());
    }

    CCRGBAProtocol* rgbaLabel = dynamic_cast<CCRGBAProtocol*>(m_titleLabel);
    if (rgbaLabel)
    {
        rgbaLabel->setColor(m_currentTitleColor);
    }
    if (m_titleLabel != NULL)
    {
        m_titleLabel->setPosition(ccp (getContentSize().width / 2, getContentSize().height / 2));
    }
    
    // Update the background sprite
    this->setBackgroundSprite(this->getBackgroundSpriteForState(m_eState));
    if (m_backgroundSprite != NULL)
    {
        m_backgroundSprite->setPosition(ccp (getContentSize().width / 2, getContentSize().height / 2));
    }
   
    // Get the title label size
    CCSize titleLabelSize;
    if (m_titleLabel != NULL)
    {
        titleLabelSize = m_titleLabel->boundingBox().size;
    }
    
    // Adjust the background image if necessary
    if (m_doesAdjustBackgroundImage)
    {
        // Add the margins
        if (m_backgroundSprite != NULL)
        {
            m_backgroundSprite->setContentSize(CCSizeMake(titleLabelSize.width + m_marginH * 2, titleLabelSize.height + m_marginV * 2));
        }
    } 
    else
    {        
        //TODO: should this also have margins if one of the preferred sizes is relaxed?
        if (m_backgroundSprite != NULL)
        {
            CCSize preferredSize = m_backgroundSprite->getPreferredSize();
            if (preferredSize.width <= 0)
            {
                preferredSize.width = titleLabelSize.width;
            }
            if (preferredSize.height <= 0)
            {
                preferredSize.height = titleLabelSize.height;
            }

            m_backgroundSprite->setContentSize(preferredSize);
        }
    }
    
    // Set the content size
    CCRect rectTitle;
    if (m_titleLabel != NULL)
    {
        rectTitle = m_titleLabel->boundingBox();
    }
    CCRect rectBackground;
    if (m_backgroundSprite != NULL)
    {
        rectBackground = m_backgroundSprite->boundingBox();
    }

    CCRect maxRect = CCControlUtils::CCRectUnion(rectTitle, rectBackground);
    setContentSize(CCSizeMake(maxRect.size.width, maxRect.size.height));        
    
    if (m_titleLabel != NULL)
    {
        m_titleLabel->setPosition(ccp(getContentSize().width/2, getContentSize().height/2));
        // Make visible the background and the label
        m_titleLabel->setVisible(true);
    }
  
    if (m_backgroundSprite != NULL)
    {
        m_backgroundSprite->setPosition(ccp(getContentSize().width/2, getContentSize().height/2));
        m_backgroundSprite->setVisible(true);   
    }   
}



bool GWScale9Button::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if (!isTouchInside(pTouch) || !isEnabled() || !isVisible())
    {
        return false;
    }
    
    m_eState=CCControlStateHighlighted;
    m_isPushed=true;
    this->setHighlighted(true);
    sendActionsForControlEvents(CCControlEventTouchDown);
    return true;
}

void GWScale9Button::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{    
    if (!isEnabled() || !isPushed() || isSelected())
    {
        if (isHighlighted())
        {
            setHighlighted(false);
        }
        return;
    }
    
    bool isTouchMoveInside = isTouchInside(pTouch);
    if (isTouchMoveInside && !isHighlighted())
    {
        m_eState = CCControlStateHighlighted;
        setHighlighted(true);
        sendActionsForControlEvents(CCControlEventTouchDragEnter);
    }
    else if (isTouchMoveInside && isHighlighted())
    {
        sendActionsForControlEvents(CCControlEventTouchDragInside);
    }
    else if (!isTouchMoveInside && isHighlighted())
    {
        m_eState = CCControlStateNormal;
        setHighlighted(false);
        
        sendActionsForControlEvents(CCControlEventTouchDragExit);        
    }
    else if (!isTouchMoveInside && !isHighlighted())
    {
        sendActionsForControlEvents(CCControlEventTouchDragOutside);        
    }
}
void GWScale9Button::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    m_eState = CCControlStateNormal;
    m_isPushed = false;
    setHighlighted(false);
    
    
    if (isTouchInside(pTouch))
    {
        sendActionsForControlEvents(CCControlEventTouchUpInside);        
    }
    else
    {
        sendActionsForControlEvents(CCControlEventTouchUpOutside);        
    }
}

void GWScale9Button::setOpacity(GLubyte opacity)
{
    m_cOpacity = opacity;
    
    CCObject* child;
    CCArray* children=getChildren();
    CCARRAY_FOREACH(children, child)
    {
        CCRGBAProtocol* pNode = dynamic_cast<CCRGBAProtocol*>(child);        
        if (pNode)
        {
            pNode->setOpacity(opacity);
        }
    }
    CCDictElement * item = NULL;
    CCDICT_FOREACH(m_backgroundSpriteDispatchTable, item)
    {
        CCScale9Sprite* sprite = (CCScale9Sprite*)item->getObject();
        sprite->setOpacity(opacity);
    }
}

GLubyte GWScale9Button::getOpacity()
{
    return m_cOpacity;
}

void GWScale9Button::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    m_eState = CCControlStateNormal;
    m_isPushed = false;
    setHighlighted(false);
    sendActionsForControlEvents(CCControlEventTouchCancel);
}

GWScale9Button* GWScale9Button::create()
{
    GWScale9Button *pControlButton = new GWScale9Button();
    if (pControlButton && pControlButton->init())
    {
        pControlButton->autorelease();
        return pControlButton;
    }
    CC_SAFE_DELETE(pControlButton);
    return NULL;
}

GWScale9Button* GWScale9Button::node()
{
    return GWScale9Button::create();
}