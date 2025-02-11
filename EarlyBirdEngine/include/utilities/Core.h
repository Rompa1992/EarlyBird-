#pragma once 

#include <map>
#include <memory>
#include <stdio.h>
#include <unordered_map>
#include <unordered_set>

namespace eb
{
    /* unique_ptr: A smart pointer that owns and manages a dynamically allocated object.
       - Use case: When you need exclusive ownership of a resource (no sharing).
       - Why use it: Automatically deletes the object when the unique_ptr goes out of scope, preventing memory leaks.
       - Why not use shared_ptr: If you don't need shared ownership, unique_ptr is more efficient (no reference counting overhead). */
    template<typename T>
    using unique_ptr = std::unique_ptr<T>;

    /* shared_ptr: A smart pointer that shares ownership of a dynamically allocated object.
       - Use case: When multiple parts of your code need to share ownership of the same resource.
       - Why use it: Automatically deletes the object when the last shared_ptr referencing it goes out of scope.
       - Why not use unique_ptr: If you need shared ownership, unique_ptr cannot be copied or shared. */
    template<typename T>
    using shared_ptr = std::shared_ptr<T>;

    /* weak_ptr: A smart pointer that holds a non-owning ("weak") reference to an object managed by shared_ptr.
       - Use case: When you need to observe or access a resource without affecting its lifetime.
       - Why use it: Prevents circular references that can cause memory leaks with shared_ptr.
       - Why not use shared_ptr: If you don't need to extend the lifetime of the resource, weak_ptr avoids unnecessary reference counting. */
    template<typename T>
    using weak_ptr = std::weak_ptr<T>;

    /* List: A dynamic array (vector) that stores elements in a contiguous block of memory.
       - Use case: When you need a resizable array with fast random access.
       - Why use it: Provides efficient iteration and access by index.
       - Why not use std::list: If you don't need frequent insertions/deletions in the middle of the list, std::vector is more cache-friendly. */
    template<typename T>
    using List = std::vector<T>;

    /* Map: An associative container that stores key-value pairs in a sorted order.
       - Use case: When you need to store and retrieve values by a unique key, with keys sorted in a specific order.
       - Why use it: Provides O(log n) lookup, insertion, and deletion.
       - Why not use std::unordered_map: If you need sorted keys, std::map is the better choice. Otherwise, std::unordered_map provides faster average-case performance (O(1)). */
    template<typename keyType, typename valueType, typename predicate = std::less<keyType>> // default predicate is in ascending order.
    using Map = std::map<keyType, valueType, predicate>;

    /* Set: An unordered collection of unique elements.
       - Use case: When you need to store unique elements and don't care about their order.
       - Why use it: Provides O(1) average-case lookup, insertion, and deletion.
       - Why not use std::set: If you need sorted elements, use std::set. Otherwise, std::unordered_set is faster. */
    template<typename T>
    using Set = std::unordered_set<T>;

    // ANSI color codes for console output
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

// Macros forconsole output
#define PRINT_COLOR(color, log, ...) printf("%s" log "\n" RESET, color, ##__VA_ARGS__);
#define PRINT(log, ...) printf(log "\n", ##__VA_ARGS__);
}