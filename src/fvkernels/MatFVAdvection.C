//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "MatFVAdvection.h"

registerADMooseObject("SquirrelApp", MatFVAdvection);

InputParameters
MatFVAdvection::validParams()
{
  InputParameters params = FVFluxKernel::validParams();
  params.addRequiredParam<RealVectorValue>("velocity", "Constant advection velocity");
  params.addParam<Real>("rho", 1.0, "density");
  params.addParam<Real>("cp", 1.0, "heat capacity");
  return params;
}

MatFVAdvection::MatFVAdvection(const InputParameters & params)
  : FVFluxKernel(params), _velocity(getParam<RealVectorValue>("velocity")),
    _rho(getParam<Real>("rho")),
    _cp(getParam<Real>("cp"))
{
}

ADReal
MatFVAdvection::computeQpResidual()
{
  ADReal u_interface;
  interpolate(InterpMethod::Upwind, u_interface, _u_elem[_qp], _u_neighbor[_qp], _velocity);
  return _rho * _cp * _normal * _velocity * u_interface;
}
