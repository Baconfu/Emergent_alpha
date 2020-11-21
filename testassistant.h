#ifndef TESTASSISTANT_H
#define TESTASSISTANT_H

#include <chunk.h>
#include <world.h>


class TestAssistant
{
public:
    TestAssistant(World * world);

    void testChunks();

private:
    World * m_world = nullptr;
};

#endif // TESTASSISTANT_H
