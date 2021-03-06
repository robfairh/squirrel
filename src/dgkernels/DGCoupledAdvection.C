#include "DGCoupledAdvection.h"

registerMooseObject("SquirrelApp", DGCoupledAdvection);

template <>
InputParameters
validParams<DGCoupledAdvection>()
{
  InputParameters params = validParams<DGKernel>();
  params.addRequiredCoupledVar("uvel", "x direction velocity");
  params.addCoupledVar("vvel", 0, "y direction velocity");
  params.addCoupledVar("wvel", 0, "z direction velocity");
  params.addClassDescription("DG upwinding for convection on Navier-Stokes velocity variables");
  return params;
}

DGCoupledAdvection::DGCoupledAdvection(const InputParameters & parameters)
  : DGKernel(parameters),
    // velocity variables
    _vel_x(coupledValue("uvel")),
    _vel_y(coupledValue("vvel")),
    _vel_z(coupledValue("wvel")),
    // gradients for the jacobian
    _grad_x_vel(coupledGradient("uvel")),
    _grad_y_vel(coupledGradient("vvel")),
    _grad_z_vel(coupledGradient("wvel")),
    // variable enumeration
    _x_vel_var_number(coupled("uvel")),
    _y_vel_var_number(coupled("vvel")),
    _z_vel_var_number(coupled("wvel"))
{
}

Real
DGCoupledAdvection::computeQpResidual(Moose::DGResidualType type)
{
  Real r = 0;

  Real vdotn = _vel_x[_qp] * _normals[_qp](0) + _vel_y[_qp] * _normals[_qp](1) +
               _vel_z[_qp] * _normals[_qp](2);
  switch (type)
  {
    case Moose::Element:
      if (vdotn >= 0)
        r += vdotn * _u[_qp] * _test[_i][_qp];
      else
        r += vdotn * _u_neighbor[_qp] * _test[_i][_qp];
      break;

    case Moose::Neighbor:
      if (vdotn >= 0)
        r -= vdotn * _u[_qp] * _test_neighbor[_i][_qp];
      else
        r -= vdotn * _u_neighbor[_qp] * _test_neighbor[_i][_qp];
      break;
  }

  return r;
}

Real
DGCoupledAdvection::computeQpJacobian(Moose::DGJacobianType type)
{
  Real r = 0;

  Real vdotn = _vel_x[_qp] * _normals[_qp](0) + _vel_y[_qp] * _normals[_qp](1) +
               _vel_z[_qp] * _normals[_qp](2);

  switch (type)
  {
    case Moose::ElementElement:
      if (vdotn >= 0)
        r += vdotn * _phi[_j][_qp] * _test[_i][_qp];
      break;

    case Moose::ElementNeighbor:
      if (vdotn < 0)
        r += vdotn * _phi_neighbor[_j][_qp] * _test[_i][_qp];
      break;

    case Moose::NeighborElement:
      if (vdotn >= 0)
        r -= vdotn * _phi[_j][_qp] * _test_neighbor[_i][_qp];
      break;

    case Moose::NeighborNeighbor:
      if (vdotn < 0)
        r -= vdotn * _phi_neighbor[_j][_qp] * _test_neighbor[_i][_qp];
      break;
  }

  return r;
}

Real
DGCoupledAdvection::computeOffDiagJacobianHelper(Moose::DGJacobianType type,
                                                 const Real & normal_comp)
{
  Real r = 0;
  Real vdotn = _vel_x[_qp] * _normals[_qp](0) + _vel_y[_qp] * _normals[_qp](1) +
               _vel_z[_qp] * _normals[_qp](2);

  switch (type)
  {
    case Moose::ElementElement:
      if (vdotn >= 0)
        r += _phi[_j][_qp] * normal_comp * _u[_qp] * _test[_i][_qp];
      else
        r += _phi[_j][_qp] * normal_comp * _u_neighbor[_qp] * _test[_i][_qp];
      break;

    case Moose::NeighborElement:
      if (vdotn >= 0)
        r -= _phi[_j][_qp] * normal_comp * _u[_qp] * _test_neighbor[_i][_qp];
      else
        r -= _phi[_j][_qp] * normal_comp * _u_neighbor[_qp] * _test_neighbor[_i][_qp];
      break;

    case Moose::ElementNeighbor:
      if (vdotn >= 0)
        r += _phi_neighbor[_j][_qp] * normal_comp * _u[_qp] * _test[_i][_qp];
      else
        r += _phi_neighbor[_j][_qp] * normal_comp * _u_neighbor[_qp] * _test[_i][_qp];
      break;

    case Moose::NeighborNeighbor:
      if (vdotn >= 0)
        r -= _phi_neighbor[_j][_qp] * normal_comp * _u[_qp] * _test_neighbor[_i][_qp];
      else
        r -= _phi_neighbor[_j][_qp] * normal_comp * _u_neighbor[_qp] * _test_neighbor[_i][_qp];
      break;
  }

  return r;
}

Real
DGCoupledAdvection::computeQpOffDiagJacobian(Moose::DGJacobianType type, unsigned jvar)
{
  Real r = 0;

  if (jvar == _x_vel_var_number)
    r += computeOffDiagJacobianHelper(type, _normals[_qp](0));
  else if (jvar == _y_vel_var_number)
    r += computeOffDiagJacobianHelper(type, _normals[_qp](1));
  else if (jvar == _z_vel_var_number)
    r += computeOffDiagJacobianHelper(type, _normals[_qp](2));

  return r;
}
