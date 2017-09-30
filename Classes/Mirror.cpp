//
//  Mirror.cpp
//  Test3D
//
//  Created by Admin on 9/26/17.
//
//

#include <stdio.h>
#include "Mirror.h"

USING_NS_CC;

Mirror::Mirror()
{
    
}

Mirror::~Mirror()
{
    
}

Node* Mirror::create()
{
    Mirror* ret = new (std::nothrow) Mirror();
    if (ret)
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    
    return ret;
    
}

bool Mirror::init1(std::string s1)
{
    GLProgram* p = GLProgram::createWithFilenames("shaders/test/Mirror.vsh", "shaders/test/Mirror.fsh");
    program = p->getProgram();
    
    //p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
    //p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
    //p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD1, GLProgram::VERTEX_ATTRIB_TEX_COORD1);
    
    //p->bindAttribLocation("a_position", GLProgram::VERTEX_ATTRIB_POSITION);
    //p->bindAttribLocation("vertexUV", GLProgram::VERTEX_ATTRIB_TEX_COORD);
    //p->bindAttribLocation("vertexUV2", GLProgram::VERTEX_ATTRIB_TEX_COORD1);
    p->link();
    p->updateUniforms();
    
    setGLProgramState(GLProgramState::getOrCreateWithGLProgram(p));
    
    Texture2D *text1 = Director::getInstance()->getTextureCache()->addImage(s1);
    texture1 = text1->getName();
    
    // Initialize VBO
    glGenBuffers(1, &Text2DVertexBufferID1);
    glGenBuffers(1, &Text2DUVBufferID1);
    
    glGenBuffers(1, &Text2DUVBufferID2);
    
    // Initialize uniforms' IDs
    Text2DUniformID1 = p->getUniformLocation("myTextureSampler1");
    
    Size size = Director::getInstance()->getWinSize();
    
    
    GLfloat width = (GLfloat) text1->getPixelsWide() * text1->getMaxS();// * 0.7f;
    GLfloat height = (GLfloat) text1->getPixelsHigh() * text1->getMaxT();// * 0.7f;
    width = 2 * width / size.width;
    height = 2 * height / size.height;
    
    GLfloat x = 0.f - width / 2;
    GLfloat y = -0.3f - height / 2;
    
    GLfloat vertices[] = {
        x,            y,
        width + x,    y,
        x,            height  + y,
        width + x,    height  + y/*,
        
        x,            height  + y,
        width + x,    height  + y,
        x,            1.5f * height + y,
        width + x,    1.5f * height + y
       */
        
    };
    
    GLfloat uv[] = {
        0.f, 0.f,
        1.f, 0.f,
        0.f, 1.f,
        1.f, 1.f
        /*,
        
        0.f, 1.f,
        1.f, 1.f,
        0.f, 0.5f,
        1.f, 0.5f*/
    };
    
    glBindBuffer(GL_ARRAY_BUFFER, Text2DVertexBufferID1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, Text2DUVBufferID1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uv), &uv[0], GL_STATIC_DRAW);
    
    GLfloat uv2[] = {
        1.f, 1.f,
        1.f, 1.f,
        1.f, 1.f,
        1.f, 1.f/*,
        0.5f, 1.f,
        0.5f, 1.f,
        0.0f, 0.5f,
        0.0f, 0.5f*/
    };
    
    glBindBuffer(GL_ARRAY_BUFFER, Text2DUVBufferID2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uv2), &uv2[0], GL_STATIC_DRAW);
    
    indices = {
        0, 1, 3,
        3, 2, 0/*,
        4, 5, 7,
        7, 6, 4*/
    };
    
    glGenBuffers(1, &elementbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0] , GL_STATIC_DRAW);
    
    
    
    return true;
}


void Mirror::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
    _customCommand.init(_globalZOrder, transform, flags);
    _customCommand.func = CC_CALLBACK_0(Mirror::onDraw, this, transform, flags);
    renderer->addCommand(&_customCommand);
}

void Mirror::onDraw(const Mat4 &transform, uint32_t flags)
{
    auto glProgram = getGLProgram();
    glProgram->use();
    glProgram->setUniformsForBuiltins(transform);
    
    // Bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // Set our "myTextureSampler" sampler to use Texture Unit 0
    glUniform1i(Text2DUniformID1, 0);
    
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
    glBindBuffer(GL_ARRAY_BUFFER, Text2DVertexBufferID1);
    glVertexAttribPointer(
                          GLProgram::VERTEX_ATTRIB_POSITION,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                          2,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          0,                  // stride
                          (void*)0            // array buffer offset
                          );
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_TEX_COORD);
    glBindBuffer(GL_ARRAY_BUFFER, Text2DUVBufferID1);
    glVertexAttribPointer(
                          GLProgram::VERTEX_ATTRIB_TEX_COORD,                                // attribute. No particular reason for 1, but must match the layout in the shader.
                          2,                                // size
                          GL_FLOAT,                         // type
                          GL_FALSE,                         // normalized?
                          0,                                // stride
                          (void*)0                          // array buffer offset
                          );
    
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_TEX_COORD1);
    glBindBuffer(GL_ARRAY_BUFFER, Text2DUVBufferID2);
    glVertexAttribPointer(
                          GLProgram::VERTEX_ATTRIB_TEX_COORD1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
                          2,                                // size
                          GL_FLOAT,                         // type
                          GL_FALSE,                         // normalized?
                          0,                                // stride
                          (void*)0                          // array buffer offset
                          );
    
    
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
    
    // Draw the triangles !
    glDrawElements(GL_TRIANGLES, (int) indices.size(), GL_UNSIGNED_SHORT, (void*)0);
    
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 8);
    
}
