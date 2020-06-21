#include "Gamepause.h"
#include "MyScene.h"
#include"HelloWorldScene.h"
//传入一个CCrenderTexture 
//相当于一个正在运行的游戏的截图作为这个暂停对话框的背景 
//这样就看起来像是对话框在游戏界面之上，一般游戏当中都是这样子写的。
CCScene* Gamepause::scene(CCRenderTexture* sqr)
{

	CCScene* scene = CCScene::create();
	Gamepause* layer = Gamepause::create();
	scene->addChild(layer, 1);//把游戏层放上面，我们还要在这上面放按钮


//增加部分：使用Game界面中截图的sqr纹理图片创建Sprite
//并将Sprite添加到GamePause场景层中
//得到窗口的大小
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCSprite* back_spr = CCSprite::createWithTexture(sqr->getSprite()->getTexture());
	back_spr->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2)); //放置位置,这个相对于中心位置。
	back_spr->setFlipY(true);            //翻转，因为UI坐标和OpenGL坐标不同
	back_spr->setColor(ccc3(128,128,128)); //图片颜色变灰色
	scene->addChild(back_spr);


	//添加游戏暂停背景小图，用来放按钮
	CCSprite* back_small_spr = CCSprite::create("pauseBackground.jpg");
	back_small_spr->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2)); //放置位置,这个相对于中心位置。
	scene->addChild(back_small_spr);


	return scene;
}

bool Gamepause::init()
{

	if (!CCLayer::init())
	{
		return false;
	}
	//得到窗口的大小
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	//原点坐标
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	//继续游戏按钮
	CCMenuItemImage* pContinueItem = CCMenuItemImage::create(
		"resume.png",
		"resume.png",
		this,
		menu_selector(Gamepause::menuContinueCallback));

	pContinueItem->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2 + 150));

	//重新开始游戏按钮
	CCMenuItemImage* pRestartItem = CCMenuItemImage::create(
		"startAgain.png",
		"startAgain.png",
		this,
		menu_selector(Gamepause::menuRestart));

	pRestartItem->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2 - 50));

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pContinueItem, pRestartItem, NULL);
	pMenu->setPosition(Vec2::ZERO);
	this->addChild(pMenu, 2);

	return true;
}
//继续游戏
void Gamepause::menuContinueCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->popScene();

}
//重新开始游戏
void  Gamepause::menuRestart(CCObject* pSender)
{
	Director::getInstance()->replaceScene(TransitionProgressRadialCCW::create(0.8f, HelloWorld::createScene()));
}
