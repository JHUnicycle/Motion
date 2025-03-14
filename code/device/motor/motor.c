#include "motor.h"

uint32 bottom_motor_deadzone = 0;

void motor_init() {
    gpio_init(P22_3, GPO, 1, GPO_PUSH_PULL);
    gpio_set_level(P22_3, 1);

    pwm_init(MOTOR_BOTTOM, MOTOR_HZ, 0);
    gpio_init(DIR_BOTTOM, GPO, 1, GPO_PUSH_PULL);

    // momentum motor
    // front momentum motor
    pwm_init(MOMENTUM_MOTOR_FRONT, MOMENTUM_HZ, MOMENTUM_MOTOR_PWM_MAX);
    gpio_init(MOMENTUM_DIR_FRONT, GPO, 1, GPO_PUSH_PULL);
    gpio_init(MOMENTUM_STOP_FRONT, GPO, 1, GPO_PUSH_PULL);
    // back momentum motor
    pwm_init(MOMENTUM_MOTOR_BACK, MOMENTUM_HZ, MOMENTUM_MOTOR_PWM_MAX);
    gpio_init(MOMENTUM_DIR_BACK, GPO, 1, GPO_PUSH_PULL);
    gpio_init(MOMENTUM_STOP_BACK, GPO, 1, GPO_PUSH_PULL);
}

// bottom motor
void set_bottom_motor_pwn(int32 pwm) {
    restrictValueI(&pwm, MOTOR_PWM_MIN, MOTOR_PWM_MAX);
    if (pwm >= 0) {
        gpio_set_level(DIR_BOTTOM, 0);
        pwm_set_duty(MOTOR_BOTTOM, pwm);
    } else {
        gpio_set_level(DIR_BOTTOM, 1);
        pwm_set_duty(MOTOR_BOTTOM, -pwm);
    }
}

void set_bottom_motor_hertz(int32 hertz) {
    restrictValueI(&hertz, MOTOR_HZ + MOTOR_HZ_RANGE,
                   MOTOR_HZ - MOTOR_HZ_RANGE);
    pwm_init(MOTOR_BOTTOM, hertz, 0);
}

void stop_bottom_motor(void) {
    set_bottom_motor_pwn(0);
}

// momentum motor
void set_momentum_motor_pwm(int32 pwmFront, int32 pwmBack) {
    restrictValueI(&pwmFront, MOMENTUM_MOTOR_PWM_MIN, MOMENTUM_MOTOR_PWM_MAX);
    restrictValueI(&pwmBack, MOMENTUM_MOTOR_PWM_MIN, MOMENTUM_MOTOR_PWM_MAX);
    if (pwmFront >= 0)
    {
        gpio_set_level(MOMENTUM_DIR_FRONT, 1);
        pwm_set_duty(MOMENTUM_MOTOR_FRONT, MOMENTUM_MOTOR_PWM_MAX - pwmFront);
    }
    else
    {
        gpio_set_level(MOMENTUM_DIR_FRONT, 0);
        pwm_set_duty(MOMENTUM_MOTOR_FRONT, MOMENTUM_MOTOR_PWM_MAX + pwmFront);
    }
    if (pwmBack >= 0)
    {
        gpio_set_level(MOMENTUM_DIR_BACK, 1);
        pwm_set_duty(MOMENTUM_MOTOR_BACK, MOMENTUM_MOTOR_PWM_MAX - pwmBack);
    }
    else
    {
        gpio_set_level(MOMENTUM_DIR_BACK, 0);
        pwm_set_duty(MOMENTUM_MOTOR_BACK, MOMENTUM_MOTOR_PWM_MAX + pwmBack);
    }
}

void stop_momentum_motor(void) {
    set_momentum_motor_pwm(0, 0);
    gpio_set_level(MOMENTUM_STOP_FRONT, 0);
    gpio_set_level(MOMENTUM_STOP_BACK, 0);
}