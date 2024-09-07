#include "vertexbuffer.hpp"
#include <GL/glew.h>

VertexBuffer::VertexBuffer(const void *data, unsigned int size) {
    glGenBuffers(1, &m_RendendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendendererID); 
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &m_RendendererID);
}

void VertexBuffer::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_RendendererID); 
}

void VertexBuffer::UnBind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
}
