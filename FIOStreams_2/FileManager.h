#pragma once
#include <string>
#include <vector>
#include "Item.h"
#include "ItemArray.h"

class FileManager {
public:
	static bool save(const std::string& path, const ItemArray& arr);
	static bool load(const std::string& path, ItemArray& arr);

	static bool  append(const std::string& path, const Item* item);
	static Item* readAt(const std::string& path, int index);
	static bool  replaceAt(const std::string& path, int index, const Item* item);
	static bool  removeAt(const std::string& path, int index);
	static int   count(const std::string& path);
};
