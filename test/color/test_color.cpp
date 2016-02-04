#include <stdio.h>
#include <color/ColorShift.h>
#include "unity.h"


void test_Color_convert_RGBW_To32Bit_isCorrect(void) {
    Color color(0x11, 0x22, 0x33, 0x44);
    TEST_ASSERT_EQUAL_HEX32(0x44112233, color.color());
}

void test_Color_convert_RGB_To32Bit_isCorrect(void) {
    Color color(0x11, 0x22, 0x33);
    TEST_ASSERT_EQUAL_HEX32(0xff112233, color.color());
}

void test_Color_RGB_constructor_assigns_correct(void) {
    Color color(0x11, 0x22, 0x33);
    TEST_ASSERT_EQUAL_MESSAGE(0x11, color.r, "Red is assigned correctly");
    TEST_ASSERT_EQUAL_MESSAGE(0x22, color.g, "Green is assigned correctly");
    TEST_ASSERT_EQUAL_MESSAGE(0x33, color.b, "Blue is assigned correctly");
    TEST_ASSERT_EQUAL_MESSAGE(0xff, color.w, "White is assigned correctly");
}

void test_Color_RGBW_constructor_assigns_correct(void) {
    Color color(0x11, 0x22, 0x33, 0x44);
    TEST_ASSERT_EQUAL_MESSAGE(0x11, color.r, "Red is assigned correctly");
    TEST_ASSERT_EQUAL_MESSAGE(0x22, color.g, "Green is assigned correctly");
    TEST_ASSERT_EQUAL_MESSAGE(0x33, color.b, "Blue is assigned correctly");
    TEST_ASSERT_EQUAL_MESSAGE(0x44, color.w, "White is assigned correctly");
}

void test_ColorShift_one_step_conversion_is_steppingCorrect(void) {
    ColorShift sut(Color::OFF, Color::WHITE, 1);

    TEST_ASSERT_EQUAL_HEX32_MESSAGE(Color::OFF.color(), sut.next().color(), "First color is start");
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(Color::WHITE.color(), sut.next().color(), "Second color is end");
}

void test_ColorShift_two_step_conversion_is_correct(void) {
    Color start(0, 0, 0),
            step1(0x10, 0x10, 0x10),
            step2(0x20, 0x20, 0x20);
    ColorShift sut(start, step2, 2);

    TEST_ASSERT_EQUAL_HEX32_MESSAGE(start.color(), sut.next().color(), "First color is start");
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(step1.color(), sut.next().color(), "Second color is in between");
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(step2.color(), sut.next().color(), "Third color is end");
}

void test_ColorShift_counting_downwards_isCorrect(void) {
    Color start(0x20, 0x20, 0x20),
            step1(0x10, 0x10, 0x10),
            step2(0x0, 0x0, 0x0);
    ColorShift sut(start, step2, 2);

    TEST_ASSERT_EQUAL_HEX32_MESSAGE(start.color(), sut.next().color(), "First color is start");
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(step1.color(), sut.next().color(), "Second color is in between");
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(step2.color(), sut.next().color(), "Third color is end");
}

void test_ColorShift_many_step_conversion_is_correct(void) {
    Color start(0, 0, 0),
            step128(0x10, 0x10, 0x10),
            step256(0x20, 0x20, 0x20);
    ColorShift sut(start, step256, 255);

    TEST_ASSERT_EQUAL_HEX32_MESSAGE(start.color(), sut.next().color(), "First color is start");
    for (int i = 0; i < 127; i++) { sut.next(); };
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(step128.color(), sut.next().color(), "Second color is in between");
    for (int i = 0; i < 127; i++) { sut.next(); };
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(step256.color(), sut.next().color(), "Third color is end");
}

void test_ColorShift_many_step_downward_conversion_is_correct(void) {
    Color step256(0, 0, 0),
            step128(0x10, 0x10, 0x10),
            start(0x20, 0x20, 0x20);
    ColorShift sut(start, step256, 255);

    TEST_ASSERT_EQUAL_HEX32_MESSAGE(start.color(), sut.next().color(), "First color is start");
    for (int i = 0; i < 127; i++) { sut.next(); };
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(step128.color(), sut.next().color(), "Second color is in between");
    for (int i = 0; i < 127; i++) { sut.next(); };
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(step256.color(), sut.next().color(), "Third color is end");
}


void test_color_step__same_to_same__isCorrect(void) {
    TEST_ASSERT_EQUAL_MESSAGE(0, color_step(10, 10, 3), "Going from 10 to 10 has a delta of 0");
}

void test_color_step__oneStep__isCorrect(void) {
    TEST_ASSERT_EQUAL_MESSAGE(200, color_step(10, 210, 1), "Going from 200 to 210 in one step has a delta of 200");
}

void test_color_step__twoSteps__isCorrect(void) {
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x10, color_step(0, 0x20, 2),
                                   "Going from 0 to 0x20 in two steps has a delta of 0x10");
    TEST_ASSERT_EQUAL_MESSAGE(100, color_step(10, 210, 2), "Going from 200 to 210 in two steps has a delta of 100");
}


int main(int argc, const char *argv[]) {
    /** example
    Color from(0x0, 0x0, 0x0), to(0x08, 0x10, 0x20);
    const uint8_t steps = 0x10;
    ColorShift shift(from, to, steps);

    printf("%.8x --> %.8x\n", from.color(), to.color());

    for (uint8_t i = 0; i <= steps; i++) {
        printf("%.2i) %.8x\n", i, shift.next().color());
    }
     */

    UnityBegin(__FILE__);
    RUN_TEST(test_Color_convert_RGBW_To32Bit_isCorrect);
    RUN_TEST(test_Color_convert_RGB_To32Bit_isCorrect);
    RUN_TEST(test_Color_RGB_constructor_assigns_correct);
    RUN_TEST(test_Color_RGBW_constructor_assigns_correct);

    RUN_TEST(test_ColorShift_one_step_conversion_is_steppingCorrect);
    RUN_TEST(test_ColorShift_two_step_conversion_is_correct);
    RUN_TEST(test_ColorShift_counting_downwards_isCorrect);
    RUN_TEST(test_ColorShift_many_step_conversion_is_correct);
    RUN_TEST(test_ColorShift_many_step_downward_conversion_is_correct);

    RUN_TEST(test_color_step__same_to_same__isCorrect);
    RUN_TEST(test_color_step__oneStep__isCorrect);
    RUN_TEST(test_color_step__twoSteps__isCorrect);

    return (UnityEnd());
}
