#include "allocator/allocator_boundary_tags/include/allocator_boundary_tags.h"
#include "allocator/allocator_global_heap/include/allocator_global_heap.h"
#include "b-tree/b_tree.h"
#include "cw/database/include/data_base.h"
#include <iostream>
#include <random>

std::mt19937 &getRandomGenerator()
{
    static std::mt19937 generator(static_cast<unsigned long>(std::time(nullptr)));
    return generator;
}

std::string generate_random_string(size_t length)
{
    const std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			      "abcdefghijklmnopqrstuvwxyz"
			      "0123456789";

    std::mt19937 &generator = getRandomGenerator();
    std::uniform_int_distribution<size_t> distribution(0, chars.size() - 1);

    std::string randomString;
    randomString.reserve(length);

    for (size_t i = 0; i < length; ++i)
    {
	    randomString += chars[distribution(generator)];
    }

    return randomString;
}

/*

FOR PROGRAM ARGS:

in_memory
filesystem
?request_dialog
D:\Study\cw_os\files\test.txt in_memory
D:\Study\cw_os\files\test.txt filesystem
?request_dialog in_memory
?request_dialog filesystem

*/

int main(int argc, char **argv)
{
    std::string db_name = "MyDB\\onLr";/* + generate_random_string(4)*/

    allocator *alloc = new allocator_boundary_tags(1'000'000, nullptr, nullptr, allocator_with_fit_mode::fit_mode::first_fit);
    std::string input = argv[1];
    if (argc == 2)
    {
        if (!(input.compare("in_memory")) || !(input.compare("filesystem")))
        {
            std::cerr << "No input file <FILE> or dialog request <?request_dialog>" << std::endl;
            return 1;
        }
//        data_base db_1(db_name);
//        С подключением кастомного аллокатора
        data_base db_1(db_name, storage_interface<std::string, schemas_pool>::storage_strategy::filesystem, alloc);
        if (!(input.compare("?request_dialog")))
        {
            db_1.start_console_dialog();
        }
        else
        {
            db_1.execute_command_from_file(argv[1]);
        }
    }

    else if (argc > 2)
    {
        std::string input_2 = argv[2];
        if (!(input_2.compare("filesystem")))
        {
            if (std::filesystem::exists(std::filesystem::absolute(db_name))) {
                std::filesystem::remove_all(db_name);
            }

            data_base db_1(db_name, storage_interface<std::string, schemas_pool>::storage_strategy::filesystem);

            if (!(input.compare("?request_dialog")))
            {
                db_1.start_console_dialog();
            }
            else
            {
                db_1.execute_command_from_file(argv[1]);
            }
        }
        else {
            data_base db_1(db_name);

            if (!(input.compare("?request_dialog")))
            {
                db_1.start_console_dialog();
            }
            else
            {
                db_1.execute_command_from_file(argv[1]);
            }
        }
    }
    else {
        std::cerr << "No storage strategy; No input file <FILE> or dialog request <?request_dialog>" << std::endl;
        return -1;
    }
}