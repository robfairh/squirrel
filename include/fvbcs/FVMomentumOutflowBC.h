//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "FVFluxBC.h"

class FVMomentumOutflowBC : public FVFluxBC
{
public:
  static InputParameters validParams();
  FVMomentumOutflowBC(const InputParameters & params);

protected:
  virtual ADReal computeQpResidual() override;

  const ADMaterialProperty<RealVectorValue> & _vel;

  /// The advected quantity
  const MooseArray<ADReal> * const _adv_quant;

  const ADMaterialProperty<Real> & _p;
  const Real _coef;
};
