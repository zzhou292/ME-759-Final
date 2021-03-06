// =============================================================================
// PROJECT CHRONO - http://projectchrono.org
//
// Copyright (c) 2014 projectchrono.org
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
// Simplified powertrain model constructed with data from file (JSON format).
//
// =============================================================================

#ifndef SIMPLE_POWERTRAIN_H
#define SIMPLE_POWERTRAIN_H

#include "chrono_vehicle/ChApiVehicle.h"
#include "chrono_vehicle/powertrain/ChSimplePowertrain.h"

#include "chrono_thirdparty/rapidjson/document.h"

namespace chrono {
namespace vehicle {

/// @addtogroup vehicle_powertrain
/// @{

/// Simple powertrain subsystem (specified through JSON file).
class CH_VEHICLE_API SimplePowertrain : public ChSimplePowertrain {
  public:
    SimplePowertrain(const std::string& filename);
    SimplePowertrain(const rapidjson::Document& d);
    ~SimplePowertrain() {}

    virtual void SetGearRatios(std::vector<double>& fwd, double& rev) override;
    virtual double GetMaxTorque() const override { return m_max_torque; }
    virtual double GetMaxSpeed() const override { return m_max_speed; }

  private:
    virtual void Create(const rapidjson::Document& d) override;

    double m_fwd_gear_ratio;  // forward gear ratio (single gear transmission)
    double m_rev_gear_ratio;  // reverse gear ratio
    double m_max_torque;      // maximum motor torque
    double m_max_speed;       // maximum motor speed
};

/// @} vehicle_powertrain

}  // end namespace vehicle
}  // end namespace chrono

#endif
