#include "encoder.h"
#include "velocity.h"
#include "zf_common_headfile.h"

static void pass_momentum_encoder(int32 frontValue,
                                  int32 backValue,
                                  struct Velocity_Motor* vel_motor) {
    vel_motor->momentumFront = -frontValue;  // TODO :fix bug
    vel_motor->momentumBack = -backValue;
    vel_motor->velocityDiff =
        vel_motor->momentumFront + vel_motor->momentumBack;
}

static void pass_bottom_encoder(int32 value, struct Velocity_Motor* vel_motor) {
    // filter the noise
    if (abs(value) < 5) {
        value = 0;
    } else {
        value > 0 ? (value -= 5) : (value += 5);
    }
    vel_motor->bottom = value;
    vel_motor->bottomSum += value;
}

void encoder_init() {
    // bottom encoder
    encoder_dir_init(ENCODER_BOTTOM, ENCODER_PIN0_BOTTOM, ENCODER_PIN1_BOTTOM);
    // momentum encoder
    encoder_dir_init(MOMENTUM_ENCODER_FRONT, ENCODER_PIN0_FRONT, ENCODER_PIN1_FRONT);
    encoder_dir_init(MOMENTUM_ENCODER_BACK, ENCODER_PIN0_BACK, ENCODER_PIN1_BACK);
}

void get_momentum_encoder(struct Velocity_Motor* vel_motor) {
    // static int32 frontEncoder[3] = {0, 0, 0};
    // static int32 backEncoder[3] = {0, 0, 0};
    // frontEncoder[2] = frontEncoder[1];
    // frontEncoder[1] = frontEncoder[0];
    // backEncoder[2] = backEncoder[1];
    // backEncoder[1] = backEncoder[0];
    int32 frontEncoderTemp = encoder_get_count(MOMENTUM_ENCODER_FRONT);
    int32 backEncoderTemp = encoder_get_count(MOMENTUM_ENCODER_BACK);
    encoder_clear_count(MOMENTUM_ENCODER_FRONT);
    encoder_clear_count(MOMENTUM_ENCODER_BACK);
    // lowPass filter
    pass_momentum_encoder(frontEncoderTemp, backEncoderTemp, vel_motor);
    // frontEncoder[0] = 
    // (int32)(0.879*(float)frontEncoderTemp + 0.121*(float)frontEncoder[1]);
    // backEncoder[0] =
    // (int32)(0.879*(float)backEncoderTemp + 0.121*(float)backEncoder[1]);
    // passMomentumEncoder(frontEncoder[0],backEncoder[0]);
}

void get_bottom_encoder(struct Velocity_Motor* vel_motor) {
    // static int32 bottomEncoder[3] = {0,0,0};
    // bottomEncoder[2] = bottomEncoder[1];
    // bottomEncoder[1] = bottomEncoder[0];
    int32 bottomEncoderTemp = encoder_get_count(ENCODER_BOTTOM);
    encoder_clear_count(ENCODER_BOTTOM);
    // lowPass filter
    pass_bottom_encoder(bottomEncoderTemp, vel_motor);
    // bottomEncoder[0] = 
    // (int32)(0.879*(float)bottomEncoderTemp + 0.121*(float)bottomEncoder[1]);
    // passBottomEncoder(bottomEncoder[0]);
}
