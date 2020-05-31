#include "MyScene.h"
USING_NS_CC;
//��������
Scene* MyScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MyScene::create();
	scene->addChild(layer);
	return scene;
}
//��ʼ����ʽ
bool MyScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	//��ȡ�����ֻ�������Ļ�ߴ�
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//��ȡ�ֻ�������ԭ�������
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//����һ����ʾ"MyScene"���ֵ�Label
	auto label = Label::createWithTTF("MyScene", "fonts/Marker Felt.ttf", 24);
	//���ð�ɫ
	label->setColor(Color3B::WHITE);
	// ����label����Ļ�е���ʾλ��
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));
	// ��label��ӵ������
	this->addChild(label, 1);
	auto sprite = Sprite::create("1.jpg");
		// position the sprite on the center of the screen
		sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

		// add the sprite as a child to this layer
		this->addChild(sprite, 0);
	createPopSprite(visibleSize);
	return true;
}
//��Ӳ����ķ���
void MyScene::createPopSprite(Size size) {
	//����������
	srand(((unsigned)time(NULL)));
	//ÿһ��ɫ��ĳ�������
	int len = (size.width) / 10;
	//����ɫ��
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			//����1��4�������
			int randColor = rand() % 4 + 1;
			//
			PopSprite* block = PopSprite::createPopSprite(-1, len, len, len*j,len*i+size.height/6);
			//�����������ɫ
			block->setPopX(i);
			block->setPopY(j);
			block->setColor(randColor);
			//�Ѿ�����ӵ���ǰ������
			addChild(block);
			//��ӵ������У�
			popStarSprite[i][j] = block;
		}
	}
}