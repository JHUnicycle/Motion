#include "test.h"
#include "attitude.h"
#include "encoder.h"
#include "lcd.h"
#include "menu_input.h"
#include "motor.h"
#include "velocity.h"
#include "zf_common_headfile.h"

void test_bottom_motor() {
    lcd_clear();
    lcd_show_string(0, 0, "KEY_U: forward");
    lcd_show_string(0, 1, "KEY_D: backward");
    lcd_show_string(0, 4, "Press KEY_L to exit");
    while (keymsg.key != KEY_L) {
        if (keymsg.key == KEY_U)  // 向前
        {
            gpio_set_level(DIR_BOTTOM, 1);
            pwm_set_duty(MOTOR_BOTTOM, 1000);
        }
        if (keymsg.key == KEY_D)  // 向后
        {
            gpio_set_level(DIR_BOTTOM, 0);
            pwm_set_duty(MOTOR_BOTTOM, 1000);
        }
        lcd_show_int(0, 5, encoder_get_count(ENCODER_BOTTOM), 5);
    }
    pwm_set_duty(MOTOR_BOTTOM, 0);
    lcd_clear();
}

void test_side_motor() {
    lcd_clear();
    lcd_show_string(0, 0, "KEY_U: left  forward");
    lcd_show_string(0, 1, "KEY_D: left backward");
    lcd_show_string(0, 2, "KEY_B:right  forward");
    lcd_show_string(0, 3, "KEY_R:right backward");
    lcd_show_string(0, 4, "Press KEY_L to exit");
    while (keymsg.key != KEY_L) {
        if (keymsg.key == KEY_U)  // 向前
        {
            gpio_set_level(MOMENTUM_DIR_FRONT, 1);
            pwm_set_duty(MOMENTUM_MOTOR_FRONT, 1000);
        }
        if (keymsg.key == KEY_D)  // 向后
        {
            gpio_set_level(MOMENTUM_DIR_FRONT, 0);
            pwm_set_duty(MOMENTUM_MOTOR_FRONT, 1000);
        }
        if (keymsg.key == KEY_B)  // 向前
        {
            gpio_set_level(MOMENTUM_DIR_BACK, 1);
            pwm_set_duty(MOMENTUM_MOTOR_BACK, 1000);
        }
        if (keymsg.key == KEY_R)  // 向后
        {
            gpio_set_level(MOMENTUM_DIR_BACK, 0);
            pwm_set_duty(MOMENTUM_MOTOR_BACK, 1000);
        }
        lcd_show_string(0, 5, "FRONT:");
        lcd_show_int(8, 5, encoder_get_count(MOMENTUM_ENCODER_FRONT), 5);
        lcd_show_string(0, 6, "BACK:");
        lcd_show_int(8, 6, encoder_get_count(MOMENTUM_ENCODER_BACK), 5);
    }
    gpio_set_level(MOMENTUM_DIR_FRONT, 1);
    pwm_set_duty(MOMENTUM_MOTOR_FRONT, 0);
    gpio_set_level(MOMENTUM_DIR_BACK, 1);
    pwm_set_duty(MOMENTUM_MOTOR_BACK, 0);
    lcd_clear();
}

void test_attitude() {
    lcd_clear();
    while (keymsg.key != KEY_L) {
        lcd_show_string(0, 0, "Pitch:");
        lcd_show_float(0, 1, currentFrontAngle, 3, 3);
        lcd_show_string(0, 2, "Row:");
        lcd_show_float(0, 3, currentSideAngle, 3, 3);
        lcd_show_string(0, 4, "Yaw:");
        lcd_show_float(0, 5, yawAngle, 3, 3);
    }
    lcd_clear();
}

void test_imu() {
    lcd_clear();
    while (keymsg.key != KEY_L) {
        lcd_show_string(0, 0, "x:");
        lcd_show_float(0, 1, g_imu_data.gyro.x, 3, 3);
        lcd_show_float(8, 1, g_imu_data.acc.x, 3, 3);
        lcd_show_string(0, 2, "y:");
        lcd_show_float(0, 3, g_imu_data.gyro.y, 3, 3);
        lcd_show_float(8, 3, g_imu_data.acc.y, 3, 3);
        lcd_show_string(0, 4, "z:");
        lcd_show_float(0, 5, g_imu_data.gyro.z, 3, 3);
        lcd_show_float(8, 5, g_imu_data.acc.z, 3, 3);
    }
    lcd_clear();
}

void test_encoder() {
    lcd_clear();
    while (keymsg.key != KEY_L) {
        lcd_show_string(0, 0, "BOTTOM:");
        lcd_show_float(0, 1, encoder_get_count(ENCODER_BOTTOM), 3, 3);
        lcd_show_string(0, 2, "FRONT:");
        lcd_show_float(0, 3, encoder_get_count(MOMENTUM_ENCODER_FRONT), 3, 3);
        lcd_show_string(0, 4, "BACK:");
        lcd_show_float(0, 5, encoder_get_count(MOMENTUM_ENCODER_BACK), 3, 3);
    }
    lcd_clear();
}
