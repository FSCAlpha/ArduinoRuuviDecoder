#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int __tests_run = 0;
static int __tests_failed = 0;

#define ASSERT_TRUE(expr) do { \
    if(!expr) { \
        printf("❌ ASSERT_TRUE failed: %s (line %d)\n", #expr, __LINE__); \
        __tests_failed++; \
    } \
} while(0)

#define ASSERT_FALSE(expr) do { \
    if(expr) { \
        printf("❌ ASSERT_FALSE failed: %s (line %d)\n", #expr, __LINE__); \
        __tests_failed++; \
    } \
} while(0)

#define TEST(name) void name()

#define RUN_TEST(name) do { \
    printf("▶ Running %s...\n", #name); \
    int before_failures = __tests_failed; \
    name(); \
    __tests_run++; \
    if (__tests_failed == before_failures) { \
        printf("✅ %s passed!\n\n", #name); \
    } else { \
        printf("❌ %s failed!\n\n", #name); \
    } \
} while(0)

#define TEST_SUMMARY() do { \
    printf("===== TEST SUMMARY =====\n"); \
    printf("Total: %d | Passed: %d | Failed: %d\n", \
        __tests_run, __tests_run - __tests_failed, __tests_failed); \
    printf("========================\n"); \
    if (__tests_failed > 0) exit(1); \
} while(0)

#define FLOAT_NEAR(a, b, tol) (fabsf((a) - (b)) <= (tol))

#define ASSERT_RUUVI_DATA_EQ(actual, expected, tol) do { \
    int failed = 0; \
    const ruuvi_data_t *_a = &(actual); \
    const ruuvi_data_t *_b = &(expected); \
    if (_a->format != _b->format) { \
        printf("  ❌ format: %u != %u\n", _a->format, _b->format); failed = 1; } \
    if (!FLOAT_NEAR(_a->temperature, _b->temperature, tol)) { \
        printf("  ❌ temperature: %.3f != %.3f\n", _a->temperature, _b->temperature); failed = 1; } \
    if (!FLOAT_NEAR(_a->humidity, _b->humidity, tol)) { \
        printf("  ❌ humidity: %.3f != %.3f\n", _a->humidity, _b->humidity); failed = 1; } \
    if (_a->pressure != _b->pressure) { \
        printf("  ❌ pressure: %u != %u\n", _a->pressure, _b->pressure); failed = 1; } \
    if (!FLOAT_NEAR(_a->accel_x, _b->accel_x, tol)) { \
        printf("  ❌ accel_x: %.3f != %.3f\n", _a->accel_x, _b->accel_x); failed = 1; } \
    if (!FLOAT_NEAR(_a->accel_y, _b->accel_y, tol)) { \
        printf("  ❌ accel_y: %.3f != %.3f\n", _a->accel_y, _b->accel_y); failed = 1; } \
    if (!FLOAT_NEAR(_a->accel_z, _b->accel_z, tol)) { \
        printf("  ❌ accel_z: %.3f != %.3f\n", _a->accel_z, _b->accel_z); failed = 1; } \
    if (_a->battery_voltage != _b->battery_voltage) { \
        printf("  ❌ battery_voltage: %u != %u\n", _a->battery_voltage, _b->battery_voltage); failed = 1; } \
    if (_a->tx_power != _b->tx_power) { \
        printf("  ❌ tx_power: %d != %d\n", _a->tx_power, _b->tx_power); failed = 1; } \
    if (_a->movement_counter != _b->movement_counter) { \
        printf("  ❌ movement_counter: %u != %u\n", _a->movement_counter, _b->movement_counter); failed = 1; } \
    if (_a->measurement_sequence != _b->measurement_sequence) { \
        printf("  ❌ measurement_sequence: %u != %u\n", _a->measurement_sequence, _b->measurement_sequence); failed = 1; } \
    if (memcmp(_a->mac, _b->mac, 6) != 0) { \
        printf("  ❌ mac mismatch:\n    expected: %02X:%02X:%02X:%02X:%02X:%02X\n" \
               "    actual:   %02X:%02X:%02X:%02X:%02X:%02X\n", \
               _b->mac[0], _b->mac[1], _b->mac[2], _b->mac[3], _b->mac[4], _b->mac[5], \
               _a->mac[0], _a->mac[1], _a->mac[2], _a->mac[3], _a->mac[4], _a->mac[5]); \
        failed = 1; } \
    if (_a->valid != _b->valid) { \
        printf("  ❌ valid: %d != %d\n", _a->valid, _b->valid); failed = 1; } \
    if (failed) __tests_failed++; \
} while(0)

#endif // TEST_H