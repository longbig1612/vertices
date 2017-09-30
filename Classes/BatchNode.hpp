//
//  BatchNode.hpp
//  Test3D
//
//  Created by Admin on 9/22/17.
//
//

#ifndef BatchNode_hpp
#define BatchNode_hpp

#include "cocos2d.h"

class BatchNode: public cocos2d::Node
{
public:
    BatchNode();
    ~BatchNode();
    virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4 &transform, uint32_t flag) override;
    void onDraw(const cocos2d::Mat4 &transform, uint32_t flags);
    bool init();
    void addTextured2D1(cocos2d::Texture2D* texture);
    static Node* create(cocos2d::Texture2D* texture, cocos2d::Texture2D* texture2);
private:
    
    // This will identify our vertex buffer
    GLuint vertexbuffer;
    GLuint colorbuffer;
    GLuint elementbuffer;
    
    std::vector<unsigned short> indices;
    
    std::vector<cocos2d::Texture2D*> listTexture2D;
protected:
    cocos2d::CustomCommand _customCommand;
};


#endif /* BatchNode_hpp */
