//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "Material.h"

class ADEulerMaterial : public Material
{
public:
  static InputParameters validParams();

  ADEulerMaterial(const InputParameters & parameters);

protected:
  virtual void computeQpProperties() override;

  const ADVariableValue & _rho;
  const ADVariableValue & _vel_x;
  const ADVariableValue * const _vel_y;
  const ADVariableValue * const _vel_z;
  const ADVariableValue & _temp;
  const Real _rgas;

  ADMaterialProperty<RealVectorValue> & _velocity;
  ADMaterialProperty<Real> & _rho_u;
  ADMaterialProperty<Real> & _rho_v;
  ADMaterialProperty<Real> & _rho_w;
  ADMaterialProperty<Real> & _rho_T;
  ADMaterialProperty<Real> & _pressure;
};
