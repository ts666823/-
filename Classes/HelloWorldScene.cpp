#include "HelloWorldScene.h"
#include"MyScene.h"
#include "SimpleAudioEngine.h" 

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

//���ϼ���
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

//��ʼ��
bool HelloWorld::init()
{

	if (!Scene::init())
	{
		return false;
	}

	//��Ч������
	//��ȡһ��UserDefault��ʵ��
	auto userDef = UserDefault::getInstance();
	/*//0��ʾ�����֣�1��ʾ�����֣�2��ʾ������
	if (userDef->getIntegerForKey(MUSICKEY, 2) == 2);
	{
		userDef->setIntegerForKey(MUSICKEY, 0);
	}

	if (userDef->getIntegerForKey(SOUNDKEY, 2) == 2);
	{
		userDef->setIntegerForKey(SOUNDKEY, 0);
	}*/

	auto audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
	audioEngine->preloadBackgroundMusic("music_bg.mp3");
	audioEngine->preloadBackgroundMusic("music_bg_HelloWorldScene.mp3");
	audioEngine->preloadBackgroundMusic("BGM.mp3");
	audioEngine->preloadBackgroundMusic("gameoverMusic.mp3");
	audioEngine->preloadEffect("music_remove.wav");
	audioEngine->preloadEffect("music_fail.wav");
	audioEngine->preloadEffect("music_gameOver.wav");
	audioEngine->preloadEffect("music_win.wav");



	// ѭ�����ű�������
	audioEngine->playBackgroundMusic("BGM.mp3", true);

	//�����Ļ�ߴ�
	const auto visibleSize = Director::getInstance()->getVisibleSize();
	const Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//����һ�����顣
	auto sprite = Sprite::create("background.jpg");
	if (sprite == nullptr)
	{
		problemLoading("'HelloWorld.png'");
	}
	else
	{
		// position the sprite on the center of the screen
		sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

		/*float visw = visibleSize.width; //��ȡ��Ļ���
		float vish = visibleSize.height;//��ȡ��Ļ�߶�
		float spx = sprite->getTextureRect().getMaxX();
		float spy = sprite->getTextureRect().getMaxY();
		sprite->setScaleX(visw / spx); //���þ��������ű���
		sprite->setScaleY(vish / spy);*/
		

		// add the sprite as a child to this layer
		this->addChild(sprite, 0);
	}

	//����һ��"Pop Star"��label��
	auto label = Label::createWithTTF("Pop Star", "fonts/Marker Felt.ttf", 24);
	label->setColor(Color3B::WHITE);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));
	this->addChild(label, 1);

	//����һ���رհ�ť��
	auto closeItem = MenuItemImage::create(
		"quit.png",
		"quit.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		closeItem->setContentSize(Size(249, 72));
		closeItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 100));

	}

	//����һ����ʼ��ť
	auto goItem = MenuItemImage::create(
		"begin.png",		
		"begin.png",
		CC_CALLBACK_1(HelloWorld::menuNextCallback, this));
	if (goItem == nullptr ||
		goItem->getContentSize().width <= 0 ||
		goItem->getContentSize().height <= 0)
	{
		problemLoading("'begin.png' and 'begin.png'");
	}
	else
	{
		goItem->setContentSize(Size(249, 72));
		goItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 100));
	}
	

	//�����˵�
	auto menu = Menu::create(closeItem, goItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);



	//����BGM���ذ�ť
	auto MusicOnItem = MenuItemImage::create(
		"sound_on.png",
		"sound_on.png");
	auto MusicOffItem = MenuItemImage::create(
		"sound_off.png",
		"sound_off.png");
	MenuItemToggle* toggleItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(HelloWorld::musicCallback, this), MusicOnItem, MusicOffItem, NULL);

	auto toggleMenu = Menu::create(toggleItem, NULL);
	toggleMenu->setPosition(Vec2(20, visibleSize.height));
	this->addChild(toggleMenu, 1);

	return true;
	
}

//�رհ�ť�ĺ���
void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

//��ʼ��ť�ĺ���
void HelloWorld::menuNextCallback(Ref* pSender)
{
	//ת��Ч��
	Scene* gameScene = MyScene::createScene(0);
	TransitionScene* transition = CCTransitionCrossFade::create(1, gameScene);
	Director::getInstance()->replaceScene(transition);
}

void HelloWorld::musicCallback(Ref* pSender)
{
	if (musicStatus)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
		musicStatus = false;
	}
	else
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("BGM.mp3", true);
		musicStatus = true;
	}
}
