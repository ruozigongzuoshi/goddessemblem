/*
    文件名：    GWScale9Button.h
    描　述：    普通按钮, 直接拷贝CCScale9Button.h的代码而不使用组合, 避免组合出现的很多麻烦
    
*/
#ifndef __GW_SCALE9_BUTTON_H__
#define __GW_SCALE9_BUTTON_H__

#include "cocos-ext.h"
#include "GWBase.h"

/* Define the button margin for Left/Right edge */
#define CCControlButtonMarginLR 8 // px
/* Define the button margin for Top/Bottom edge */
#define CCControlButtonMarginTB 2 // px

class GWScale9Button : public GWBase
{        
public:
    GWScale9Button();
    virtual ~GWScale9Button();
    virtual void needsLayout(void);

    virtual void setEnabled(bool enabled);
    virtual void setSelected(bool enabled);
    virtual void setHighlighted(bool enabled);
protected:
    /** The current title that is displayed on the button. 当前显示的按钮标题 */
    CC_SYNTHESIZE_READONLY(CCString*, m_currentTitle, CurrentTitle);

    /** The current color used to display the title. 当前按钮标题颜色 */
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(ccColor3B, m_currentTitleColor, CurrentTitleColor);

    /** 
        Adjust the background image. YES by default. If the property is set to NO, the 
        background will use the prefered size of the background image. 

        设置是否根据标题大小自动调整按钮大小, 如果否, 则根据prefered的大小来锁定按钮大小
    */
    bool doesAdjustBackgroundImage();
    void setAdjustBackgroundImage(bool adjustBackgroundImage);
    bool m_doesAdjustBackgroundImage;

    /** The current title label. 当前的标题标签 */
    CC_SYNTHESIZE_RETAIN(CCNode*, m_titleLabel, TitleLabel);

    /** The current background sprite.  当前按钮图片 */
    CC_SYNTHESIZE_RETAIN(CCScale9Sprite*, m_backgroundSprite, BackgroundSprite);

    /** 
        The prefered size of the button, if label is larger it will be expanded.
        按钮大小,如果标题标签大于这个值,则自动扩展(除非AdjustBackgroundImage为false)
    */
    CC_PROPERTY(CCSize, m_preferredSize, PreferredSize);

    /** Adjust the button zooming on touchdown. Default value is YES. */
    CC_PROPERTY(bool, m_zoomOnTouchDown, ZoomOnTouchDown);

    /** 按钮标签的基准点 */
    CC_PROPERTY(CCPoint, m_labelAnchorPoint, LabelAnchorPoint);

    /* 
        Override setter to affect a background sprite too 
        重写函数, 是为了设置背景精灵的透明度
    */
    virtual GLubyte getOpacity(void);
    virtual void setOpacity(GLubyte var);
    
    /** Flag to know if the button is currently pushed.  */
protected:
    bool m_isPushed;
    bool m_bParentInited;
public:
    bool isPushed() { return m_isPushed; }

    // <CCControlState, CCString*>
    CC_SYNTHESIZE_RETAIN(CCDictionary*, m_titleDispatchTable, TitleDispatchTable);
    // <CCControlState, CCColor3bObject*>
    CC_SYNTHESIZE_RETAIN(CCDictionary*, m_titleColorDispatchTable, TitleColorDispatchTable);
    // <CCControlState, CCNode*>
    CC_SYNTHESIZE_RETAIN(CCDictionary*, m_titleLabelDispatchTable, TitleLabelDispatchTable);
    // <CCControlState, CCScale9Sprite*>
    CC_SYNTHESIZE_RETAIN(CCDictionary*, m_backgroundSpriteDispatchTable, BackgroundSpriteDispatchTable);

    /* Define the button margin for Top/Bottom edge */
    CC_SYNTHESIZE_READONLY(int, m_marginV, VerticalMargin);
    /* Define the button margin for Left/Right edge */
    CC_SYNTHESIZE_READONLY(int, m_marginH, HorizontalOrigin);
    //set the margins at once (so we only have to do one call of needsLayout)
    virtual void setMargins(int marginH, int marginV);


public:
    virtual bool init();
    virtual bool initWithLabelAndBackgroundSprite(CCNode* label, CCScale9Sprite* backgroundSprite);
    //@deprecated: This interface will be deprecated sooner or later.
    CC_DEPRECATED_ATTRIBUTE static GWScale9Button* buttonWithLabelAndBackgroundSprite(CCNode* label, CCScale9Sprite* backgroundSprite);
    static GWScale9Button* create(CCNode* label, CCScale9Sprite* backgroundSprite);
    
    virtual bool initWithTitleAndFontNameAndFontSize(std::string title, const char * fontName, float fontSize);
    //@deprecated: This interface will be deprecated sooner or later.
    CC_DEPRECATED_ATTRIBUTE static GWScale9Button* buttonWithTitleAndFontNameAndFontSize(std::string title, const char * fontName, float fontSize);

    static GWScale9Button* create(std::string title, const char * fontName, float fontSize);
    
    virtual bool initWithBackgroundSprite(CCScale9Sprite* sprite);

    //@deprecated: This interface will be deprecated sooner or later.
    CC_DEPRECATED_ATTRIBUTE static GWScale9Button* buttonWithBackgroundSprite(CCScale9Sprite* sprite);

    static GWScale9Button* create(CCScale9Sprite* sprite);
    
    //events
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

    /**
    * Returns the title used for a state.
    *
    * @param state The state that uses the title. Possible values are described in
    * "CCControlState".
    *
    * @return The title for the specified state.
    */
    virtual CCString* getTitleForState(CCControlState state);

    /**
    * Sets the title string to use for the specified state.
    * If a property is not specified for a state, the default is to use
    * the CCButtonStateNormal value.
    *
    * @param title The title string to use for the specified state.
    * @param state The state that uses the specified title. The values are described
    * in "CCControlState".
    */
    virtual void setTitleForState(CCString* title, CCControlState state);

    /**
    * Returns the title color used for a state.
    *
    * @param state The state that uses the specified color. The values are described
    * in "CCControlState".
    *
    * @return The color of the title for the specified state.
    */

    virtual const ccColor3B getTitleColorForState(CCControlState state);

    /**
    * Sets the color of the title to use for the specified state.
    *
    * @param color The color of the title to use for the specified state.
    * @param state The state that uses the specified color. The values are described
    * in "CCControlState".
    */
    virtual void setTitleColorForState(ccColor3B color, CCControlState state);

    /**
    * Returns the title label used for a state.
    *
    * @param state The state that uses the title label. Possible values are described
    * in "CCControlState".
    */
    virtual CCNode* getTitleLabelForState(CCControlState state);

    /**
    * Sets the title label to use for the specified state.
    * If a property is not specified for a state, the default is to use
    * the CCButtonStateNormal value.
    *
    * @param title The title label to use for the specified state.
    * @param state The state that uses the specified title. The values are described
    * in "CCControlState".
    */
    virtual void setTitleLabelForState(CCNode* label, CCControlState state);

    virtual void setTitleTTFForState(const char * fntFile, CCControlState state);
    virtual const char * getTitleTTFForState(CCControlState state);

    virtual void setTitleTTFSizeForState(float size, CCControlState state);
    virtual float getTitleTTFSizeForState(CCControlState state);

    /**
     * Sets the font of the label, changes the label to a CCLabelBMFont if neccessary.
     * @param fntFile The name of the font to change to
     * @param state The state that uses the specified fntFile. The values are described
     * in "CCControlState".
     */
    virtual void setTitleBMFontForState(const char * fntFile, CCControlState state);
    virtual const char * getTitleBMFontForState(CCControlState state);

    /**
    * Returns the background sprite used for a state.
    *
    * @param state The state that uses the background sprite. Possible values are
    * described in "CCControlState".
    */
    virtual CCScale9Sprite* getBackgroundSpriteForState(CCControlState state);

    /**
    * Sets the background sprite to use for the specified button state.
    *
    * @param sprite The background sprite to use for the specified state.
    * @param state The state that uses the specified image. The values are described
    * in "CCControlState".
    */
    virtual void setBackgroundSpriteForState(CCScale9Sprite* sprite, CCControlState state);

    /**
     * Sets the background spriteFrame to use for the specified button state.
     *
     * @param spriteFrame The background spriteFrame to use for the specified state.
     * @param state The state that uses the specified image. The values are described
     * in "CCControlState".
     */
    virtual void setBackgroundSpriteFrameForState(CCSpriteFrame * spriteFrame, CCControlState state);

    CC_DEPRECATED_ATTRIBUTE static GWScale9Button * node();
    static GWScale9Button* create();
	GLubyte m_cOpacity;
};

// end of GUI group
/// @}
/// @}

#endif