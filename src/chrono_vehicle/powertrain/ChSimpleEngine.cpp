// =============================================================================
// PROJECT CHRONO - http://projectchrono.org
//
// Copyright (c) 2023 projectchrono.org
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be found
// in the LICENSE file at the top level of the distribution and at
// http://projectchrono.org/license-chrono.txt.
//
// =============================================================================
// Authors: Radu Serban
// =============================================================================
//
// Simple engine model template
//
// =============================================================================

#include "chrono_vehicle/powertrain/ChSimpleEngine.h"

namespace chrono {
namespace vehicle {

ChSimpleEngine::ChSimpleEngine(const std::string& name)
    : ChEngine(name), m_motor_speed(0), m_motor_torque(0), m_critical_speed(1e4) {}

void ChSimpleEngine::Initialize(std::shared_ptr<ChChassis> chassis) {
    ChEngine::Initialize(chassis);

    m_critical_speed = GetMaxPower() / GetMaxTorque();
}

void ChSimpleEngine::Synchronize(double time, const DriverInputs& driver_inputs, double shaft_speed) {
    m_motor_speed = shaft_speed;

    // The torque depends on a hyperbolic speed-torque curve of the motor
    // like in DC motors or combustion engines with CVT gearbox.
    if (m_motor_speed <= m_critical_speed) {
        m_motor_torque = GetMaxTorque();
    } else {
        m_motor_torque = GetMaxPower() / m_motor_speed;
    }

    // Limit the speed range
    if (m_motor_speed >= GetMaxSpeed()) {
        m_motor_torque = 0.0;
    }

    // Motor torque is linearly modulated by throttle gas value:
    m_motor_torque *= driver_inputs.m_throttle;

    // Apply the motor torque on the motorshaft
    m_motorshaft->SetAppliedTorque(m_motor_torque);
}

}  // end namespace vehicle
}  // end namespace chrono
