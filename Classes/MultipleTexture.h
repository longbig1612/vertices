//
//  MultipleTexture.h
//  Test3D
//
//  Created by Admin on 9/24/17.
//
//

#ifndef MultipleTexture_h
#define MultipleTexture_h

#include "cocos2d.h"

class MultipleTexture: public cocos2d::Node
{
public:
    MultipleTexture();
    ~MultipleTexture();
    virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4 &transform, uint32_t flag) override;
    void onDraw(const cocos2d::Mat4 &transform, uint32_t flags);
    bool init1(std::string s1, std::string s2);
    static Node* create();
private:
    
    // This will identify our vertex buffer
    GLuint vertexbuffer;
    GLuint colorbuffer;
    GLuint elementbuffer;
    GLuint program;
    
    GLuint texture1;
    GLuint texture2;
    GLuint TextureID1;
    GLuint TextureID2;
    
    GLuint Text2DVertexBufferID1;
    GLuint Text2DVertexBufferID2;
    
    GLuint Text2DUVBufferID1;
    GLuint Text2DUVBufferID2;
    
    GLuint Text2DUniformID1;
    GLuint Text2DUniformID2;
    
    std::vector<unsigned short> indices;
protected:
    cocos2d::CustomCommand _customCommand;
    struct V3F_C4B
    {
        cocos2d::Vec3     vertices;
        cocos2d::Color4B  colors;
    };
};


#endif /* MultipleTexture_h */
