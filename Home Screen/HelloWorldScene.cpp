#include "HelloWorldScene.h"
//下一个场景
#include "MyScene.h"
//声音引擎
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

//故障加载
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

//初始化
bool HelloWorld::init()
{
   
    if ( !Scene::init() )
    {
        return false;
    }
	
	/*//音效和音乐
	//获取一个UserDefault的实例
	auto userDef = UserDefault::getInstance();
	//0表示有音乐，1表示无音乐，2表示不存在
	if (userDef->getIntegerForKey(MUSICKEY, 2)==2);
	{
		userDef->setIntegerForKey(MUSICKEY, 0);
	}

	if (userDef->getIntegerForKey(SOUNDKEY, 2) == 2);
	{
		userDef->setIntegerForKey(SOUNDKEY, 0);
	}

	//提前加载音乐文件
	auto audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
	audioEngine->preloadBackgroundMusic("music_bg.mp3");
	audioEngine->preloadBackgroundMusic("music_bg_HelloWorldScene.mp3");
	audioEngine->preloadEffect("music_remove.wav");
	audioEngine->preloadEffect("music_fail.wav");
	audioEngine->preloadEffect("music_gameOver.wav");
	audioEngine->preloadEffect("music_win.wav");*/

	//获得屏幕尺寸
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//设置一个精灵。
	auto sprite = Sprite::create("HelloWorld.png");
	if (sprite == nullptr)
	{
		problemLoading("'HelloWorld.png'");
	}
	else
	{
		// position the sprite on the center of the screen
		sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

		// add the sprite as a child to this layer
		this->addChild(sprite, 0);
	}

	//设置一个"Pop Star"的label；
	auto label = Label::createWithTTF("Pop Star","fonts/Marker Felt.ttf", 24);
	label-> setColor(Color3B::WHITE);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));
	this->addChild(label, 1);

	//设置一个关闭按钮：
    auto closeItem = MenuItemImage::create(
										   "begin.png",
                                           "begin.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + visibleSize.height-closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

	//设置一个开始按钮
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
		goItem->setPosition(Vec2(origin.x + visibleSize.width / 2 , origin.y / 2+visibleSize.height/2- sprite->getContentSize().height/2));
	}

	//创建菜单
    auto menu = Menu::create(closeItem,goItem ,NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    return true;
}

//关闭按钮的函数
void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

//开始按钮的函数
void HelloWorld::menuNextCallback(Ref* pSender)
{
	//转场效果
	Scene* gameScene = MyScene::createScene();
	TransitionScene* transition = CCTransitionCrossFade::create(1, gameScene);
	Director::getInstance()->replaceScene(transition);
}
