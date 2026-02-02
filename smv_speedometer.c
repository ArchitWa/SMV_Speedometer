/*
 * @file smv_speedometer.c
 * @brief Implementation for 4-digit multiplexed 7-segment speedometer
 */

#include "smv_speedometer.h"
#include "smv_speedometer_board.h"

/* ===== Lookup table ===== */
static const uint8_t segment_lut[10] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F  // 9
};


static void SMV_disableAllDigits(void)
{
    D1_OFF;
    D2_OFF;
    D3_OFF;
    D4_OFF;
}

static void SMV_setSegments(uint8_t seg)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, (seg & (1 << 0)) ? GPIO_PIN_SET : GPIO_PIN_RESET); // A
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, (seg & (1 << 1)) ? GPIO_PIN_SET : GPIO_PIN_RESET); // B
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, (seg & (1 << 2)) ? GPIO_PIN_SET : GPIO_PIN_RESET); // C
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, (seg & (1 << 3)) ? GPIO_PIN_SET : GPIO_PIN_RESET); // D
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, (seg & (1 << 4)) ? GPIO_PIN_SET : GPIO_PIN_RESET); // E
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, (seg & (1 << 5)) ? GPIO_PIN_SET : GPIO_PIN_RESET); // F
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, (seg & (1 << 6)) ? GPIO_PIN_SET : GPIO_PIN_RESET); // G
}

/**
 * @brief Helper method to split a number into n-digit array
 * @param value number to be split
 * @param *out digit array
 */
static void SMV_splitDigits(uint16_t value, uint8_t *out)
{
    if (value > 9999) value = 9999;

    out[0] = value / 1000;
    out[1] = (value / 100) % 10;
    out[2] = (value / 10)  % 10;
    out[3] = value % 10;
}


static void SMV_setValue(SMV_Speedometer *self, uint16_t value)
{
    self->value = value;
    SMV_splitDigits(value, self->digits);
}

/**
 * @brief Sets the corresponding pins to high/low depending on number
 */
static void SMV_scan(SMV_Speedometer *self)
{
    /* Turn everything off first (avoid ghosting) */
    SMV_disableAllDigits();
    DP_OFF;

    /* Load segment data */
    uint8_t digit_value = self->digits[self->current_digit];
    SMV_setSegments(segment_lut[digit_value]);

    /* Enable decimal point if this is the decimal digit */
    if (self->current_digit == SMV_DECIMAL_DIGIT) {
        DP_ON;
    }

    /* Enable correct digit */
    switch (self->current_digit) {
        case 0: D1_ON; break;
        case 1: D2_ON; break;
        case 2: D3_ON; break;
        case 3: D4_ON; break;
        default: break;
    }

    /* Advance to next digit */
    self->current_digit++;
    if (self->current_digit >= SMV_NUM_DIGITS) {
        self->current_digit = 0;
    }
}

static void SMV_init(SMV_Speedometer *self)
{
    self->value = 0;
    self->current_digit = 0;
    SMV_splitDigits(0, self->digits);

    SMV_disableAllDigits();
    DP_OFF;
}

/* ===== Constructor ===== */

SMV_Speedometer SMV_Speedometer_new(void)
{
    SMV_Speedometer smv;

    smv.value = 0;
    smv.current_digit = 0;

    smv.setValue = SMV_setValue;
    smv.scan     = SMV_scan;
    smv.init     = SMV_init;

    SMV_splitDigits(0, smv.digits);

    return smv;
}
