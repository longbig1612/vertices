#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Cube.h"
#include "BatchNode.hpp"
#include "MultipleTexture.h"
#include "Mirror.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    Director::getInstance()->setClearColor(Color4F(0, 0, 0, 0));
    Director::getInstance()->getScheduler()->schedule(CC_CALLBACK_1(HelloWorld::update, this), this, 1.0f/60, false, "mainloop");
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    skybox();
    playground(Vec3(0, 0, 0));
    //playground(Vec3(-3, -3, 1));
    
    //batchCall();
    //mirrorTest();

    
    return true;
}

void HelloWorld::skybox()
{
    auto textureCube = TextureCube::create("skybox/sahara_lf.jpg",
                                           "skybox/sahara_rt.jpg",
                                           "skybox/sahara_up.jpg",
                                           "skybox/sahara_dn.jpg",
                                           "skybox/sahara_ft.jpg",
                                           "skybox/sahara_bk.jpg");
    Texture2D::TexParams tParams;
    tParams.magFilter = GL_NEAREST;
    tParams.minFilter = GL_NEAREST;
    tParams.wrapS = GL_MIRRORED_REPEAT;
    tParams.wrapT = GL_MIRRORED_REPEAT;
    textureCube->setTexParameters(tParams);
    auto skybox = Skybox::create();
    skybox->setTexture(textureCube);
    skybox->setCameraMask((int)CameraFlag::USER1);
    //this->addChild(skybox);
    
    //setup camera
    auto s = Director::getInstance()->getWinSize();
    _camera = Camera::createPerspective(45, s.width / s.height, 0.01f, 100.f);
    _camera->setCameraFlag(CameraFlag::USER1);
    _camera->setPosition3D(Vec3(4.f, 3.f, 3.f));
    _camera->lookAt(Vec3(0.f, 0.f, 0.f), Vec3(0.f, 1.f, 0.f));
    addChild(_camera);
    
    
    
    
    //_camera->setBackgroundBrush(CameraBackgroundBrush::createNoneBrush());
    /*_camera->setBackgroundBrush(CameraBackgroundBrush::createSkyboxBrush("skybox/sahara_lf.jpg",
                                                                         "skybox/sahara_rt.jpg",
                                                                         "skybox/sahara_up.jpg",
                                                                         "skybox/sahara_dn.jpg",
                                                                         "skybox/sahara_ft.jpg",
                                                                         "skybox/sahara_bk.jpg"
                                                                         ));*/
    
    //_camera->setBackgroundBrush(CameraBackgroundBrush::createColorBrush(Color4F(1.f, 0.f, 0.f, 1.f), 1.f));
    
    //_camera->setBackgroundBrush(CameraBackgroundBrush::createDepthBrush(1.f));
    
    
    //auto cam = Camera::getDefaultCamera();
    //cam->setPosition3D(spritePos + Vec3(0, 0, 800));
    //cam->setBackgroundBrush(CameraBackgroundBrush::createNoneBrush());
    /*cam->setBackgroundBrush(CameraBackgroundBrush::createSkyboxBrush("skybox/sahara_lf.jpg",
                                                                     "skybox/sahara_rt.jpg",
                                                                     "skybox/sahara_up.jpg",
                                                                     "skybox/sahara_dn.jpg",
                                                                     "skybox/sahara_ft.jpg",
                                                                     "skybox/sahara_bk.jpg"
                                                                     ));*/
}

void HelloWorld::playground(Vec3 pos)
{
    auto cube = Cube::create("asd");
    cube->setCameraMask((int)CameraFlag::USER1);
    cube->init();
    this->addChild(cube);
    cube->setPosition3D(pos);
}

void HelloWorld::batchCall()
{
    MultipleTexture* mt = (MultipleTexture*) MultipleTexture::create();
    //mt->setCameraMask((int) CameraFlag::USER1);
    mt->init1("s1.png", "s2.png");
    //mt->setPosition(100, 100);
    this->addChild(mt);
}

void HelloWorld::mirrorTest()
{
    Mirror* mr = (Mirror*) Mirror::create();
    mr->init1("s1.png");
    this->addChild(mr);
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}

void HelloWorld::update(float dt) {
    
}
