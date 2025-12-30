/* test_dut.c: Implementation of a testable component.

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <limits.h>
#include "unity.h"
#include <ui.h>


TEST_CASE("PASS", "[bit_manipulation]")
{
    TEST_ASSERT_EQUAL(0, 0);
}

TEST_CASE("Fail", "[bit_manipulation]")
{
    TEST_ASSERT_EQUAL(5, 1);
}