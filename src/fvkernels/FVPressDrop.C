//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "FVPressDrop.h"

registerADMooseObject("SquirrelApp", FVPressDrop);

InputParameters
FVPressDrop::validParams()
{
  InputParameters params = FVElementalKernel::validParams();
  params.addClassDescription("Pressure drop due to friction");
  params.addRequiredCoupledVar("rho", "Density in the friction term");
  params.addParam<Real>("coef", 1.0, "Coefficent multiplier for frictional term: C1.");
  return params;
}

FVPressDrop::FVPressDrop(const InputParameters & parameters)
  : FVElementalKernel(parameters),
    _rho(adCoupledValue("rho")),
    _coef(getParam<Real>("coef"))
{
}

ADReal
FVPressDrop::computeQpResidual()
{
  return _coef * _rho[_qp] * _u[_qp] *_u[_qp];
}
