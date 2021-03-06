#ifndef DGFUNCTIONCONVECTION_H
#define DGFUNCTIONCONVECTION_H

#include "DGKernel.h"

class DGFunctionConvection;

template <>
InputParameters validParams<DGFunctionConvection>();

class DGFunctionConvection : public DGKernel
{
public:
  DGFunctionConvection(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual(Moose::DGResidualType type);
  virtual Real computeQpJacobian(Moose::DGJacobianType type);

  RealVectorValue _velocity;

  const Function & _vel_x_func;
  const Function & _vel_y_func;
  const Function & _vel_z_func;
};

#endif // DGFUNCTIONCONVECTION_H
