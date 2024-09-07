#include "indexbuffer.hpp"
#include <GL/glew.h>
#include <cassert>
#include <GL/gl.h>

IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int cout) {
    m_Count = cout;
    assert(sizeof(unsigned int) == sizeof(GLuint));//change to glBufferData(..., sizeof(GLuint) * cout,...);

    glGenBuffers(1, &m_RendendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendendererID); 
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * cout, data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &m_RendendererID);
}

void IndexBuffer::Bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendendererID); 
}

void IndexBuffer::UnBind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); 
}
