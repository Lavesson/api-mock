#ifndef T_UNIT_H
#define T_UNIT_H
#include <cmath>
#include <iostream>
#include <functional>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>

const std::string T_UNIT_VERSION = "t-unit v0.5.1";

// Macro to generate fixture classes - Don't invoke this macro directly. Use FIXTURE / SKIP_FIXTURE instead
#define FIXTURE_GEN(name, run_fixture)\
	namespace fixture_ns_##name\
{\
class fixture_##name : public test_fixture {\
public:\
	fixture_##name();\
} fixture_instance;\
	fixture_##name::fixture_##name() : test_fixture(#name, run_fixture) {\
	if (run_fixture) {\
	test_runner::register_fixture(this);\
	}\
};\
}\
	namespace fixture_ns_##name

#define FIXTURE(name) FIXTURE_GEN(name, true)
#define SKIP_FIXTURE(name) FIXTURE_GEN(name, false)

class test_fixture;
class asserter;

enum class test_status {
	ok, not_ok, skipped, inconclusive
};

// Abstract fixture hook class for setup/teardown hooks
class fixture_hook {
	friend class test_fixture;
	virtual void hook()=0;
};

// test timing
class timer {
private:
	std::chrono::system_clock::time_point start, end;

public:
	void start_time_measurement() {
		start = std::chrono::high_resolution_clock::now();
	}

	void end_time_measurement() {
		end = std::chrono::high_resolution_clock::now();
	}

	int calculate_duration_ms() const {
		auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
		return time;
	}
};

// This is merely a base class for the auto-generated test cases
struct test {
    const std::string label;
	bool run_test;
	timer t;
	test(const std::string& label, bool run_test) : label(label), run_test(run_test) {}

	virtual void execute() = 0;\
};

// Struct to represent metadata/diagnostics for failed assertions
struct test_diagnostics {
	test_diagnostics(const std::string& expected, const std::string& actual, const std::string& comment)
		: expected(expected), actual(actual), comment(comment) {}

	const std::string expected;
	const std::string actual;
	const std::string comment;
};

// Contains the results of a test after being run.
struct test_result
{
public:
	int id;
	int duration_ms;
	const test_status status;
	const std::string test_label;
	const test_diagnostics diagnostics;
	const bool ok;
	const bool skipped;

	test_result(int id, const test_status& status, const std::string& test_label, const test_diagnostics& diagnostics)
		: id(id), duration_ms(0), status(status), test_label(test_label), diagnostics(diagnostics), ok(status == test_status::ok), skipped(status == test_status::skipped) {}
	test_result(int id, const test_status& status, const std::string& test_label)
		: id(id), duration_ms(0), status(status), test_label(test_label), diagnostics(test_diagnostics("","","")), ok(status != test_status::not_ok), skipped(status == test_status::skipped) {}
};

// the assertions class
class asserter
{
private:
	test_fixture& that;
	template <typename T>
	std::string diagnostics_string(T expected, T actual, const std::string& comment);

public:
	inline explicit asserter(test_fixture& that) : that(that) {}
	inline void fail(const std::string& comment="");
	inline void is_true(bool statement, const std::string& comment="");
	inline void is_false(bool statement, const std::string& comment="");
	inline void are_equal(int expected, int actual, const std::string& comment="");
	inline void are_equal(float expected, float actual, const std::string& comment="");
	inline void are_equal(float expected, float actual, float delta, const std::string& comment="");
	inline void are_equal(double expected, double actual, const std::string& comment="");
	inline void are_equal(double expected, double actual, double delta, const std::string& comment="");
	inline void are_equal(const std::string& expected, const std::string& actual, const std::string& comment="");
	template <typename T> inline void are_equal(T expected, T actual, const std::string& comment="");
	template <typename T> inline void not_equal(T expected, T actual, const std::string& comment="");
	template <typename T> inline void is_nullptr(T* ptr, const std::string& comment="");
	template <typename T> inline void is_not_nullptr(T* ptr, const std::string& comment="");
	template <typename T> inline void throws(std::function<void()> call, const std::string& comment="");
	inline void no_throws(std::function<void()> call, const std::string& comment="");
};

// a test fixture, containing one or more tests
class test_fixture
{
private:
	timer t;
	fixture_hook* _setup;
	fixture_hook* _teardown;
public:
	test* current;
	const std::string name;
	bool run_fixture;
	std::vector<test*> tests;
	std::vector<test_result> results;
	test_fixture(const std::string& name, bool run_fixture) : _setup(nullptr), _teardown(nullptr), name(name), run_fixture(run_fixture) {}

	void reset()
	{
		results.clear();
	}

	void setup_callback(fixture_hook* hook)
	{
		_setup = hook;
	}

	void teardown_callback(fixture_hook* hook)
	{
		_teardown = hook;
	}

	void run()
	{
		t.start_time_measurement();
		for (auto t : tests) {
			if (_setup) _setup->hook();
			current = t;
			t->execute();
			if (_teardown) _teardown->hook();
		}
		t.end_time_measurement();
	}

	void add_test(test* t)
	{
		tests.push_back(t);
		current = t;
	}

	int test_count() const { return results.size(); }
	int total_test_count() const { return results.size(); }

	void report_duration_ms_for_current_test(int duration_ms) {
		if (results.size() > 0 && results.back().test_label == current->label) {
			results.back().duration_ms = duration_ms;
		}
	}

	int passed_test_count() const {
		int count=0;
		for (auto r : results) if (r.status == test_status::ok) count++;
		return count;
	}

	int failed_test_count() const {
		int count=0;
		for (auto r : results) if (r.status == test_status::not_ok) count++;
		return count;
	}

	int inconclusive_test_count() const {
		int count=0;
		for (auto r : results) if (r.status == test_status::inconclusive) count++;
		return count;
	}

	int skipped_test_count() const {
		int count=0;
		for (auto r : results) if (r.status == test_status::skipped) count++;
		return count;
	}

	int total_duration_ms() const {
		return t.calculate_duration_ms();
	}

	void add_test_result(bool ok, const std::string& test_name, const std::string& expected, const std::string& actual, const std::string& comment) {
		bool add_more = true;

		// Replacement
		if (results.size() > 0) {
			auto b = results.back();

			if (b.test_label == test_name) {
				add_more = (b.status == test_status::ok && !ok) || (b.status == test_status::inconclusive);
				if (add_more) results.pop_back();
			}
		}

		if (add_more)
			results.push_back(
			test_result(results.size(),
			(ok ? test_status::ok : test_status::not_ok),
			test_name, test_diagnostics(expected, actual, comment)));
	}

	void add_inconclusive_test_result(const std::string& test_name) {
		results.push_back(test_result(results.size(), test_status::inconclusive, test_name));
	}

	void add_skipped_test_result(const std::string& test_name) {
		results.push_back(test_result(results.size(), test_status::skipped, test_name));
	}
};

// Test harness representation
class test_harness {
private:
	const std::string _t_unit_version;
	std::vector<test_fixture*> _fixtures;
	timer _t;
public:
	test_harness(const std::string& t_unit_version, const std::vector<test_fixture*> fixtures)
		: _t_unit_version(t_unit_version), _fixtures(fixtures) {}

	void reset() {
		for (auto f : _fixtures) f->reset();
	}

	void run() {
		_t.start_time_measurement();
		for (auto f : _fixtures) f->run();
		_t.end_time_measurement();
	}

	const std::vector<test_fixture*>& fixtures() const {
		return _fixtures;
	}

	int num_total_tests() const {
		int n = 0;
		for (auto f : _fixtures) n += f->total_test_count();
		return n;
	}

	const std::string& t_unit_version() const {
		return _t_unit_version;
	}

	int num_fixtures() const {
		return _fixtures.size();
	}

	int num_passed_tests() const {
		int n = 0;
		for (auto f : _fixtures)  n += f->passed_test_count();
		return n;
	}

	int num_inconclusive_tests() const {
		int n = 0;
		for (auto f : _fixtures) n += f->inconclusive_test_count();
		return n;
	}

	int num_failed_tests() const {
		int n = 0;
		for (auto f : _fixtures)  n += f->failed_test_count();
		return n;
	}

	int num_skipped_tests() const {
		int n = 0;
		for (auto f : _fixtures) n += f->skipped_test_count();
		return n;
	}

	int duration_ms() const {
		auto time = _t.calculate_duration_ms();
		return time;
	}
};

// Macro for expanding test cases
#define TEST_GEN(name, run_test) \
class test_##name : public test\
{\
private:\
void content();\
asserter assert;\
test_fixture* owning_fixture;\
public:\
	void execute();\
	test_##name(test_fixture* fixture) : test(#name, run_test), assert(fixture_instance), owning_fixture(fixture) {\
	fixture->add_test(this);\
}\
} test_instance_##name(&fixture_instance);\
void test_##name::execute()\
{\
	if (!run_test)\
		owning_fixture->add_skipped_test_result(#name);\
	else {\
		owning_fixture->add_inconclusive_test_result(#name);\
		t.start_time_measurement();\
		content();\
		t.end_time_measurement();\
		owning_fixture->report_duration_ms_for_current_test(t.calculate_duration_ms());\
	}\
}\
void test_##name::content()\

#define TEST(name) TEST_GEN(name, true)
#define SKIP_TEST(name) TEST_GEN(name, false)

// Test Setup hook
#define SETUP()\
class setup_hook : public fixture_hook\
{\
private:\
	void hook();\
public:\
	setup_hook(test_fixture* fixture);\
} setup_instance(&fixture_instance);\
setup_hook::setup_hook(test_fixture* fixture)\
{\
	fixture->setup_callback(this);\
}\
void setup_hook::hook()

// Test Teardown hook
#define TEARDOWN()\
class teardown_hook : public fixture_hook\
{\
private:\
	void hook();\
public:\
	teardown_hook(test_fixture* fixture);\
} teardown_instance(&fixture_instance);\
teardown_hook::teardown_hook(test_fixture* fixture)\
{\
	fixture->teardown_callback(this);\
}\
void teardown_hook::hook()

// report generator base
class report_generator
{
public:
	virtual void generate_for(const test_harness& harness) = 0;
};

// runs tests in a given test fixture
class test_runner
{
public:
	static void run_all_tests() {
		auto harness = get_harness();
		harness->reset();
		harness->run();
	}

	static void register_fixture(test_fixture* tf) {
		test_runner::get_fixtures().push_back(tf);
	}

	static void create_report(report_generator& gen) {
		gen.generate_for(*get_harness());
	}

private:
	static test_harness* get_harness() {
		static test_harness harness(T_UNIT_VERSION, get_fixtures());
		return &harness;
	}

	static std::vector<test_fixture*>& get_fixtures() {
		static std::vector<test_fixture*> fixtures;
		return fixtures;
	}
};

// Assertions

template <typename T>
std::string asserter::diagnostics_string(T expected, T actual, const std::string& comment) {
	std::stringstream ss;
	ss << "# got: "		  << actual		<< std::endl;
	ss << "# expected: "  << expected	<< std::endl;
	if (comment != "") ss << "# " << comment << std::endl;
	return ss.str();
}

void asserter::is_true(bool statement, const std::string& comment) {
	statement ?
		that.add_test_result(true, that.current->label, "true", "true", comment) :
		that.add_test_result(false, that.current->label, "true", "false", comment);
}

void asserter::fail(const std::string& comment) {
	that.add_test_result(false, that.current->label, "[unknown]", "[unknown]", comment);
}

void asserter::is_false(bool statement, const std::string& comment) {
	!statement ?
		that.add_test_result(true, that.current->label, "false", "false", comment) :
		that.add_test_result(false, that.current->label, "false", "true", comment);
}

template <typename T>
void asserter::are_equal(T expected, T actual, const std::string& comment) {
	that.add_test_result(expected == actual, that.current->label, "[unknown]", "[unknown]", comment);
}

void asserter::are_equal(int expected, int actual, const std::string& comment) {
	that.add_test_result(expected == actual, that.current->label, std::to_string(expected), std::to_string(actual), comment);
}

void asserter::are_equal( float expected, float actual, const std::string& comment) {
	that.add_test_result(expected == actual, that.current->label, std::to_string(expected), std::to_string(actual), comment);
}

void asserter::are_equal( float expected, float actual, float delta, const std::string& comment) {
	that.add_test_result(expected - actual <= std::abs(delta), that.current->label, std::to_string(expected), std::to_string(actual), comment);
}

void asserter::are_equal(double expected, double actual, const std::string& comment)
{
	that.add_test_result(expected == actual, that.current->label, std::to_string(expected), std::to_string(actual), comment);
}

void asserter::are_equal(double expected, double actual, double delta, const std::string& comment)
{
	that.add_test_result(expected - actual <= std::abs(delta), that.current->label, std::to_string(expected), std::to_string(actual), comment);
}

void asserter::are_equal(const std::string& expected, const std::string& actual, const std::string& comment)
{
	that.add_test_result(expected == actual, that.current->label, expected, actual, comment);
}

template <typename T>
void asserter::not_equal(T expected, T actual, const std::string& comment) {
	that.add_test_result(expected != actual, that.current->label, "[unknown]", "[unknown]", comment);
}

template <typename T>
void asserter::throws(std::function<void()> call, const std::string& comment) {
	// We need to utilize RTTI here in order to output some information about the actual type excepted (and hopefully caught)
	try {
		call();
	} catch (T) {
		that.add_test_result(true, that.current->label,
			std::string("[") + typeid(T).name() + std::string("] as exception"),
			std::string("[") + typeid(T).name() + std::string("] as exception"), comment);
		return;
	} catch (...) {}

	that.add_test_result(false, that.current->label, std::string("[") + typeid(T).name() + std::string("] as exception"), "Incorrect or missing exception", comment);
}

template <typename T>
void asserter::is_nullptr(T* ptr, const std::string& comment) {
	(ptr == nullptr) ?
		that.add_test_result(true, that.current->label, "nullptr", "nullptr", comment) :
		that.add_test_result(false, that.current->label, "nullptr", "not nullptr", comment);
}

template <typename T>
void asserter::is_not_nullptr(T* ptr, const std::string& comment) {
	(ptr != nullptr) ?
		that.add_test_result(true, that.current->label, "not nullptr", "not nullptr", comment) :
		that.add_test_result(false, that.current->label, "not nullptr", "nullptr", comment);
}

void asserter::no_throws(std::function<void()> call, const std::string& comment) {
	try {
		call();
		that.add_test_result(true, that.current->label, "No exception thrown", "Exception thrown", comment);
	} catch (...) {
		that.add_test_result(false, that.current->label, "No exception thrown", "Exception thrown", comment);
	}
}

#endif
