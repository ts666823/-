#include "Gamepause.h"
#include "MyScene.h"
#include"HelloWorldScene.h"
//����һ��CCrenderTexture 
//�൱��һ���������е���Ϸ�Ľ�ͼ��Ϊ�����ͣ�Ի���ı��� 
//�����Ϳ��������ǶԻ�������Ϸ����֮�ϣ�һ����Ϸ���ж���������д�ġ�
CCScene* Gamepause::scene(CCRenderTexture* sqr)
{

	CCScene* scene = CCScene::create();
	Gamepause* layer = Gamepause::create();
	scene->addChild(layer, 1);//����Ϸ������棬���ǻ�Ҫ��������Ű�ť


//���Ӳ��֣�ʹ��Game�����н�ͼ��sqr����ͼƬ����Sprite
//����Sprite��ӵ�GamePause��������
//�õ����ڵĴ�С
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCSprite* back_spr = CCSprite::createWithTexture(sqr->getSprite()->getTexture());
	back_spr->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2)); //����λ��,������������λ�á�
	back_spr->setFlipY(true);            //��ת����ΪUI�����OpenGL���겻ͬ
	back_spr->setColor(ccc3(128,128,128)); //ͼƬ��ɫ���ɫ
	scene->addChild(back_spr);


	//�����Ϸ��ͣ����Сͼ�������Ű�ť
	CCSprite* back_small_spr = CCSprite::create("pauseBackground.jpg");
	back_small_spr->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2)); //����λ��,������������λ�á�
	scene->addChild(back_small_spr);


	return scene;
}

bool Gamepause::init()
{

	if (!CCLayer::init())
	{
		return false;
	}
	//�õ����ڵĴ�С
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	//ԭ������
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	//������Ϸ��ť
	CCMenuItemImage* pContinueItem = CCMenuItemImage::create(
		"resume.png",
		"resume.png",
		this,
		menu_selector(Gamepause::menuContinueCallback));

	pContinueItem->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2 + 150));

	//���¿�ʼ��Ϸ��ť
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
//������Ϸ
void Gamepause::menuContinueCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->popScene();

}
//���¿�ʼ��Ϸ
void  Gamepause::menuRestart(CCObject* pSender)
{
	Director::getInstance()->replaceScene(TransitionProgressRadialCCW::create(0.8f, HelloWorld::createScene()));
}
