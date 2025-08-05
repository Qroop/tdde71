#include <cstddef>
#include <stdexcept>
#include <iostream>
#include <string>

#pragma once

class TimeMicro {
public:
	TimeMicro();
	TimeMicro(const size_t hour, const size_t minute, const size_t second, const size_t milliseconds = 0);
	TimeMicro(const std::string& time_str);

	std::string to_string() const;
	std::string to_string(const bool& twelve_h) const;

	// Postfix & Prefix increment and decrement operators
	TimeMicro& operator++(); // Prefix increment
	TimeMicro operator++(int); // Postfix increment
	TimeMicro& operator--(); // Prefix decrement
	TimeMicro operator--(int); // Postfix decrement

	// Overloaded operators
	bool operator==(const TimeMicro& other) const;
	bool operator!=(const TimeMicro& other) const;
	bool operator<(const TimeMicro& other) const;
	bool operator<=(const TimeMicro& other) const;
	bool operator>(const TimeMicro& other) const;
	bool operator>=(const TimeMicro& other) const;

	// Arithmetic operators
	float operator-(const TimeMicro& other) const;

	// Stream operators

	bool is_am() const;
	int get_hour() const;
	int get_minute() const;
	int get_second() const;

private:
	float total_seconds;
};
	
