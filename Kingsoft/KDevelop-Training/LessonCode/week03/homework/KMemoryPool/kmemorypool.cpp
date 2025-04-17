#include <cstring>
#include <stdexcept>

#include "kmemorypool.h"

KMemoryPool::KMemoryPool(size_t blockSize, const std::string& name)
    : m_name(name)
    , m_allocatedBlocks(0)
{
    if (blockSize < sizeof(KBlock)) 
    {
        blockSize = sizeof(KBlock);
    }

    m_blockSize = blockSize;
    m_totalBlocks = MAX_POOL_SIZE / blockSize;

    if (m_totalBlocks == 0) 
    {
        throw std::bad_alloc();             //内存分配超过抛出bad_alloc
    }

    m_memory = malloc(m_totalBlocks * m_blockSize);
    if (!m_memory) 
    {
        throw std::bad_alloc();
    }

    m_freeList = nullptr;

    for (size_t i = 0; i < m_totalBlocks; ++i) 
    {
        KBlock* block = reinterpret_cast<KBlock*>(
            static_cast<char*>(m_memory) + i * m_blockSize
            );
        block->m_next = m_freeList;
        m_freeList = block;
    }

    std::cout << "Memory pool '"    << m_name                         << "' create successfully "<< std::endl;
    std::cout << "Block Size: "     << m_blockSize                    << "bytes"                 << std::endl;
    std::cout << "Block Number:"    << m_totalBlocks                                             << std::endl;
    std::cout << "Total Size: "     << (m_totalBlocks * m_blockSize)  << " bytes)"               << std::endl;
    std::cout << std::endl;
}

KMemoryPool::~KMemoryPool() 
{
    size_t leakedBlocks = m_allocatedBlocks;

    if (leakedBlocks > 0) 
    {
        std::cerr << "WARNING: Memory leak detected in pool: '" << m_name << std::endl;
        std::cerr << leakedBlocks << " blocks ("<< (leakedBlocks * m_blockSize)<< " bytes) not freed"
                  << std::endl;
    }
    else 
    {
        std::cout << "Memory pool " << m_name
                  << "destroyed with no memory leaks" << std::endl;
    }

    free(m_memory);
    m_memory = nullptr;
    m_freeList = nullptr;
}

KMemoryPool* KMemoryPool::createPool(size_t blockSize, const std::string& name) 
{
    try 
    {
        return new KMemoryPool(blockSize, name);
    }
    catch (...) 
    {
        std::cerr << "Failed to create memory pool: " << name << std::endl;
        return nullptr;
    }
}

void KMemoryPool::destroyPool(KMemoryPool* pool) 
{
    if (pool) 
    {
        delete pool;
        pool = nullptr;
    }
}



void* KMemoryPool::allocate() 
{
    if (!m_freeList) 
    {
        throw std::bad_alloc();
    }

    KBlock* block = m_freeList;
    m_freeList = block->m_next;
    m_allocatedBlocks++;

    memset(block, 0, m_blockSize);

    return block;
}

bool KMemoryPool::deallocate(void* p) 
{
    if (!p || !isAddressInPool(p)) 
    {
        return false;
    }

    KBlock* block = static_cast<KBlock*>(p);
    block->m_next = m_freeList;
    m_freeList = block;
    m_allocatedBlocks--;

    return true;
}

bool KMemoryPool::isAddressInPool(void* p) const 
{
    char* addr = static_cast<char*>(p);
    char* start = static_cast<char*>(m_memory);
    char* end = start + m_totalBlocks * m_blockSize;

    return addr >= start && addr < end &&
        (addr - start) % m_blockSize == 0; // 地址必须在块边界上
}

void KMemoryPool::printDetails() const 
{
    std::cout << "Memory Pool: "        << m_name                           << std::endl;
    std::cout << "Block size: "         << m_blockSize        << " bytes"   << std::endl;
    std::cout << "Total blocks: "       << m_totalBlocks                    << std::endl;
    std::cout << "Allocated blocks: "   << m_allocatedBlocks 
              << " ("<< (m_allocatedBlocks * m_blockSize)     << " bytes)"  << std::endl;
    std::cout << "Free blocks: " << getFreeBlocks() 
              << " ("<< (getFreeBlocks() * m_blockSize)       << " bytes)"  << std::endl;
    std::cout << "Usage: " << (static_cast<double>(m_allocatedBlocks) / m_totalBlocks * 100)
              << "%" << std::endl;
    std::cout << std::endl;
}

std::string KMemoryPool::getName() const 
{
    return m_name;
}

size_t KMemoryPool::getBlockSize() const 
{
    return m_blockSize;
}

size_t KMemoryPool::getTotalBlocks() const 
{
    return m_totalBlocks;
}

size_t KMemoryPool::getAllocatedBlocks() const 
{
    return m_allocatedBlocks;
}

size_t KMemoryPool::getFreeBlocks() const 
{
    return m_totalBlocks - m_allocatedBlocks;
}