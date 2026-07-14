#pragma once

#include <iostream>
#include <mutex>

class Singleton final
{
private:
	std::mutex mutex;

	Singleton() = default;
	Singleton(const Singleton&) = delete;
	
	Singleton& operator=(const Singleton&) = delete;
	Singleton(Singleton&&) = delete;

	Singleton& operator=(Singleton&&) = delete;
	~Singleton() {};

public:
	static Singleton& getInstance() {
		static Singleton instance;
		return instance;
	}
};