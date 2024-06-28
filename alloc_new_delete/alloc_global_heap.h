#ifndef SANDBOX_CPP_ALLOC_GLOBAL_HEAP_H
#define SANDBOX_CPP_ALLOC_GLOBAL_HEAP_H

#include "memory.h"
#include "./logger/logger.h"
#include "./logger/logger_holder.h"
#include "typename_holder.h"

class alloc_global_heap final:
    public memory,
    protected logger_holder,
    protected typename_holder
{

private:

    logger *_logger;

public:

    explicit alloc_global_heap(
        logger *logger = nullptr);

public:

    size_t get_occupied_block_size(
        void * const current_block_address) const ;

    void * allocate(
        size_t block_size) const override;

    void deallocate(
        void * const block_pointer) const override;

    void setup_allocation_mode(
        memory::allocate_mode mode) ;

private:

    logger *get_logger() const override;

private:

    std::string get_typename() const noexcept override;

private:

    void *get_buddies(void *target_ptr) const override;
    bool is_free_block(void *target_ptr) const override;
    memory *get_memory() const override;

};

#endif //SANDBOX_CPP_ALLOC_GLOBAL_HEAP_H
