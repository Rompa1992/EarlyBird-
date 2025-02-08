#pragma once 

#include <map>
#include <memory>
#include <stdio.h>
#include <unordered_map>
#include <unordered_set>

namespace eb
{
	template<typename T>
	using unique_ptr = std::unique_ptr<T>;

	template<typename T>
	using shared_ptr = std::shared_ptr<T>;

	template<typename T>
	using weak_ptr = std::weak_ptr<T>;

	template<typename T>
	using List = std::vector<T>;

	template<typename keyType, typename valueType, typename predicate = std::less<keyType>>				// default predicate is in ascending order.  
	using Map = std::map<keyType, valueType, predicate>;


#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

#define PRINT_COLOR(color, log, ...) printf("%s" log "\n" RESET, color, ##__VA_ARGS__);
#define PRINT(log, ...) printf(log "\n", ##__VA_ARGS__);
}