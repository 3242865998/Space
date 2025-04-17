#include "kmemorypool.h"
#include "kmemorypoolmanager.h"
#include <iostream>
#include <vector>
#include <stdexcept>

// 测试简单分配和释放
void testBasicAllocDealloc() 
{
    std::cout << std::endl << "==== Testing Pool Allocate/Deallocate ====" << std::endl;

    KMemoryPool* pool = KMemoryPool::createPool(64, "TestBasic");
    pool->printDetails();

    void* p1 = pool->allocate();
    void* p2 = pool->allocate();
    void* p3 = pool->allocate();

    std::cout << "Allocated 3 blocks"       << std::endl;
    pool->printDetails();

    pool->deallocate(p2);
    std::cout << "Freed 1 block"            << std::endl;
    pool->printDetails();

    pool->deallocate(p1);
    pool->deallocate(p3);
    std::cout << "Freed remaining blocks"   << std::endl;
    pool->printDetails();

    KMemoryPool::destroyPool(pool);
}

// 测试内存池耗尽情况
void testPoolExhaustion() 
{
    std::cout << std::endl << "==== Testing Pool Exhaustion ====" << std::endl;

    const size_t blockSize = 1024;

    KMemoryPool* pool = KMemoryPool::createPool(blockSize, "ExhaustTest");
    pool->printDetails();

    const size_t totalBlocks = pool->getTotalBlocks();
    const size_t attemptBlocks = totalBlocks + 10;

    std::vector<void*> blocks;

    try 
    {
        std::cout << "Attempting to allocate " << attemptBlocks 
                  << " blocks (beyond capacity of "<< totalBlocks<< ")..."<< std::endl;

        for (size_t i = 0; i < attemptBlocks; i++) 
        {
            void* block = pool->allocate();
            blocks.push_back(block);

            if (i % 1000 == 0 || i > totalBlocks - 10) 
            {
                std::cout << "Allocated block " << i + 1 << " of " << totalBlocks << std::endl;
            }
        }

        std::cout << "ERROR: Successfully allocated beyond capacity without exception!" << std::endl;
    }
    catch (const std::bad_alloc& e) 
    {
        std::cout << "Expected exception caught: " << e.what() << std::endl;
        std::cout << "Successfully allocated " << blocks.size() << " blocks before pool exhaustion" << std::endl;
    }

    pool->printDetails();

    for (void* block : blocks) 
    {
        pool->deallocate(block);
    }

    std::cout << "All blocks freed" << std::endl;
    pool->printDetails();

    KMemoryPool::destroyPool(pool);
}

// 测试内存泄漏检测
void testMemoryLeakDetection() 
{
    std::cout << std::endl << "==== Testing Memory Leak Detection ====" << std::endl;

    KMemoryPool* pool = KMemoryPool::createPool(128, "LeakTest");
    pool->printDetails();

    pool->allocate();
    pool->allocate();

    std::cout << "Allocated 2 blocks but won't free them" << std::endl;
    pool->printDetails();

    KMemoryPool::destroyPool(pool);
    std::cout << "Pool destroyed, should report 2 leaked blocks" << std::endl;
}

// 测试边界条件
void testEdgeCases() 
{
    std::cout << std::endl << "==== Testing Edge Cases ====" << std::endl;

    KMemoryPool* smallPool = KMemoryPool::createPool(1, "SmallBlockPool");
    std::cout << "Created pool with requested block size 1 byte" << std::endl;
    smallPool->printDetails();

    void* p = smallPool->allocate();
    std::cout << "Successfully allocated from small block pool" << std::endl;
    smallPool->deallocate(p);

    void* invalidPtr = (void*)0x12345678;
    bool result = smallPool->deallocate(invalidPtr);
    std::cout << "Attempt to free invalid pointer: "
        << (result ? "succeeded (BAD!)" : "failed (GOOD!)") << std::endl;

    result = smallPool->deallocate(nullptr);
    std::cout << "Attempt to free nullptr: "
        << (result ? "succeeded (BAD!)" : "failed (GOOD!)") << std::endl;

    KMemoryPool::destroyPool(smallPool);
}


// 测试通过Manager创建和销毁内存池
void testManagerCreateDestroy() 
{
    std::cout << std::endl << "==== Testing Pool Creation and Destruction via Manager ====" << std::endl;

    KMemoryPoolManager::createPool("PoolA", 64);
    KMemoryPoolManager::createPool("PoolB", 128);
    KMemoryPoolManager::createPool("PoolC", 256);

    for (const std::string& name : { "PoolA", "PoolB", "PoolC" }) 
    {
        if (KMemoryPool* pool = KMemoryPoolManager::getPool(name)) 
        {
            pool->printDetails();
        }
    }

    KMemoryPoolManager::destroyPool("PoolB");
    std::cout << "Destroyed PoolB" << std::endl;

    for (const std::string& name : { "PoolA", "PoolB", "PoolC" }) 
    {
        if (KMemoryPool* pool = KMemoryPoolManager::getPool(name)) 
        {
            std::cout << name << " exists" << std::endl;
        }
        else 
        {
            std::cout << name << " not found" << std::endl;
        }
    }

    KMemoryPoolManager::destroyAll();
    std::cout << "All pools destroyed" << std::endl;
}

int main() 
{
    try 
    {
        std::cout << "===== KMemoryPool Test Program =====" << std::endl;

        testBasicAllocDealloc();
        testPoolExhaustion();
        testMemoryLeakDetection();
        testEdgeCases();
        testManagerCreateDestroy();

        std::cout << std::endl << "All tests completed." << std::endl;
    }
    catch (const std::exception& e) 
    {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}