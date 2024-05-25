#include <gtest/gtest.h>

#include <memory>
#include <stdexcept>

#include "bagel/dynamic_library.hpp"

TEST(DynamicLibrary, DefaultConstructor) {
    bagel::DynamicLibrary dl{};
    using Fn = void(*)();
    Fn badFn = dl.sym<Fn>("blah");
    EXPECT_EQ(badFn, nullptr);
}

TEST(DynamicLibrary, LoadingCorrectPath) {
    bagel::DynamicLibrary dl("./libdynamic_lib_example.my_lib", RTLD_LAZY);
}

TEST(DynamicLibrary, LoadingIncorrectPath) {
    EXPECT_THROW(bagel::DynamicLibrary dl("./blah", RTLD_LAZY), std::invalid_argument);
}

TEST(DynamicLibrary, InvokePointerFunction) {
    bagel::DynamicLibrary dl("./libdynamic_lib_example.my_lib", RTLD_LAZY);
    using Fn = int*(*)();
    Fn answerToLife = dl.sym<Fn>("answerToLifeHeap");
    std::unique_ptr<int> val(answerToLife());
    EXPECT_EQ(*val, 42);
}

TEST(DynamicLibrary, InvokePrimitiveFunction) {
    bagel::DynamicLibrary dl{"./libdynamic_lib_example.my_lib", RTLD_LAZY};
    using Fn = int(*)();
    Fn answerToLife = dl.sym<Fn>("answerToLife");
    EXPECT_EQ(answerToLife(), 42);
}

TEST(DynamicLibrary, CopyConstructor) {
    bagel::DynamicLibrary dl1{"./libdynamic_lib_example.my_lib", RTLD_LAZY};
    bagel::DynamicLibrary dl2{dl1};
    using Fn = int(*)();
    Fn answerToLife = dl2.sym<Fn>("answerToLife");
    EXPECT_EQ(answerToLife(), 42);
}

TEST(DynamicLibrary, CopyAssignment) {
    bagel::DynamicLibrary dl1{"./libdynamic_lib_example.my_lib", RTLD_LAZY};
    bagel::DynamicLibrary dl2 = dl1;
    using Fn = int(*)();
    Fn answerToLife = dl2.sym<Fn>("answerToLife");
    EXPECT_EQ(answerToLife(), 42);
}

TEST(DynamicLibrary, MoveConstructor) {
    bagel::DynamicLibrary dl1{"./libdynamic_lib_example.my_lib", RTLD_LAZY};
    bagel::DynamicLibrary dl2{std::move(dl1)};
    using Fn = int(*)();
    Fn answerToLife = dl2.sym<Fn>("answerToLife");
    EXPECT_EQ(answerToLife(), 42);
}

TEST(DynamicLibrary, MoveAssignment) {
    bagel::DynamicLibrary dl1{"./libdynamic_lib_example.my_lib", RTLD_LAZY};
    bagel::DynamicLibrary dl2 = std::move(dl1);
    using Fn = int(*)();
    Fn answerToLife = dl2.sym<Fn>("answerToLife");
    EXPECT_EQ(answerToLife(), 42);
}

TEST(DynamicLibrary, InvokeNonExistentFunction) {
    bagel::DynamicLibrary dl("./libdynamic_lib_example.my_lib", RTLD_LAZY);
    using Fn = void(*)();
    Fn badFn = dl.sym<Fn>("blah");
    EXPECT_EQ(badFn, nullptr);
}

TEST(DynamicLibrary, InvokeConstantFunction) {
    bagel::DynamicLibrary dl("./libdynamic_lib_example.my_lib", RTLD_LAZY);
    using Fn = double*(*)();
    Fn g = dl.sym<Fn>("g");
    EXPECT_FLOAT_EQ(*g(), 9.8);
}
