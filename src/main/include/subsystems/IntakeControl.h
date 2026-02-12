// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc2/command/CommandPtr.h>
#include <ctre/phoenix6/TalonFX.hpp>
#include <ctre/phoenix6/controls/PositionVoltage.hpp>
#include <ctre/phoenix6/controls/MotionMagicVoltage.hpp>
#include <ctre/phoenix6/controls/VelocityVoltage.hpp>
#include <frc2/command/CommandPtr.h>

using namespace ctre::phoenix6;

class IntakeControl : public frc2::SubsystemBase {
 public:
  IntakeControl();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

  void SetIntakePosition(units::angle::turn_t Angle);
  
  frc2::CommandPtr SetIntakeSpeed(units::turns_per_second_t speed);

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.

  ctre::phoenix6::hardware::TalonFX m_IntakePosMotor{2};  
  ctre::phoenix6::hardware::TalonFX m_IntakeMotor{3};

  ctre::phoenix6::controls::PositionVoltage m_positionVoltage{0_tr};
  controls::MotionMagicVoltage m_motionMagicControl{0_tr};

  ctre::phoenix6::controls::VelocityVoltage m_velocityVoltage{0_tps};
};