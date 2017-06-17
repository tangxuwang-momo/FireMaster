#include "cocos2d.h"
#include "FireMaster.h"
#include "SimpleAudioEngine.h"
#include "AppDelegate.h"

using namespace CocosDenshion;

using namespace ui;
Scene* FireMaster::createScene() {
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = FireMaster::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool FireMaster::init()
{
	//super init first
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	addSprite();
	return true;
}

void FireMaster::addSprite() {
	//add background
	auto bgSprite = Sprite::create("imges/bg2.png");
	bgSprite->setPosition(visibleSize / 2);
	bgSprite->setScale(visibleSize.width / bgSprite->getContentSize().width, visibleSize.height / bgSprite->getContentSize().height);
	this->addChild(bgSprite, 0);

	auto tankScaleSize = 0.7; //设置坦克缩放大小
	//add yellow tank
	yellowTank = Sprite::createWithSpriteFrameName("yellowAttack1.png");
	yellowTank->setAnchorPoint(Point(0.5, 0.5));
	yellowTank->setPosition(visibleSize.width - 100, 100);
	yellowTank->setScale(tankScaleSize);
	yellowTank->setFlipX(true);
	//车动画，到时候删，现在先在这运行看看效果
	auto yTankAttackAnimate = Animate::create(AnimationCache::getInstance()->getAnimation("yellowTankAttackAnimation"));
	yellowTank->runAction(RepeatForever::create(yTankAttackAnimate));
	this->addChild(yellowTank, 1);

	//explosion动画展示，到时候删
	auto explosion = Sprite::createWithSpriteFrameName("explosion1.png");
	explosion->setAnchorPoint(Point(0.5, 0.5));
	explosion->setPosition(visibleSize.width/2, visibleSize.height/2);
	auto explosionAnimate = Animate::create(AnimationCache::getInstance()->getAnimation("explosionAnimation"));
	explosion->runAction(RepeatForever::create(explosionAnimate));
	this->addChild(explosion, 1);

	//add blue tank
	blueTank = Sprite::createWithSpriteFrameName("blueAttack1.png");
	blueTank->setAnchorPoint(Point(0.5, 0.5));
	blueTank->setPosition(100, 100);
	blueTank->setScale(tankScaleSize);
	this->addChild(blueTank, 1); 

	//add obstacle
	obstacle = Sprite::createWithSpriteFrameName("obstacle.png");
	obstacle->setAnchorPoint(Point(0.5, 0.5));
	obstacle->setPosition(visibleSize.width / 2, 120);
	obstacle->setScale(1.3, 1.4);
	this->addChild(obstacle, 1);

    //add UI
	topUI = Sprite::createWithSpriteFrameName("topUI.png");
	topUI->setAnchorPoint(Point(0.5, 0.5));
	topUI->setPosition(visibleSize.width / 2, visibleSize.height - 80);
	topUI->setScale(1.4, 1.3);
	this->addChild(topUI, 1);

	//add powerBullet_Btn1
	powerBullet_Btn1 = Button::create("imges/tank_bullet4.png", "imges/tank_bullet4.png");
	powerBullet_Btn1->setPosition(Vec2(visibleSize.width / 12, visibleSize.height * 8.1 / 10 ));
	powerBullet_Btn1->addTouchEventListener(CC_CALLBACK_1(FireMaster::powerBullet_Btn1_click, this));
	this->addChild(powerBullet_Btn1, 1);

	//add fix_Btn1
	fix_Btn1 = Button::create("imges/tanks_crateRepair.png", "imges/tanks_crateRepair.png");
	fix_Btn1->setPosition(Vec2(visibleSize.width * 17 / 96, visibleSize.height * 8.1 / 10));
	fix_Btn1->setScale(0.5);
	fix_Btn1->addTouchEventListener(CC_CALLBACK_1(FireMaster::fix_Btn1_click, this));
	this->addChild(fix_Btn1, 1);

	//add defence_Btn1
	defence_Btn1 = Button::create("imges/tanks_crateArmor.png", "imges/tanks_crateArmor.png");
	defence_Btn1->setPosition(Vec2(visibleSize.width * 25 / 96 , visibleSize.height * 8.1 / 10));
	defence_Btn1->setScale(0.5);
	defence_Btn1->addTouchEventListener(CC_CALLBACK_1(FireMaster::defence_Btn1_click, this));
	this->addChild(defence_Btn1, 1);

	//add triAttack_Btn1
	triAttack_Btn1 = Button::create("imges/tanks_crateAmmo.png", "imges/tanks_crateAmmo.png");
	triAttack_Btn1->setPosition(Vec2(visibleSize.width * 33 / 96, visibleSize.height * 8.1 / 10));
	triAttack_Btn1->setScale(0.5);
	triAttack_Btn1->addTouchEventListener(CC_CALLBACK_1(FireMaster::triAttack_Btn1_click, this));
	this->addChild(triAttack_Btn1, 1);

	//add powerBullet_Btn2
	powerBullet_Btn2 = Button::create("imges/tank_bullet4.png", "imges/tank_bullet4.png");
	powerBullet_Btn2->setPosition(Vec2(visibleSize.width *11 / 12, visibleSize.height * 8.1 / 10));
	powerBullet_Btn2->setFlipX(true);
	powerBullet_Btn2->addTouchEventListener(CC_CALLBACK_1(FireMaster::powerBullet_Btn2_click, this));
	this->addChild(powerBullet_Btn2, 1);

	//add fix_Btn2
	fix_Btn2 = Button::create("imges/tanks_crateRepair.png", "imges/tanks_crateRepair.png");
	fix_Btn2->setPosition(Vec2(visibleSize.width * 79 / 96, visibleSize.height * 8.1 / 10));
	fix_Btn2->setScale(0.5);
	fix_Btn2->addTouchEventListener(CC_CALLBACK_1(FireMaster::fix_Btn2_click, this));
	this->addChild(fix_Btn2, 1);

	//add defence_Btn2
	defence_Btn2 = Button::create("imges/tanks_crateArmor.png", "imges/tanks_crateArmor.png");
	defence_Btn2->setPosition(Vec2(visibleSize.width * 71 / 96, visibleSize.height * 8.1 / 10));
	defence_Btn2->setScale(0.5);
	defence_Btn2->addTouchEventListener(CC_CALLBACK_1(FireMaster::defence_Btn2_click, this));
	this->addChild(defence_Btn2, 1);

	//add triAttack_Btn2
	triAttack_Btn2 = Button::create("imges/tanks_crateAmmo.png", "imges/tanks_crateAmmo.png");
	triAttack_Btn2->setPosition(Vec2(visibleSize.width * 63 / 96, visibleSize.height * 8.1 / 10));
	triAttack_Btn2->setScale(0.5);
	triAttack_Btn2->addTouchEventListener(CC_CALLBACK_1(FireMaster::triAttack_Btn2_click, this));
	this->addChild(triAttack_Btn2, 1);


	//add hp1
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("imges/FireMaster.plist");
    Sprite* hp1 = Sprite::createWithSpriteFrameName("blood.png");
	hp1->setFlipX(true);
	pT1 = ProgressTimer::create(hp1);
	pT1->setScaleX(11);
	pT1->setScaleY(1.18);
	pT1->setAnchorPoint(Vec2(0, 0));
	pT1->setType(ProgressTimerType::BAR);
	pT1->setBarChangeRate(Point(1, 0));
	pT1->setMidpoint(Point(0, 1));
	pT1->setPercentage(50);
	pT1->setPosition(Vec2(54,561));
	addChild(pT1, 1);

	//add hp2
	Sprite* hp2 = Sprite::createWithSpriteFrameName("blood.png");
	pT2 = ProgressTimer::create(hp2);
	pT2->setScaleX(11);
	pT2->setScaleY(1.18);
	pT2->setAnchorPoint(Vec2(0, 0));
	pT2->setType(ProgressTimerType::BAR);
	pT2->setBarChangeRate(Point(1, 0));
	pT2->setMidpoint(Point(0, 1));
	pT2->setPercentage(50);
	pT2->setPosition(Vec2(574, 561));
	addChild(pT2, 1);

	//add windpower
	//风向好似唔洗整血条，直接移动就得？？甘你直接用我个Position同缩放比例就得
	Sprite* windpower = Sprite::createWithSpriteFrameName("wind.png");
	wind = ProgressTimer::create(windpower);
	wind->setScaleX(6);
	wind->setScaleY(1.18);
	wind->setAnchorPoint(Vec2(0, 0));
	wind->setType(ProgressTimerType::BAR);
	wind->setBarChangeRate(Point(1, 0));
	wind->setMidpoint(Point(0, 1));
	wind->setPercentage(50);
	wind->setPosition(Vec2(450, 500));
	addChild(wind, 1);
}

//UI栏技能点击函数
void FireMaster::powerBullet_Btn1_click(Ref * sender)
{
	powerBullet_Btn1->runAction(FadeOut::create(0.5));
}
void FireMaster::fix_Btn1_click(Ref * sender)
{
	fix_Btn1->runAction(FadeOut::create(0.5));
}
void FireMaster::defence_Btn1_click(Ref * sender)
{
	defence_Btn1->runAction(FadeOut::create(0.5));
}
void FireMaster::triAttack_Btn1_click(Ref * sender)
{
	triAttack_Btn1->runAction(FadeOut::create(0.5));
}
void FireMaster::powerBullet_Btn2_click(Ref * sender)
{
	powerBullet_Btn2->runAction(FadeOut::create(0.5));
}
void FireMaster::fix_Btn2_click(Ref * sender)
{
	fix_Btn2->runAction(FadeOut::create(0.5));
}
void FireMaster::defence_Btn2_click(Ref * sender)
{
	defence_Btn2->runAction(FadeOut::create(0.5));
}
void FireMaster::triAttack_Btn2_click(Ref * sender)
{
	triAttack_Btn2->runAction(FadeOut::create(0.5));
}




