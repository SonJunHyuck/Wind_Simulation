#include "buffer.h"

Buffer::~Buffer()
{
    if (m_buffer)
    {
        glDeleteBuffers(1, &m_buffer);
    }
}

BufferUPtr Buffer::CreateWithData(uint32_t bufferType, uint32_t usage, const void* data, size_t stride, size_t count)
{
    auto buffer = BufferUPtr(new Buffer());
    if (!buffer->Init(bufferType, usage, data, stride, count))
        return nullptr;
    return std::move(buffer);
}

void Buffer::Bind() const
{
    glBindBuffer(m_bufferType, m_buffer);
}

bool Buffer::Init(uint32_t bufferType, uint32_t usage, const void* data, size_t stride, size_t count)
{
    m_bufferType = bufferType;
    m_usage = usage;
    m_stride = stride;
    m_count = count;
    int datasize = stride * count;
    
    glGenBuffers(1, &m_buffer);
    Bind();
    glBufferData(m_bufferType, datasize, data, usage);
    return true;
}