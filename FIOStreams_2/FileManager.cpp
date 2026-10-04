#include "FileManager.h"
#include "ItemFabric.h"
#include <fstream>
#include <sstream>
#include <vector>

bool FileManager::save(const std::string& path, const ItemArray& arr) {
	std::ofstream out;
	out.open(path, std::ios::binary | std::ios::trunc);
	if (!out.is_open()) return false;

	for (int i = 0; i < arr.getCount(); ++i) {
		const Item* item = arr[i];
		if (!item) continue;

		int type = item->type();

		std::ostringstream buf(std::ios::binary);
		item->write(buf);
		if (buf.fail()) { out.close(); return false; }
		std::string payload = buf.str();
		int size = static_cast<int>(payload.size());

		out.write(reinterpret_cast<const char*>(&type), sizeof(type));
		out.write(reinterpret_cast<const char*>(&size), sizeof(size));
		out.write(payload.data(), size);

		if (!out.good()) { out.close(); return false; }
	}
	out.close();
	return true;
}

bool FileManager::load(const std::string& path, ItemArray& arr) {
	std::ifstream in;
	in.open(path, std::ios::binary);
	if (!in.is_open()) return false;

	while (true) {
		int type = 0, size = 0;
		in.read(reinterpret_cast<char*>(&type), sizeof(type));
		if (in.eof()) break;
		if (in.fail()) { in.close(); return false; }

		in.read(reinterpret_cast<char*>(&size), sizeof(size));
		if (in.fail() || size < 0 || size > 10 * 1024 * 1024) { in.close(); return false; }

		std::string payload(size, '\0');
		in.read(&payload[0], size);
		if (in.fail()) { in.close(); return false; }

		Item* item = ItemFabric::create(type);
		if (!item) { in.close(); return false; }

		std::istringstream buf(payload, std::ios::binary);
		item->readBin(buf);
		if (buf.fail()) { delete item; in.close(); return false; }

		arr.add(item);
	}
	in.close();
	return true;
}

bool FileManager::append(const std::string& path, const Item* item) {
	if (!item) return false;
	std::ofstream out;
	out.open(path, std::ios::binary | std::ios::app);
	if (!out.is_open()) return false;

	int type = item->type();
	std::ostringstream buf(std::ios::binary);
	item->write(buf);
	if (buf.fail()) { out.close(); return false; }
	std::string payload = buf.str();
	int size = static_cast<int>(payload.size());

	out.write(reinterpret_cast<const char*>(&type), sizeof(type));
	out.write(reinterpret_cast<const char*>(&size), sizeof(size));
	out.write(payload.data(), size);
	bool ok = out.good();
	out.close();
	return ok;
}

Item* FileManager::readAt(const std::string& path, int index) {
	if (index < 0) return nullptr;
	std::ifstream in(path, std::ios::binary);
	if (!in.is_open()) return nullptr;

	for (int i = 0; ; ++i) {
		int type = 0, size = 0;
		in.read(reinterpret_cast<char*>(&type), sizeof(type));
		if (in.eof() || in.fail()) return nullptr;
		in.read(reinterpret_cast<char*>(&size), sizeof(size));
		if (in.fail() || size < 0) return nullptr;

		if (i < index) {
			in.seekg(size, std::ios::cur);
			if (in.fail()) return nullptr;
			continue;
		}

		std::string payload(size, '\0');
		in.read(&payload[0], size);
		if (in.fail()) return nullptr;

		Item* item = ItemFabric::create(type);
		if (!item) return nullptr;

		std::istringstream buf(payload, std::ios::binary);
		item->readBin(buf);
		if (buf.fail()) { delete item; return nullptr; }
		return item;
	}
}

bool FileManager::replaceAt(const std::string& path, int index, const Item* item) {
	ItemArray tmp;
	if (!FileManager::load(path, tmp)) return false;
	if (index < 0 || index >= tmp.getCount()) return false;

	Item* copy = item->clone();
	if (!tmp.replace(index, copy)) { delete copy; return false; }
	return FileManager::save(path, tmp);
}

bool FileManager::removeAt(const std::string& path, int index) {
	ItemArray tmp;
	if (!FileManager::load(path, tmp)) return false;
	if (index < 0 || index >= tmp.getCount()) return false;

	Item* obj = tmp[index];
	return tmp.removeByName(obj->getName());
}

int FileManager::count(const std::string& path) {
	std::ifstream in(path, std::ios::binary);
	if (!in.is_open()) return 0;
	int n = 0;
	while (true) {
		int type = 0, size = 0;
		in.read(reinterpret_cast<char*>(&type), sizeof(type));
		if (in.eof() || in.fail()) break;
		in.read(reinterpret_cast<char*>(&size), sizeof(size));
		if (in.fail() || size < 0) break;
		in.seekg(size, std::ios::cur);
		if (in.fail()) break;
		++n;
	}
	return n;
}
