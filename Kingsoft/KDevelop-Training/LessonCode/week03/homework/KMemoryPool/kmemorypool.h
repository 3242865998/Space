#ifndef _KMEMORYPOOL_H_
#define _KMEMORYPOOL_H_

#include <iostream>
#include <cstddef>
#include <string>

class KMemoryPool
{
public:

    KMemoryPool(size_t blockSize, const std::string& name = "default");

    ~KMemoryPool();

    //创建内存池
    static KMemoryPool* createPool(size_t blockSize, const std::string& name = "default");
    //销毁内存池
    static void destroyPool(KMemoryPool* pool);

    void* allocate();                   //分配内存块
    bool deallocate(void* p);           //释放之前分配的内存块
    void printDetails() const;          //输出内存池详细信息

    std::string getName() const;        //获取内存池名字
    size_t getBlockSize() const;        //获取块大小
    size_t getTotalBlocks() const;      //获取总块数
    size_t getAllocatedBlocks() const;  //获取已分配块数
    size_t getFreeBlocks() const;       //获取空闲块数



private:

    struct KBlock {
        KBlock* m_next;                  //指向下一个内存块的指针
    };

    static const size_t MAX_POOL_SIZE = 10 * 1024 * 1024;  // 10MB

    void* m_memory;                     // 内存池起始地址
    KBlock* m_freeList;                 // 空闲块链表头
    size_t m_blockSize;                 // 块大小
    size_t m_totalBlocks;               // 总块数
    size_t m_allocatedBlocks;           // 已分配块数
    std::string m_name;                 // 内存池名称

    bool isAddressInPool(void* p) const;//检查指针是否合法
};

#endif // _KMEMORYPOOL_H_