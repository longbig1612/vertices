//
//  BatchNode.cpp
//  Test3D
//
//  Created by Admin on 9/22/17.
//
//

#include "BatchNode.hpp"

USING_NS_CC;

BatchNode::BatchNode()
{
    
}

BatchNode::~BatchNode()
{
    
}

Node* BatchNode::create(Texture2D* texture, Texture2D* texture2)
{
    BatchNode* ret = new (std::nothrow) BatchNode();
    if (ret && ret->init())
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    ret->addTextured2D1(texture);
    ret->addTextured2D1(texture2);
    return ret;
    
}

bool BatchNode::init()
{
    
    return true;
}

void BatchNode::addTextured2D1(Texture2D* texture)
{
    listTexture2D.push_back(texture);
}


void BatchNode::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
    _customCommand.init(_globalZOrder, transform, flags);
    _customCommand.func = CC_CALLBACK_0(BatchNode::onDraw, this, transform, flags);
    renderer->addCommand(&_customCommand);
}

void BatchNode::onDraw(const Mat4 &transform, uint32_t flags)
{
    //auto glProgram = getGLProgram();
    //glProgram->use();
    //glProgram->setUniformsForBuiltins(transform);
    
    GLProgram* glProgram = GLProgram::createWithFilenames("shaders/test/TestVertexShader.vsh", "shaders/test/TestFragmentShader.fsh");
    
    for (int i = 0; i < listTexture2D.size(); ++i) {
        Texture2D* texture = listTexture2D.at(i);
        GLuint data = texture->getName();
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->getPixelsWide(), texture->getPixelsHigh(), 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, texture);
    }
}

/*void BatchNode::onDraw(const Mat4 &transform, uint32_t flags)
{
    auto glProgram = getGLProgram();
    glProgram->use();
    glProgram->setUniformsForBuiltins(transform);
    
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
                          GLProgram::VERTEX_ATTRIB_POSITION,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                          3,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          0,                  // stride
                          (void*)0            // array buffer offset
                          );
    
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_COLOR);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glVertexAttribPointer(
                          GLProgram::VERTEX_ATTRIB_COLOR,                                // attribute. No particular reason for 1, but must match the layout in the shader.
                          3,                                // size
                          GL_FLOAT,                         // type
                          GL_FALSE,                         // normalized?
                          0,                                // stride
                          (void*)0                          // array buffer offset
                          );
    
    // Index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
    
    // Draw the triangles !
    glDrawElements(GL_TRIANGLES, (int) indices.size(), GL_UNSIGNED_SHORT, (void*)0);
    
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 8);
    
    
}*/
