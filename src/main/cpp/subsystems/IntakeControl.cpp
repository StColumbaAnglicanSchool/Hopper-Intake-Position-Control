// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/IntakeControl.h"
#include <frc2/command/CommandPtr.h>
#include <frc2/command/FunctionalCommand.h>
#include <iostream>

using namespace ctre::phoenix6;

IntakeControl::IntakeControl()
{
    ctre::phoenix6::configs::TalonFXConfiguration turretConfig{};

    // Populate the turretConfig object
    turretConfig.MotorOutput.Inverted =
        signals::InvertedValue::Clockwise_Positive;

    turretConfig.Feedback.SensorToMechanismRatio = 9;

    turretConfig.MotionMagic.MotionMagicCruiseVelocity = 100_tps;
    turretConfig.MotionMagic.MotionMagicAcceleration = 50_tr_per_s_sq;
    turretConfig.MotionMagic.MotionMagicJerk = 500_tr_per_s_cu;

    turretConfig.Slot0.kS = 0.1;
    turretConfig.Slot0.kV = 0.12;
    turretConfig.Slot0.kA = 0.01;
    turretConfig.Slot0.kP = 30.0;
    turretConfig.Slot0.kI = 0;
    turretConfig.Slot0.kD = 0;

    turretConfig.Voltage.PeakForwardVoltage = 8_V;
    turretConfig.Voltage.PeakReverseVoltage = -8_V;

    // Create a StatusCode Object so we can collect Error information
    // if applying the config object fails
    ctre::phoenix::StatusCode status =
        ctre::phoenix::StatusCode::StatusCodeNotInitialized;

    // Try to apply the turret motor config object up to 5 times.
    for (int i = 0; i < 5; ++i)
    {
        status = m_IntakePosMotor.GetConfigurator().Apply(turretConfig);
        if (status.IsOK())
            break;
    }
    if (!status.IsOK())
    {
        std::cout << "Could not apply intake_position config, error code: "
                  << status.GetName() << std::endl;
    }
};

// This method will be called once per scheduler run
void IntakeControl::Periodic()
{
}

void IntakeControl::SetIntakePosition(units::angle::turn_t Angle)
{
    m_IntakePosMotor.SetControl(m_motionMagicControl.WithPosition(Angle).WithSlot(0));
}

frc2::CommandPtr IntakeControl::SetIntakeSpeed(units::turns_per_second_t speed) {
    m_IntakeMotor.SetControl(m_velocityVoltage.WithVelocity(speed).WithSlot(0));
}