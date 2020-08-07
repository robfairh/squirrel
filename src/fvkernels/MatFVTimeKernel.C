//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "MatFVTimeKernel.h"

#include "SystemBase.h"

registerADMooseObject("SquirrelApp", MatFVTimeKernel);

InputParameters
MatFVTimeKernel::validParams()
{
  InputParameters params = FVElementalKernel::validParams();
  params.set<MultiMooseEnum>("vector_tags") = "time";
  params.set<MultiMooseEnum>("matrix_tags") = "system time";
  params.addParam<Real>("rho", 1.0, "density");
  params.addParam<Real>("cp", 1.0, "heat capacity");
  return params;
}

MatFVTimeKernel::MatFVTimeKernel(const InputParameters & parameters)
  : FVElementalKernel(parameters), _u_dot(_var.adUDot()),
    _rho(getParam<Real>("rho")),
    _cp(getParam<Real>("cp"))
{
}

ADReal
MatFVTimeKernel::computeQpResidual()
{
  return _rho * _cp * _u_dot[_qp];
}
