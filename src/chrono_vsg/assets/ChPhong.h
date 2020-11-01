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
// Authors: Rainer Gericke
// =============================================================================

#ifndef CH_PHONG_H
#define CH_PHONG_H

#include "chrono/assets/ChAsset.h"
#include "chrono_vsg/core/ChApiVSG.h"
#include "chrono_vsg/resources/ChVSGPhongMaterial.h"

namespace chrono {
namespace vsg3d {

/// Base class for assets that define basic textures. Assets can be attached to ChBody objects.
/// Different post processing modules can handle textures in proper ways (ex for ray tracing, or
/// openGL visualization), or may also create specialized classes of textures with more properties.
class CH_VSG_API ChPhong : public ChAsset {
  protected:
    vsg::vec3 ambientColor;
    vsg::vec3 diffuseColor;
    vsg::vec3 specularColor;
    float shininess;

  public:
    ChPhong();
    ChPhong(ChVSGPhongMaterial& material);
    vsg::vec3 GetAmbientColor() { return ambientColor; }
    vsg::vec3 GetDiffuseColor() { return diffuseColor; }
    vsg::vec3 GetSpecularColor() { return specularColor; }
    float GetShininess() { return shininess; }
    virtual ~ChPhong() {}

    /// Method to allow serialization of transient data to archives.
    virtual void ArchiveOUT(ChArchiveOut& marchive) override;

    /// Method to allow de-serialization of transient data from archives.
    virtual void ArchiveIN(ChArchiveIn& marchive) override;
};

}  // namespace vsg3d
CH_CLASS_VERSION(vsg3d::ChPhong, 0)
}  // end namespace chrono

#endif
