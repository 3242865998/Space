#ifndef _KMEMORYPOOLMANAGER_H_
#define _KMEMORYPOOLMANAGER_H_

#include <map>
#include <string>
#include "kmemorypool.h"

class KMemoryPoolManager {
public:
    static KMemoryPool* createPool(const std::string& name, size_t blockSize);      //创建新内存池
    static KMemoryPool* getPool(const std::string& name);                           //获取指定名称的内存池
    static bool destroyPool(const std::string& name);                               //销毁指定名称的内存池
    static void destroyAll();                                                       //销毁所有内存池
    static void printAllPools();                                                    //打印所有内存池信息

private:
    static std::map<std::string, KMemoryPool*> s_pools;
};

#endif
