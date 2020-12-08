// =============================================================================
// PROJECT CHRONO - http://projectchrono.org
//
// Copyright (c) 2020 projectchrono.org
// All right reserved.
//
// Use of this source code is governed by a BSD-style license that can be found
// in the LICENSE file at the top level of the distribution and at
// http://projectchrono.org/license-chrono.txt.
//
// =============================================================================
// Authors: Radu Serban
// =============================================================================
//
// Definition of the rigid TERRAIN NODE (using Chrono::Parallel).
//
// The global reference frame has Z up, X towards the front of the vehicle, and
// Y pointing to the left.
//
// =============================================================================

#ifndef CH_VEHCOSIM__TERRAINNODE_RIGID_H
#define CH_VEHCOSIM__TERRAINNODE_RIGID_H

#include "chrono_parallel/physics/ChSystemParallel.h"

#include "chrono_vehicle/cosim/ChVehicleCosimTerrainNode.h"

namespace chrono {
namespace vehicle {

class CH_VEHICLE_API ChVehicleCosimTerrainNodeRigid : public ChVehicleCosimTerrainNode {
  public:
    /// Create a rigid terrain subsystem.
    ChVehicleCosimTerrainNodeRigid(ChContactMethod method,  ///< contact method (penalty or complementatiry)
                                   bool render              ///< use run-time visualization
    );
    ~ChVehicleCosimTerrainNodeRigid();

    virtual ChSystem* GetSystem() override { return m_system; }

    /// Set the material properties for terrain.
    /// The type of material must be consistent with the contact method (penalty or complementarity)
    /// specified at construction. These parameters characterize the material for the container and
    /// (if applicable) the granular material.  Tire contact material is received from the rig node.
    void SetMaterialSurface(const std::shared_ptr<ChMaterialSurface>& mat);

    /// Specify whether contact coefficients are based on material properties (default: true).
    /// Note that this setting is only relevant when using the penalty method.
    void UseMaterialProperties(bool flag);

    /// Set the normal contact force model (default: Hertz)
    /// Note that this setting is only relevant when using the penalty method.
    void SetContactForceModel(ChSystemSMC::ContactForceModel model);

  private:
    ChSystemParallel* m_system;  ///< containing system

    virtual bool SupportsFlexibleTire() const override { return true; }

    virtual void Construct() override;

    virtual void CreateMeshProxies() override;
    virtual void UpdateMeshProxies() override;
    virtual void GetForcesMeshProxies() override;
    virtual void PrintMeshProxiesUpdateData() override;
    virtual void PrintMeshProxiesContactData() override;

    virtual void CreateWheelProxy() override;
    virtual void UpdateWheelProxy() override;
    virtual void GetForceWheelProxy() override;
    virtual void PrintWheelProxyUpdateData() override;
    virtual void PrintWheelProxyContactData() override;

    virtual void OutputTerrainData(int frame) override;
    virtual void OnSynchronize(int step_number, double time) override;
    virtual void OnAdvance(double step_size) override;
};

}  // end namespace vehicle
}  // end namespace chrono

#endif
