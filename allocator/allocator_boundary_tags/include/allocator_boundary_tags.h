#ifndef MATH_PRACTICE_AND_OPERATING_SYSTEMS_ALLOCATOR_ALLOCATOR_BOUNDARY_TAGS_H
#define MATH_PRACTICE_AND_OPERATING_SYSTEMS_ALLOCATOR_ALLOCATOR_BOUNDARY_TAGS_H

#include "../../allocator/include/allocator_guardant.h"
#include "../../allocator/include/allocator_test_utils.h"
#include "../../allocator/include/allocator_with_fit_mode.h"
#include "../../../logger/logger/include/logger_guardant.h"
#include "../../../logger/client_logger/include/client_logger.h"
#include "../../allocator/include/allocator.h"
#include "../../common/include/typename_holder.h"
#include <mutex>

class allocator_boundary_tags final:
    private allocator_guardant,
    public allocator_test_utils,
    public allocator_with_fit_mode,
    private logger_guardant,
    private typename_holder
{

private:

    void *_trusted_memory;

    static constexpr const size_t _size_allocator_meta = sizeof(logger*) + sizeof(allocator*) + sizeof(allocator_with_fit_mode::fit_mode)  +  sizeof(size_t) +  sizeof(std::mutex)  + sizeof(void*);

    static constexpr const size_t _size_load_block_meta = sizeof(size_t) + 3 * sizeof(void*);

public:

    ~allocator_boundary_tags() override;

    allocator_boundary_tags(
	    allocator_boundary_tags const &other) = delete;

    allocator_boundary_tags &operator=(
	    allocator_boundary_tags const &other) = delete;

    allocator_boundary_tags(
	    allocator_boundary_tags &&other) noexcept;

    allocator_boundary_tags &operator=(
	    allocator_boundary_tags &&other) noexcept;

public:

    explicit allocator_boundary_tags(
	    size_t space_size,
	    allocator *parent_allocator = nullptr,
	    logger *logger = nullptr,
	    allocator_with_fit_mode::fit_mode allocate_fit_mode = allocator_with_fit_mode::fit_mode::first_fit);

public:

    [[nodiscard]] void *allocate(
	    size_t value_size,
	    size_t values_count) override;

    void deallocate(
	    void *at) override;

public:

    std::string get_typename() override
    {
	return "allocator_boundary_tags";
    }

    std::string get_fit_mode_str() override;


    inline void set_fit_mode(
	    allocator_with_fit_mode::fit_mode mode) override;

public:

    std::vector<block_info> get_blocks_info(size_t& full_free_size) const noexcept override;

private:

    inline allocator *get_allocator() const override;

    inline logger *get_logger() const override;

    inline std::string get_typename() const noexcept override;

private:

    inline std::mutex& get_mutex() noexcept;

public:

    inline allocator_with_fit_mode::fit_mode& get_fit_mode() const noexcept;

private:

    void* get_first_suitable(size_t need_size)  const noexcept;

    void* get_worst_suitable(size_t need_size) const noexcept;

    void* get_best_suitable(size_t need_size)  const noexcept;

    inline size_t get_size_full() const noexcept;

    inline size_t get_size_current_load_block(void* current_block) const noexcept;

    inline void** get_next_load_block(void* current_block) const noexcept;

    inline void** get_prev_load_block(void* current_block) const noexcept;

    inline void** get_parrent_for_current_load_block(void* current_block) const noexcept;

    inline void** get_first_block() const noexcept;

    inline size_t get_next_free_size(void* loaded_block) const noexcept;

    static std::string get_info_in_string(const std::vector<allocator_test_utils::block_info>& vec) noexcept;

    static std::string get_dump(char* at, size_t size);
};

#endif //MATH_PRACTICE_AND_OPERATING_SYSTEMS_ALLOCATOR_ALLOCATOR_BOUNDARY_TAGS_H