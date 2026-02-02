/*
 * @file smv_speedometer.h
 * @brief Provides functionality to drive a 4-digit multiplexed 7-segment display
 *
 * Create an instance of struct using pseudo constructor function and
 * call function pointers to update and scan the display
 */

#ifndef _SMV_SPEEDOMETER_H
#define _SMV_SPEEDOMETER_H

#include <stdint.h>
#include "stm32f4xx_hal.h"


/* Number of digits on display */
#define SMV_NUM_DIGITS 4

/* Decimal point location (0-based index) */
#define SMV_DECIMAL_DIGIT 1

/*
 * @brief container to hold current values and settings for speedometer instance
 */
typedef struct SMV_Speedometer SMV_Speedometer;
struct SMV_Speedometer {

    /* ===== Data ===== */
    uint16_t value;                  /* value to display (0–9999) */
    uint8_t  digits[SMV_NUM_DIGITS]; /* broken-out digits */
    uint8_t  current_digit;          /* active multiplex index */

    /* ===== Function pointers ===== */
    void (*setValue)(SMV_Speedometer*, uint16_t);
    void (*scan)(SMV_Speedometer*);
    void (*init)(SMV_Speedometer*);
};

/* ================= API ================= */

/**
 * @brief Constructor for speedometer instance
 * @return SMV_Speedometer struct with function pointers initialized
 */
SMV_Speedometer SMV_Speedometer_new(void);

#endif /* _SMV_SPEEDOMETER_H */
