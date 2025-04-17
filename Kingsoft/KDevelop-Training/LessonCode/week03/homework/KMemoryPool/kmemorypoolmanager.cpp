#include "kmemorypoolmanager.h"

std::map<std::string, KMemoryPool*> KMemoryPoolManager::s_pools;

KMemoryPool* KMemoryPoolManager::createPool(const std::string& name, size_t blockSize)
{
    if (s_pools.count(name)) 
    {
        std::cerr << "Memory pool " << name << " already exists!" << std::endl;
        return nullptr;
    }

    KMemoryPool* pool = KMemoryPool::createPool(blockSize, name);
    if (pool) 
    {
        s_pools[name] = pool;
        std::cout << "Memory pool " << name << " create successfully!" << std::endl;
    }
    return pool;
}

KMemoryPool* KMemoryPoolManager::getPool(const std::string& name) 
{
    auto it = s_pools.find(name);
    return (it != s_pools.end()) ? it->second : nullptr;
}

bool KMemoryPoolManager::destroyPool(const std::string& name) 
{
    auto it = s_pools.find(name);
    if (it == s_pools.end())
    {
        std::cerr << "Memory pool " << name << "does not exist!" << std::endl;
        return false;
    }

    KMemoryPool::destroyPool(it->second);
    s_pools.erase(it);
    std::cout << "Memory pool " << name << " destroies successfully!" << std::endl;
    return true;
}

void KMemoryPoolManager::destroyAll() 
{
    for (auto& kv : s_pools) 
    {
        KMemoryPool::destroyPool(kv.second);
    }
    s_pools.clear();
    std::cout << "All memory pools destroy successfully!" << std::endl;
}

void KMemoryPoolManager::printAllPools() 
{
    for (const auto& kv : s_pools) 
    {
        kv.second->printDetails();
    }
}
