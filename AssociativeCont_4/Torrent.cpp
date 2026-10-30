#include "Torrent.h"
#include <iomanip>

Torrent::Torrent()
	: id(0),
	name(),
	totalSize(0.0),
	category(),
	uploaderName(),
	createdAt(),
	seeders(0),
	leechers(0)
{
}

Torrent::Torrent(int id, const std::string& name, double totalSize,
	const std::string& category, const std::string& uploaderName,
	const Date& createdAt, int seeders, int leechers, int ownerCode)
	: id(0),
	name(name),
	totalSize(totalSize),
	category(category),
	uploaderName(uploaderName),
	createdAt(createdAt),
	seeders(seeders),
	leechers(leechers),
	ownerCode(ownerCode)
{
	if (this->seeders < 0)
		this->seeders = 0;

	if (this->leechers < 0)
		this->leechers = 0;

	if (this->totalSize < 0)
		this->totalSize = 0.0;
}

int Torrent::getId() const
{
	return id;
}

const std::string& Torrent::getName() const
{
	return name;
}

double Torrent::getTotalSize() const
{
	return totalSize;
}

const std::string& Torrent::getCategory() const
{
	return category;
}

const std::string& Torrent::getUploaderName() const
{
	return uploaderName;
}

Date Torrent::getCreatedAt() const
{
	return createdAt;
}

int Torrent::getSeeders() const
{
	return seeders;
}

int Torrent::getLeechers() const
{
	return leechers;
}

int Torrent::getOwnerCode() const
{
	return ownerCode;
}

void Torrent::setId(int id)
{
	this->id = id;
}

void Torrent::setName(const std::string& name)
{
	this->name = name;
}

void Torrent::setTotalSize(double totalSize)
{
	if (totalSize < 0)
		return;

	this->totalSize = totalSize;
}

void Torrent::setCategory(const std::string& category)
{
	this->category = category;
}

void Torrent::setUploaderName(const std::string& uploaderName)
{
	this->uploaderName = uploaderName;
}

void Torrent::setCreatedAt(const Date& createdAt)
{
	this->createdAt = createdAt;
}

void Torrent::setSeeders(int seeders)
{
	if (seeders < 0)
		return;

	this->seeders = seeders;
}

void Torrent::setLeechers(int leechers)
{
	if (leechers < 0)
		return;

	this->leechers = leechers;
}

void Torrent::setOwnerCode(int ownerCode)
{
	this->ownerCode = ownerCode;
}

void Torrent::print(std::ostream& os) const
{
	os.setf(std::ios::showpoint);
	os << std::left
		<< std::setw(6) << id << " | "
		<< std::setw(40) << name << " | "
		<< std::right
		<< std::setw(10) << totalSize << " | "
		<< std::left
		<< std::setw(15) << category << " | "
		<< std::setw(20) << uploaderName << " | "
		<< std::setw(12) << createdAt << " | "
		<< std::right
		<< std::setw(6) << seeders << " | "
		<< std::setw(6) << leechers << " | ";
	os.unsetf(std::ios::showpoint);
}

void Torrent::read(std::istream& is)
{

	std::cout << "Название: \n";
	std::getline(is, name);
	if (is.fail())
		return;

	std::cout << "Общий размер (ГБ): ";
	is >> totalSize;
	if (is.fail() || totalSize < 0) {
		is.clear();
		is.ignore(100000, '\n');
		is.setstate(std::ios::failbit);
		return;
	}
	is.ignore(100000, '\n');

	std::cout << "Категория: \n";
	std::getline(is, category);
	if (is.fail())
		return;

	std::cout << "Имя загрузившего: \n";
	std::getline(is, uploaderName);
	if (is.fail())
		return;

	std::cout << "Дата создания (дд.мм.гггг): ";
	is >> createdAt;
	if (is.fail())
		return;
	is.ignore(100000, '\n');

	std::cout << "Раздающих (seeders): ";
	is >> seeders;
	if (is.fail() || seeders < 0) {
		is.clear();
		is.ignore(100000, '\n');
		is.setstate(std::ios::failbit);
		return;
	}
	is.ignore(100000, '\n');

	std::cout << "Скачивающих (leechers): ";
	is >> leechers;
	if (is.fail() || leechers < 0) {
		is.clear();
		is.ignore(100000, '\n');
		is.setstate(std::ios::failbit);
		return;
	}
	is.ignore(100000, '\n');
}

void Torrent::writeString(std::ostream& os, const std::string& s)
{
	int len = static_cast<int>(s.size());
	os.write(reinterpret_cast<const char*>(&len), sizeof(len));
	os.write(s.data(), len);
}

void Torrent::readString(std::istream& is, std::string& s)
{
	int len = 0;
	is.read(reinterpret_cast<char*>(&len), sizeof(len));
	if (is.fail() || len < 0 || len > 100000) {
		is.setstate(std::ios::failbit);
		return;
	}
	s.resize(len);
	if (len > 0)
		is.read(&s[0], len);
	if (is.fail())
		is.setstate(std::ios::failbit);
}

void Torrent::writeBase(std::ostream& os) const
{
	os.write(reinterpret_cast<const char*>(&id), sizeof(id));
	writeString(os, name);
	os.write(reinterpret_cast<const char*>(&totalSize), sizeof(totalSize));
	writeString(os, category);
	writeString(os, uploaderName);
	createdAt.write(os);
	os.write(reinterpret_cast<const char*>(&seeders), sizeof(seeders));
	os.write(reinterpret_cast<const char*>(&leechers), sizeof(leechers));
}

void Torrent::readBase(std::istream& is)
{
	is.read(reinterpret_cast<char*>(&id), sizeof(id));
	if (is.fail() || id < 0) {
		is.setstate(std::ios::failbit);
		return;
	}

	readString(is, name);
	if (is.fail())
		return;

	is.read(reinterpret_cast<char*>(&totalSize), sizeof(totalSize));
	if (is.fail() || totalSize < 0) {
		is.setstate(std::ios::failbit);
		return;
	}

	readString(is, category);
	if (is.fail())
		return;

	readString(is, uploaderName);
	if (is.fail())
		return;

	createdAt.read(is);
	if (is.fail())
		return;

	is.read(reinterpret_cast<char*>(&seeders), sizeof(seeders));
	if (is.fail() || seeders < 0) {
		is.setstate(std::ios::failbit);
		return;
	}

	is.read(reinterpret_cast<char*>(&leechers), sizeof(leechers));
	if (is.fail() || leechers < 0) {
		is.setstate(std::ios::failbit);
		return;
	}
}

bool Torrent::operator==(const Torrent& other) const
{
	return seeders == other.seeders && leechers == other.leechers;
}

bool Torrent::operator!=(const Torrent& other) const
{
	return !(*this == other);
}

bool Torrent::operator<(const Torrent& other) const
{
	if (seeders != other.seeders)
		return seeders < other.seeders;

	return leechers < other.leechers;
}

bool Torrent::operator>(const Torrent& other) const
{
	return other < *this;
}

bool Torrent::operator<=(const Torrent& other) const
{
	return !(other < *this);
}

bool Torrent::operator>=(const Torrent& other) const
{
	return !(*this < other);
}

std::istream& operator>>(std::istream& is, Torrent& t)
{
	t.read(is);
	return is;
}

std::ostream& operator<<(std::ostream& os, const Torrent& t)
{
	t.print(os);
	return os;
}