#include <iostream>
#include "logger/logger.h"
#include "logger/logger_builder_concrete.h"
#include "alloc_new_delete/alloc_global_heap.h"
#include "list"

int main() {
    logger_builder *builder = new logger_builder_concrete();
    auto *sorted_list_allocator_logger = builder
            ->add_stream("alloc_global_heap.txt", logger::severity::debug)->construct();
    delete builder;
    alloc_global_heap *allocator = new alloc_global_heap(sorted_list_allocator_logger);
    std::list<void *> allocated_blocks;
    srand((unsigned)time(nullptr));
    for (auto i = 0; i < 100; i++)
    {
        switch (rand() % 2)
        {
            case 0:
            case 1:
                try
                {
                    allocated_blocks.push_front(allocator->allocate(rand() % 251 + 50));
                    std::cout << "allocation succeeded" << std::endl;
                }
                catch (std::bad_alloc const &ex)
                {
                    std::cout << ex.what() << std::endl;
                }
                break;
            case 2:
                if (allocated_blocks.empty())
                {
                    std::cout << "No blocks to deallocate" << std::endl;
                    break;
                }
                auto it = allocated_blocks.begin();
                std::advance(it, rand() % allocated_blocks.size());
                allocator->deallocate(*it);
                allocated_blocks.erase(it);
                std::cout << "deallocation succeeded" << std::endl;
                break;
        }
    }

    while (!allocated_blocks.empty())
    {
        auto it = allocated_blocks.begin();
        std::advance(it, rand() % allocated_blocks.size());
        allocator->deallocate(*it);
        allocated_blocks.erase(it);
        std::cout << "deallocation succeeded" << std::endl;
    }

    delete allocator;
    delete sorted_list_allocator_logger;
    delete builder;
}
