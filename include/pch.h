#ifndef PCH_H
#define PCH_H

// STL
#include <algorithm>
#include <assert.h>
#include <bitset>
#include <cassert>
#include <chrono>
#include <fstream>
#include <functional>
#include <iostream>
#include <istream>
#include <limits>
#include <map>
#include <memory>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <stdint.h>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "raylib.h"

template <typename T> using Shared = std::shared_ptr<T>;
template <typename T> using Unique = std::unique_ptr<T>;
template <typename T> using Weak = std::weak_ptr<T>;

#define INVALID_ID -1

#define TEMPLATE template <typename T>

#endif // PCH_H
