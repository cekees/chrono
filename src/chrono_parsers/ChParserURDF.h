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
// Parser utility class for URDF input files.
//
// =============================================================================

#ifndef CH_PARSER_URDF_H
#define CH_PARSER_URDF_H

#include "chrono_parsers/ChApiParsers.h"
#include "chrono/physics/ChBodyAuxRef.h"
#include "chrono/physics/ChSystem.h"

#include <urdf_parser/urdf_parser.h>

namespace chrono {
namespace parsers {

/// @addtogroup parsers_module
/// @{

/// URDF input file parser.
class ChApiParsers ChParserURDF {
  public:
    ChParserURDF() {}

    /// Parse the specified URDF input file and create the model in the given system.
    void Parse(ChSystem& sys,               ///< containing Chrono system
               const std::string& filename  ///< URDF input file name
    );

    /// Print body tree from parsed URDF file.
    void PrintModelTree();

  private:
    urdf::ModelInterfaceSharedPtr m_model;
};

/// @} parsers_module

}  // end namespace parsers
}  // end namespace chrono

#endif
