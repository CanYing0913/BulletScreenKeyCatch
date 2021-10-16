/**
 * @file zalg.h
 * Declarations of z-algorithm pattern matching functions.
 */

#pragma once

#include <string>
#include <vector>

int create_zarray(std::string S, int* Z);
std::vector<int> zalg_search(std::string P, std::string T);