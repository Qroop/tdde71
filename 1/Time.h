#include <cstddef>
#include <stdexcept>
#include <string>

#pragma once

class Time {
public:
	Time();
	Time(const size_t hour, const size_t minute, const size_t second);
	Time(const std::string& time_str);

	std::string to_string() const;
	std::string to_string(const bool& twelve_h) const;

	bool is_am() const;
	int get_hour() const;
	int get_minute() const;
	int get_second() const;

private:
	const size_t total_seconds;
};
