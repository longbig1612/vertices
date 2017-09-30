//
//  Cube.h
//  Test3D
//
//  Created by Admin on 9/21/17.
//
//

#ifndef Cube_h
#define Cube_h

#include "cocos2d.h"

class Cube: public cocos2d::Node
{
public:
    Cube();
    ~Cube();
    virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4 &transform, uint32_t flag) override;
    void onDraw(const cocos2d::Mat4 &transform, uint32_t flags);
    bool init();
    static Node* create(const std::string modelPath);
private:
    
    // This will identify our vertex buffer
    GLuint vertexbuffer;
    GLuint colorbuffer;
    GLuint elementbuffer;
    
    std::vector<unsigned short> indices;
protected:
    cocos2d::CustomCommand _customCommand;
    struct V3F_C4B
    {
        cocos2d::Vec3     vertices;
        cocos2d::Color4B  colors;
    };
};

#endif /* Cube_h */
