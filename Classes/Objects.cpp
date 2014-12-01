#include "Objects.h"

BillManager::BillManager(char* name, cocos2d::SpriteFrame* frame, cocos2d::SpriteFrame* frameIcon, cocos2d::SpriteFrame* frameFloating, int value, int unlockValue)
{
	mName = name;
	mSpriteFrame = frame;
	mSpriteFrame->retain();
	mSpriteFrameIcon = frameIcon;
	mSpriteFrameFloating = frameFloating;
	mValue = value;
	mUnlockValue = unlockValue;
}

BillManager::~BillManager()
{
	cocos2d::log("destroy billfactory");
}

cocos2d::SpriteFrame* BillManager::getSpriteFrame()
{
	return mSpriteFrame;
}

cocos2d::SpriteFrame* BillManager::getFloatingSpriteFrame()
{
	return mSpriteFrameFloating;
}

cocos2d::SpriteFrame* BillManager::getIconSpriteFrame()
{
	return mSpriteFrameIcon;
}

const char* BillManager::getName()
{
	return mName;
}

int BillManager::getValue()
{
	return mValue;
}

int BillManager::getUnlockValue()
{
	return mUnlockValue;
}

Bill* Bill::create(BillManager* factory)
{
	Bill* ret = new Bill();
	ret->initWithSpriteFrame(factory->getSpriteFrame());
	ret->mFactory = factory;
	ret->autorelease();
	
	return ret;
}

MyMenuItem* MyMenuItem::create(cocos2d::Node* sprite, const cocos2d::ccMenuCallback& callback)
{
	return create(sprite, nullptr, callback);
}

MyMenuItem* MyMenuItem::create(cocos2d::Node* enabledSprite, cocos2d::Node* disabledSprite, const cocos2d::ccMenuCallback& callback)
{
	MyMenuItem* ret = new MyMenuItem();
	ret->initWithNormalSprite(enabledSprite, nullptr, disabledSprite, callback);
	ret->mEnabled = true;
	ret->autorelease();
	
	return ret;
}

void MyMenuItem::selected()
{
	MenuItem::selected();
	
	runAction(cocos2d::Sequence::create(
			cocos2d::ScaleTo::create(0.07f, 0.9f),
			cocos2d::ScaleTo::create(0.07f, 1),
			NULL
	));
}

void MyMenuItem::unselected()
{
	MenuItem::unselected();
}

void MyMenuItem::activate()
{
	MenuItemSprite::activate();
}

bool MyMenuItem::getEnabled()
{
	return mEnabled;
}

void MyMenuItem::setEnabled(bool state)
{
	if (state != mEnabled)
	{
		mEnabled = state;
		_normalImage->setVisible(mEnabled);
		if (_disabledImage)
			_disabledImage->setVisible(!mEnabled);
	}
}

void ObjectPool::init(int capacity, cocos2d::SpriteFrame* spriteFrame, cocos2d::Node* parent)
{
	if (getAvailableItemCount() > 0)
		clearPool();
	
	mSpriteFrame = spriteFrame;
	mParent = parent;
	
	initWithCapacity(capacity);
}

cocos2d::Sprite* ObjectPool::onAllocatePoolItem()
{
	cocos2d::Sprite* sprite = cocos2d::Sprite::createWithSpriteFrame(mSpriteFrame);
	sprite->setVisible(false);
	sprite->pause();
	mParent->addChild(sprite);
	return sprite;
}

void ObjectPool::onRecycleItem(cocos2d::Sprite* item)
{
	item->setScale(1);
	item->stopAllActions();
}

void MoneyPool::init(int capacity, BillManager* factory, cocos2d::Node* parent)
{
	if (getAvailableItemCount() > 0)
		clearPool();
	
	mFactory = factory;
	mParent = parent;
	
	initWithCapacity(capacity);
}

Bill* MoneyPool::onAllocatePoolItem()
{
	Bill* sprite = Bill::create(mFactory);
	sprite->setVisible(false);
	sprite->pause();
	mParent->addChild(sprite);
	return sprite;
}

void MoneyPool::onRecycleItem(Bill* item)
{
	item->setScale(1);
	item->stopAllActions();
}
