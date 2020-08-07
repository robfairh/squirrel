//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "FVFluxKernel.h"

class MatFVAdvection : public FVFluxKernel
{
public:
  static InputParameters validParams();
  MatFVAdvection(const InputParameters & params);

protected:
  virtual ADReal computeQpResidual() override;

  ADRealVectorValue _velocity;
  const Real & _rho;
  const Real & _cp;
};
