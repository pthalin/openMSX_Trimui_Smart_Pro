#include "StringOp.hh"
#include "MSXException.hh"
#include "likely.hh"
#include "ranges.hh"
#include "stl.hh"
#include "view.hh"
#include <cstdlib>
#include <stdexcept>

using std::string;
using std::string_view;
using std::vector;

namespace StringOp {

int stringToInt(const string& str)
{
	return strtol(str.c_str(), nullptr, 0);
}
bool stringToInt(const string& str, int& result)
{
	char* endptr;
	result = strtol(str.c_str(), &endptr, 0);
	return *endptr == '\0';
}

unsigned stringToUint(const string& str)
{
	return strtoul(str.c_str(), nullptr, 0);
}
bool stringToUint(const string& str, unsigned& result)
{
	char* endptr;
	result = strtoul(str.c_str(), &endptr, 0);
	return *endptr == '\0';
}

uint64_t stringToUint64(const string& str)
{
	return strtoull(str.c_str(), nullptr, 0);
}

bool stringToBool(string_view str)
{
	if (str == "1") return true;
	if ((str.size() == 4) && (strncasecmp(str.data(), "true", 4) == 0))
		return true;
	if ((str.size() == 3) && (strncasecmp(str.data(), "yes", 3) == 0))
		return true;
	return false;
}

double stringToDouble(const string& str)
{
	return strtod(str.c_str(), nullptr);
}
bool stringToDouble(const string& str, double& result)
{
	char* endptr;
	result = strtod(str.c_str(), &endptr);
	return *endptr == '\0';
}

string toLower(string_view str)
{
	string result(str);
	transform_in_place(result, ::tolower);
	return result;
}

bool startsWith(string_view total, string_view part)
{
	return (total.size() >= part.size()) &&
	       (memcmp(total.data(), part.data(), part.size()) == 0);
}
bool startsWith(string_view total, char part)
{
	return !total.empty() && (total.front() == part);
}

bool endsWith(string_view total, string_view part)
{
	return (total.size() >= part.size()) &&
	       (memcmp(total.data() + total.size() - part.size(), part.data(), part.size()) == 0);
}
bool endsWith(string_view total, char part)
{
	return !total.empty() && (total.back() == part);
}

void trimRight(string& str, const char* chars)
{
	auto pos = str.find_last_not_of(chars);
	if (pos != string::npos) {
		str.erase(pos + 1);
	} else {
		str.clear();
	}
}
void trimRight(string& str, char chars)
{
	auto pos = str.find_last_not_of(chars);
	if (pos != string::npos) {
		str.erase(pos + 1);
	} else {
		str.clear();
	}
}
void trimRight(string_view& str, string_view chars)
{
	while (!str.empty() && (chars.find(str.back()) != string_view::npos)) {
		str.remove_suffix(1);
	}
}
void trimRight(string_view& str, char chars)
{
	while (!str.empty() && (str.back() == chars)) {
		str.remove_suffix(1);
	}
}

void trimLeft(string& str, const char* chars)
{
	str.erase(0, str.find_first_not_of(chars));
}
void trimLeft(string& str, char chars)
{
	str.erase(0, str.find_first_not_of(chars));
}
void trimLeft(string_view& str, string_view chars)
{
	while (!str.empty() && (chars.find(str.front()) != string_view::npos)) {
		str.remove_prefix(1);
	}
}
void trimLeft(string_view& str, char chars)
{
	while (!str.empty() && (str.front() == chars)) {
		str.remove_prefix(1);
	}
}

void trim(string_view& str, string_view chars)
{
	trimRight(str, chars);
	trimLeft (str, chars);
}

void trim(string_view& str, char chars)
{
	trimRight(str, chars);
	trimLeft (str, chars);
}

std::pair<string_view, string_view> splitOnFirst(string_view str, string_view chars)
{
	auto pos = str.find_first_of(chars);
	if (pos == string_view::npos) {
		return {str, string_view{}};
	} else {
		return {str.substr(0, pos), str.substr(pos + 1)};
	}
}
std::pair<string_view, string_view> splitOnFirst(string_view str, char chars)
{
	auto pos = str.find_first_of(chars);
	if (pos == string_view::npos) {
		return {str, string_view{}};
	} else {
		return {str.substr(0, pos), str.substr(pos + 1)};
	}
}

std::pair<string_view, string_view> splitOnLast(string_view str, string_view chars)
{
	auto pos = str.find_last_of(chars);
	if (pos == string_view::npos) {
		return {string_view{}, str};
	} else {
		return {str.substr(0, pos), str.substr(pos + 1)};
	}
}
std::pair<string_view, string_view> splitOnLast(string_view str, char chars)
{
	auto pos = str.find_last_of(chars);
	if (pos == string_view::npos) {
		return {string_view{}, str};
	} else {
		return {str.substr(0, pos), str.substr(pos + 1)};
	}
}

vector<string_view> split(string_view str, char chars)
{
	vector<string_view> result;
	while (!str.empty()) {
		auto [first, last] = splitOnFirst(str, chars);
		result.push_back(first);
		str = last;
	}
	return result;
}

static unsigned parseNumber(string_view str)
{
	trim(str, " \t");
	if (!str.empty()) {
		try {
			return fast_stou(str);
		} catch (std::invalid_argument&) {
			// parse error
		}
	}
	throw openmsx::MSXException("Invalid integer: ", str);
}

static void insert(unsigned x, vector<unsigned>& result, unsigned min, unsigned max)
{
	if ((x < min) || (x > max)) {
		throw openmsx::MSXException("Out of range");
	}
	auto it = ranges::lower_bound(result, x);
	if ((it == end(result)) || (*it != x)) {
		result.insert(it, x);
	}
}

static void parseRange2(string_view str, vector<unsigned>& result,
                        unsigned min, unsigned max)
{
	// trimRight only: here we only care about all spaces
	trimRight(str, " \t");
	if (str.empty()) return;

	auto pos = str.find('-');
	if (pos == string_view::npos) {
		insert(parseNumber(str), result, min, max);
	} else {
		unsigned begin = parseNumber(str.substr(0, pos));
		unsigned end   = parseNumber(str.substr(pos + 1));
		if (end < begin) {
			std::swap(begin, end);
		}
		for (unsigned i = begin; i <= end; ++i) {
			insert(i, result, min, max);
		}
	}
}

vector<unsigned> parseRange(string_view str, unsigned min, unsigned max)
{
	vector<unsigned> result;
	while (true) {
		auto next = str.find(',');
		string_view sub = (next == string_view::npos)
		               ? str
		               : str.substr(0, next++);
		parseRange2(sub, result, min, max);
		if (next == string_view::npos) break;
		str = str.substr(next);
	}
	return result;
}

unsigned fast_stou(string_view s)
{
	unsigned result = 0;
	for (char c : s) {
		unsigned d = c - '0';
		if (unlikely(d > 9)) {
			throw std::invalid_argument("fast_stoi");
		}
		result *= 10;
		result += d;
	}
	return result;
}

#if defined(__APPLE__)

std::string fromCFString(CFStringRef str)
{
	// Try the quick route first.
	const char *cstr = CFStringGetCStringPtr(str, kCFStringEncodingUTF8);
	if (cstr) {
		// String was already in UTF8 encoding.
		return std::string(cstr);
	}

	// Convert to UTF8 encoding.
	CFIndex len = CFStringGetLength(str);
	CFRange range = CFRangeMake(0, len);
	CFIndex usedBufLen = 0;
	CFStringGetBytes(
		str, range, kCFStringEncodingUTF8, '?', false, nullptr, len, &usedBufLen);
	UInt8 buffer[usedBufLen];
	CFStringGetBytes(
		str, range, kCFStringEncodingUTF8, '?', false, buffer, len, &usedBufLen);
	return std::string(reinterpret_cast<const char *>(buffer), usedBufLen);
}

#endif

} // namespace StringOp
