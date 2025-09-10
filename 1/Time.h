#include <cstddef>
#include <stdexcept>
#include <iostream>
#include <string>

#pragma once

class Time {
public:
	Time();
	Time(const size_t hour, const size_t minute, const size_t second);
	Time(const std::string& time_str);

	std::string to_string() const;
	std::string to_string(const bool& twelve_h) const;

	// Postfix & Prefix increment and decrement operators
	Time& operator++(); // Prefix increment
	Time operator++(int); // Postfix increment
	Time& operator--(); // Prefix decrement
	Time operator--(int); // Postfix decrement

	// Overloaded operators
	bool operator==(const Time& other) const;
	bool operator!=(const Time& other) const;
	bool operator<(const Time& other) const;
	bool operator<=(const Time& other) const;
	bool operator>(const Time& other) const;
	bool operator>=(const Time& other) const;

	bool is_am() const;
	int get_hour() const;
	int get_minute() const;
	int get_second() const;

private:
	size_t total_seconds;
};
	
