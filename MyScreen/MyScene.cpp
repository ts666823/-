#include "MyScene.h"
USING_NS_CC;
//创建场景
Scene* MyScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MyScene::create();
	scene->addChild(layer);
	return scene;
}
//初始化方式
bool MyScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	//获取整个手机可视屏幕尺寸
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//获取手机可视屏原点的坐标
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//创建一个显示"MyScene"文字的Label
	auto label = Label::createWithTTF("MyScene", "fonts/Marker Felt.ttf", 24);
	//设置白色
	label->setColor(Color3B::WHITE);
	// 设置label在屏幕中的显示位置
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));
	// 把label添加到画面层
	this->addChild(label, 1);
	auto sprite = Sprite::create("1.jpg");
		// position the sprite on the center of the screen
		sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

		// add the sprite as a child to this layer
		this->addChild(sprite, 0);
	createPopSprite(visibleSize);
	return true;
}
//添加产生的方阵
void MyScene::createPopSprite(Size size) {
	//添加随机种子
	srand(((unsigned)time(NULL)));
	//每一个色块的长宽设置
	int len = (size.width) / 10;
	//放置色块
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			//产生1到4的随机数
			int randColor = rand() % 4 + 1;
			//
			PopSprite* block = PopSprite::createPopSprite(-1, len, len, len*j,len*i+size.height/6);
			//设置坐标和颜色
			block->setPopX(i);
			block->setPopY(j);
			block->setColor(randColor);
			//把精灵添加到当前场景中
			addChild(block);
			//添加到数组中；
			popStarSprite[i][j] = block;
		}
	}
}