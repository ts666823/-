#include "GameOverScene.h"
//��һ������
#include "HelloWorldScene.h"

#include "SimpleAudioEngine.h"

#include"ScoreScene.h"

USING_NS_CC;

Scene* GameOver::createScene()
{
	auto scene = Scene::create();
	auto layer = GameOver::create();
	scene->addChild(layer);
	return scene;
}

//���ϼ���
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GameOvere.cpp\n");
}

bool GameOver::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	bool bRect = false;

	//��������
	if (CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
	{
		auto userDef = UserDefault::getInstance();
		auto audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
		audioEngine->preloadBackgroundMusic("gameoverMusic.mp3");
		audioEngine->playBackgroundMusic("gameoverMusic.mp3", true);
	}

	do
	{
		//�����Ļ�ߴ�
		const auto visibleSize = Director::getInstance()->getVisibleSize();
		const Vec2 origin = Director::getInstance()->getVisibleOrigin();


		//��ӱ���ͼƬ
		auto m_background = Sprite::create("GameOver.jpeg");
		m_background->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
		m_background->setAnchorPoint(Vec2(0.5, 0.5));
		CC_BREAK_IF(!m_background);

		this->addChild(m_background);
		

		/////////////////////////////
		// 2. add a menu item with "X" image, which is clicked to quit the program
		//    you may modify it.

		//�����˳���Ϸ��ť��
		auto closeItem = MenuItemImage::create(
			"quit.png",
			"quit.png",
			CC_CALLBACK_1(GameOver::menuCloseCallback, this));

		if (closeItem == nullptr ||
			closeItem->getContentSize().width <= 0 ||
			closeItem->getContentSize().height <= 0)
		{
			problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
		}
		else
		{
			closeItem->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2 + 100));

		}

		//����һ����ʼ��ť
		auto backItem = MenuItemImage::create(
			"startAgain.png",
			"startAgain.png",
			CC_CALLBACK_1(GameOver::menuMainCallback, this));
		if (backItem == nullptr ||
			backItem->getContentSize().width <= 0 ||
			backItem->getContentSize().height <= 0)
		{
			problemLoading("'begin.png' and 'begin.png'");
		}
		else
		{
			backItem->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2 - 100));
		};



	auto menu = Menu::create(closeItem, backItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	bRect = true;
} while (0);

	/////////////////////////////
	// 3. add your codes below...


	return true;
}


// �˳���Ϸ
void GameOver::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

// ����������
void GameOver::menuMainCallback(cocos2d::Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
	Director::getInstance()->replaceScene(TransitionProgressRadialCCW::create(0.8f, HelloWorld::createScene()));
}

