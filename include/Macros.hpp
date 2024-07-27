#pragma once
#include <source_location>
#include <iostream>


inline void Assert(bool Condition, std::source_location Location = std::source_location::current()) {
	if (!Condition) {
		std::cout << "Assertion failed at " << Location.file_name() << " (" << Location.line() << ", " << Location.column() << ")" << std::endl;
		abort();
	}
}