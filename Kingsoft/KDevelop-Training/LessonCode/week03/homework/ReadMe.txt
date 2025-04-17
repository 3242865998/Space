设计思路:
1.整体架构
核心内存池类：KMemoryPool类
成员函数：
KMemoryPool(size_t, const std::string&)			构造函数，初始化内存池
~KMemoryPool()								析构函数，释放内存并检查泄漏
KMemoryPool* createPool						创建一个内存池
void destroyPool								销毁一个内存池
void* allocate()								分配一个内存块
bool deallocate(void*)							释放一个内存块
void printDetails()								打印内存池使用详情
bool isAddressInPool(void*)					检查指针合法性
一些getX()函数

多内存池管理类：KMemoryPoolManager类
成员函数：
KMemoryPool* createPool						在当前管理类创建一个内存池
KMemoryPool* getPool						获取指定名称的内存池
bool destroyPool								销毁指定名称的内存池
destroyAll									销毁管理类内所有内存池
printAllPools									打印管理类内所有内存池信息



2. 内存池原理
预分配内存：在程序启动或需要前，一次性向操作系统申请一块较大的连续内存空间（称为“内存池”）。
按需分配：当程序需要申请小内存时，直接从内存池中分配预先划分好的小块内存（即KBlock）。
回收复用：当程序释放内存时，不直接归还给操作系统，而是将内存块标记为“可用”，放回内存池以便下次快速分配。

3.实现方式：
3.1.固定大小内存池：将内存池划分为多个大小相同的小块（例如每个块16字节、32字节等），适用于频繁分配固定大小内存的场景（例如网络数据包、对象实例）。
3.2.使用的数据结构：使用单向链表管理空闲内存块
 			     每个内存块的首部包含一个指向下一个空闲块的指针
			     内存池管理整个内存区域的元数据，包括总块数、已分配块数等

3.3. 内存分配策略：LIFO (Last-In-First-Out)
分配时从空闲链表头部取出一个块并返回
释放时将块重新插入到空闲链表头部

3.4. 错误处理
内存池满时分配会抛出bad_alloc异常
释放非法指针会返回false
析构时会检测内存泄漏并报告

3.5. 安全性考虑
在分配时清零内存块，防止数据泄露
在释放时验证指针是否属于本内存池

3.6.多内存池
KMemoryPoolManager类集中管理多内存池
通过map容器管理内存池名和内存池之间的映射

3.7.限制
单个内存池限制为10MB
只支持固定大小的内存块分配
没有实现线程安全支持

4.具体方法实现思路

4.1. 构造函数 KMemoryPool::KMemoryPool(size_t blockSize, const std::string& name)
功能：实现初始化内存池并分配内存空间
关键步骤：
调整 blockSize：如果传入的块大小小于指针大小（sizeof(Block)），则提升为指针大小，以确保每个块足以保存链表指针。
计算总块数：通过 MAX_POOL_SIZE / blockSize 得到最大可容纳的块数，防止超出 10MB 限制。
分配内存：调用 malloc 一次性分配整个内存池，如果失败抛出 std::bad_alloc。
初始化空闲链表：
	将整块内存按块大小划分；
	将每一块转为 Block*，构建单向链表；
打印内存池状态

4.2. 析构函数 KMemoryPool::~KMemoryPool()
函数功能：销毁内存池，检查是否存在内存泄漏
关键步骤：
读取当前m_allocatedBlocks，如非零表示有泄漏；
输出泄漏警告信息，指明未释放的块数量及大小；
调用free释放内存池；
将内部指针设为nullptr 

4.3 创建内存池函数KMemoryPool* KMemoryPool::createPool(size_t blockSize, const std::string& name)
函数功能：通过指定块大小和内存池名字创建内存池
关键步骤:
new一个新内存池
如果捕获到错误，控制台打印错误提示和内存池名字

4.4 销毁内存池函数：void KMemoryPool::destroyPool(KMemoryPool* pool) 
函数功能：销毁内存池
关键步骤：
判断内存池地址是否存在
若存在，delete掉该内存池，系统会自动调用其析构函数
析构函数会自行释放掉该内存池占用的内存并进行泄露检查
将pool指针置空

4.5.分配函数 void* KMemoryPool::allocate()
函数功能：从空闲链表中取出一个可用块，并返回该块指针
关键步骤:
检查m_freeList是否为空，为空则抛出std::bad_alloc；
从空闲链表头取出第一个块，更新链表头指针；
使用memset将分配出的内存块内容清零，提升安全性；
增加已分配计数m_allocatedBlocks；
返回该块地址。

4.6 释放函数 bool KMemoryPool::deallocate(void* p)
函数功能：将指定内存块归还给空闲链表，更新分配状态
关键步骤：
检验指针p是否合法
若合法，将该块加到空闲链表表头并减少m_allocatedBlocks
返回true表示释放成功，若不成功返回false
 
4.7 指针合法性检查 bool KMemoryPool::isAddressInPool(void* p) const
函数功能：判断一个指针是否为当前内存池分配的块地址
关键步骤：
获取内存池的起始地址和终止地址；
判断地址是否落在内存池范围内；
判断地址偏移是否为m_blockSize的整数倍，确保指针恰好指向块起始地址

4.8 内存池状态输出void KMemoryPool::printDetails() const
函数功能：输出当前内存池的状态
关键步骤
输出：内存池名、池大小、总块数、已分配的块数和总字节数、空闲块数和对应的字节数、内存池空间使用率


KMemoryPoolManager类的函数逻辑简单，主要都是调用KMemoryPool类的函数接口，不单独阐述。