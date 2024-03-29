#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "common.h"
#include "buffer.h"
#include "vertex_layout.h"
#include "program.h"

struct ParticleAttribute
{
    float index;
    glm::vec2 position;
    float age;
    float life;
};

struct TailAttribute
{
    glm::vec2 positions;
    glm::vec4 tailColors;
};


CLASS_PTR(Particle);
class Particle
{
public:
    static ParticleUPtr Create(const uint32_t inParticleNum, const uint32_t inTailNum, uint32_t primitiveType);

    const VertexLayout *GetVertexLayout() const { return m_vertexLayout.get(); }
    const uint32_t GetParticleNum() const { return m_particleNum; }
    const int GetTailLength() const { return m_tailLength; }
    const float GetVelocityWeight() const { return m_velocityWeight; }
    
    void SetParticleNum(uint32_t inParticleNum) { m_particleNum = inParticleNum; }
    void SetTailLength(float inTailNum) { m_tailLength = inTailNum; }
    void SetVelocityWeight(float inVelocityWeight) { m_velocityWeight = inVelocityWeight; }

    void Draw(const Program* program) const;

    uint32_t m_particleMAX { 1024 * 32 };
    uint32_t m_tailLengthMAX { 256 };
private:
    Particle() {}
    void Init(const uint32_t inParticleNum, const uint32_t inTailNum, uint32_t primitiveType);

    uint32_t m_primitiveType{GL_POINTS};
    VertexLayoutUPtr m_vertexLayout;
    
    BufferPtr m_particleIndexBuffer;
    BufferPtr m_particlePositionBuffer;
    BufferPtr m_particleAgeBuffer;
    BufferPtr m_particleLifeBuffer;
    BufferPtr m_tailPositionBuffer;
    BufferPtr m_tailColorBuffer;

    uint32_t m_particleNum { 1024 * 32 };
    int m_tailLength { 256 };
    float m_velocityWeight { 1.0f };
};

#endif // __PARTICLE_H__