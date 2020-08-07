//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "MatFVConstantScalarOutflowBC.h"

registerMooseObject("SquirrelApp", MatFVConstantScalarOutflowBC);

InputParameters
MatFVConstantScalarOutflowBC::validParams()
{
  InputParameters params = FVFluxBC::validParams();
  params.addRequiredParam<RealVectorValue>("velocity", "Constant advection velocity");
  params.addParam<Real>("rho", 1.0, "density");
  params.addParam<Real>("cp", 1.0, "heat capacity");
  return params;
}

MatFVConstantScalarOutflowBC::MatFVConstantScalarOutflowBC(const InputParameters & parameters)
  : FVFluxBC(parameters), _velocity(getParam<RealVectorValue>("velocity")),
    _rho(getParam<Real>("rho")),
    _cp(getParam<Real>("cp"))
{
}

ADReal
MatFVConstantScalarOutflowBC::computeQpResidual()
{
  return _rho * _cp * _normal * _velocity * _u[_qp];
}
