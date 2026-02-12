// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <RobotContainer.h>
#include <frc/shuffleboard/Shuffleboard.h>
#include <frc2/command/button/JoystickButton.h>
#include <frc2/command/button/Trigger.h>
#include <frc2/command/WaitCommand.h>
#include <frc2/command/PrintCommand.h>

#include <frc2/command/RunCommand.h>

RobotContainer::RobotContainer() {
  // Initialize all of your commands and subsystems here
  // Log Shuffleboard events for command initialize, execute, finish, interrupt
  frc2::CommandScheduler::GetInstance().OnCommandInitialize(
      [](const frc2::Command& command) {
        frc::Shuffleboard::AddEventMarker(
            "Command initialized", command.GetName(),
            frc::ShuffleboardEventImportance::kNormal);
      });
  frc2::CommandScheduler::GetInstance().OnCommandExecute(
      [](const frc2::Command& command) {
        frc::Shuffleboard::AddEventMarker(
            "Command executed", command.GetName(),
            frc::ShuffleboardEventImportance::kNormal);
      });
  frc2::CommandScheduler::GetInstance().OnCommandFinish(
      [](const frc2::Command& command) {
        frc::Shuffleboard::AddEventMarker(
            "Command finished", command.GetName(),
            frc::ShuffleboardEventImportance::kNormal);
      });
  frc2::CommandScheduler::GetInstance().OnCommandInterrupt(
      [](const frc2::Command& command) {
        frc::Shuffleboard::AddEventMarker(
            "Command interrupted", command.GetName(),
            frc::ShuffleboardEventImportance::kNormal);
      });


  // Configure the button bindings
  ConfigureBindings();
}

frc2::CommandPtr RobotContainer::GetAutonomousCommand() {
  return frc2::PrintCommand("Auto").ToPtr();
}

void RobotContainer::ConfigureBindings() {
  // Configure your trigger bindings here
  frc2::JoystickButton(&m_driverController, 7).WhileTrue(m_intakeSS.SetIntakeSpeed(30_tps));
  
  m_intakeSS.SetDefaultCommand(
    frc2::RunCommand(
      [this] {
        double throttle = m_driverController.GetThrottle();
        double scaled = ((throttle+1)/2)*(1.2);
        m_intakeSS.SetIntakePosition(scaled*1_tr);
      }, {&m_intakeSS}
    )
  );
}