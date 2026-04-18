#include <cstdlib>
#include <string>
#include "gtest/gtest.h"
#include "formatting.h"
#include "test_helpers.h"
#include "rapidcheck/gtest.h"

auto word_generator() {
    /* Creates a generator for a string made up of
     * characters from [a - z]
     */
    return rc::gen::container<std::string>(
        rc::gen::inRange<char>('a', '{') // { is next on the ASCII after z, because we need inRange z+1
    );
}

auto vector_of_ints_to_vector_of_strings(const std::vector<int>& numbers) {
    /* Create a vector of strings from a vector of ints
     */
    std::vector<std::string> result;
    for (int n : numbers) {
        result.push_back(std::to_string(n));
    }
    return result;
}


TEST(ParseArgsTests, SimpleCheckArgumentsParsedSuccessfully) {
    /*
     * Check that you parse the command line arguments correctly.
     * (ar_out and len_out are set to the right values).
     * Don't forget to free any memory that was dynamically allocated as part of your test.'
     */
    std::vector<std::string> args = {"prog", "4", "-2", "7", "10"};
    std::vector<char*> argv;
    for (auto& s : args) {
        argv.push_back(&s[0]);
    }

    int* ar_out = nullptr;
    int len_out = 0;

    parse_args(argv.size(), argv.data(), &ar_out, &len_out);

    EXPECT_EQ(len_out, 4);
    EXPECT_EQ(ar_out[0], 4);
    EXPECT_EQ(ar_out[1], -2);
    EXPECT_EQ(ar_out[2], 7);
    EXPECT_EQ(ar_out[3], 10);

    free(ar_out);
}

TEST(ParseArgsTests, SimpleCheckParseNoArgs) {
    /*
     * Check that you parse you can successfully parse "no" command line arguments.
     */
    std::vector<std::string> args = {"prog"};
    std::vector<char*> argv;
    for (auto& s : args) {
        argv.push_back(&s[0]);
    }

    int* ar_out = nullptr;
    int len_out = 0;

    parse_args(argv.size(), argv.data(), &ar_out, &len_out);

    EXPECT_EQ(len_out, 0);
    EXPECT_EQ(ar_out, nullptr);
}


RC_GTEST_PROP(ParseArgsTests,
              PropertyCheckArgumentsParsedSuccessfully,
              ()
) {
    /* Check that we can correctly parse the command line
     * arguments when we receive 1 or more arguments.
     * Don't forget to free any memory that was dynamically allocated as part of this test
     */
    std::vector<int> values = *rc::gen::nonEmpty<std::vector<int>>();
    std::vector<std::string> args = {"prog"};
    std::vector<std::string> number_strings = vector_of_ints_to_vector_of_strings(values);

    for (const auto& s : number_strings) {
        args.push_back(s);
    }

    std::vector<char*> argv;
    for (auto& s : args) {
        argv.push_back(&s[0]);
    }

    int* ar_out = nullptr;
    int len_out = 0;

    parse_args(argv.size(), argv.data(), &ar_out, &len_out);

    RC_ASSERT(len_out == static_cast<int>(values.size()));

    for (size_t i = 0; i < values.size(); i++) {
        RC_ASSERT(ar_out[i] == values[i]);
    }

    free(ar_out);
}

RC_GTEST_PROP(ParseArgsTests,
              PropertyCheckParseNoArgs,
              ()
) {
    /*
     * Check that you parse you can successfully parse "no" command line arguments.
     */
    std::vector<std::string> args = {"prog"};
    std::vector<char*> argv;
    for (auto& s : args) {
        argv.push_back(&s[0]);
    }

    int* ar_out = nullptr;
    int len_out = 0;

    parse_args(argv.size(), argv.data(), &ar_out, &len_out);

    RC_ASSERT(len_out == 0);
    RC_ASSERT(ar_out == nullptr);
}
