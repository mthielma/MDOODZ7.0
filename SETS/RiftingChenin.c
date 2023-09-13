#include "math.h"
#include "mdoodz.h"
#include "stdbool.h"
#include "stdlib.h"


double SetSurfaceZCoord(MdoodzInput *instance, double x_coord) {
  const double TopoLevel = -0.0e3 / instance->scaling.L;
  const double h_pert    = instance->model.user3 / instance->scaling.L;
  return TopoLevel + h_pert * (3330.0 - 2800.0) / 2800.0 * cos(2 * PI * x_coord / (instance->model.xmax - instance->model.xmin));
}

int SetPhase(MdoodzInput *instance, Coordinates coordinates) {
  Rectangle westernContinent = {
          .sizeZ   = 180e3,
          .sizeX   = 500e3,
          .centreZ = -90e3,
          .centreX = -350e3,
          .angle   = 0,
  };
  Rectangle easternContinent = {
          .sizeZ   = 140e3,
          .sizeX   = 500e3,
          .centreZ = -70e3,
          .centreX = 350e3,
          .angle   = 0,
  };
  Rectangle HOceanicPlate = {
          .sizeZ   = 60e3,
          .sizeX   = 200e3,
          .centreZ = -30e3,
          .centreX = 0e3,
          .angle   = 0,
  };


  // const double HOceanicPlate = 20e3 / instance->scaling.L;
  if (IsRectangleCoordinates(coordinates, westernContinent, instance->scaling.L)) {
    if (coordinates.z > -40e3 / instance->scaling.L) {
      return 1;}
    else {
      return 2;
    }
  } else if (IsRectangleCoordinates(coordinates, easternContinent, instance->scaling.L)) {
    if (coordinates.z > -30e3 / instance->scaling.L) {
      return 1;}
    else {
      return 2;
    }
  } else if (IsRectangleCoordinates(coordinates, HOceanicPlate, instance->scaling.L)) {
    if (coordinates.z > -20e3 / instance->scaling.L) {
      return 8;
    } else {
      return 2;
    }
  }
  return 6;
}

double SetTemperature(MdoodzInput *instance, Coordinates coordinates) {
  const double lithosphereThickness = instance->model.user1 / instance->scaling.L;
  const double surfaceTemperature   = 273.15 / instance->scaling.T;
  const double mantleTemperature    = (1330.0 + 273.15) / instance->scaling.T;
  const double particleTemperature  = ((mantleTemperature - surfaceTemperature) / lithosphereThickness) * (-coordinates.z) + surfaceTemperature;
  if (particleTemperature > mantleTemperature) {
    return mantleTemperature;
  } else {
    return particleTemperature;
  }
}

double SetGrainSize(MdoodzInput *instance, Coordinates coordinates, int phase) {
  const int asthenospherePhase = 3;
  return instance->materials.gs_ref[asthenospherePhase];
}

double SetHorizontalVelocity(MdoodzInput *instance, Coordinates coordinates) {
  return -coordinates.x * instance->model.bkg_strain_rate;
}

double SetVerticalVelocity(MdoodzInput *instance, Coordinates coordinates) {
  return coordinates.z * instance->model.bkg_strain_rate;
}

char SetBCPType(MdoodzInput *instance, POSITION position) {
  if (position == NE || position == NW) {
    return 0;
  } else {
    return -1;
  }
}

SetBC SetBCT(MdoodzInput *instance, POSITION position, double particleTemperature) {
  SetBC     bc;
  double surfaceTemperature = zeroC / instance->scaling.T;
  if (position == free_surface) {
    bc.value = surfaceTemperature;
    bc.type  = 1;
  } else {
    bc.value = 0.0;
    bc.type  = 0;
  }
  return bc;
}


SetBC SetBCTNew(MdoodzInput *instance, POSITION position, double particleTemperature) {
  SetBC     bc;
  double surfaceTemperature = zeroC / instance->scaling.T;
  double mantleTemperature  = (1330. + zeroC) / instance->scaling.T;
  if (position == S || position == SE || position == SW) {
    bc.value = particleTemperature;
    bc.type  = 1;
  } else if (position == N || position == NE || position == NW) {
    bc.value = mantleTemperature;
    bc.type  = 1;
  } else if (position == W || position == E) {
    bc.value = mantleTemperature;
    bc.type  = 0;
  } else {
    bc.value = 0;
    bc.type  = 0;
  }
  return bc;
}

SetBC SetBCVz(MdoodzInput *input, POSITION position, Coordinates coordinates) {
  SetBC bc;
  if (position == W || position == E || position == SW || position == SE || position == NW || position == NE) {
    bc.value = 0;
    bc.type  = 13;
  } else if (position == N) {
    bc.value = coordinates.z * input->model.bkg_strain_rate;
    bc.type  = 0;
  } else if (position == S) {
    bc.value = coordinates.z * input->model.bkg_strain_rate;
    bc.type  = 0;
  } else {
    bc.value = 0;
    bc.type  = -1;
  }
  return bc;
}

void AddCrazyConductivity(MdoodzInput *input) {
  int               *asthenospherePhases = (int *) malloc(sizeof(int));
  CrazyConductivity *crazyConductivity   = (CrazyConductivity *) malloc(sizeof(CrazyConductivity));
  asthenospherePhases[0]                 = 3;
  crazyConductivity->phases              = asthenospherePhases;
  crazyConductivity->nPhases             = 1;
  crazyConductivity->multiplier          = 1000;
  input->crazyConductivity               = crazyConductivity;
}

int main() {
  MdoodzSetup setup = {
          .BuildInitialTopography = &(BuildInitialTopography_ff){
                  .SetSurfaceZCoord = SetSurfaceZCoord,
          },
          .SetParticles = &(SetParticles_ff){
                  .SetPhase              = SetPhase,
                  .SetTemperature        = SetTemperature,
                  .SetGrainSize          = SetGrainSize,
                  .SetHorizontalVelocity = SetHorizontalVelocity,
                  .SetVerticalVelocity   = SetVerticalVelocity,
          },
          .SetBCs = &(SetBCs_ff){
                  .SetBCVx    = SetPureShearBCVx,
                  .SetBCVz    = SetBCVz,
                  .SetBCPType = SetBCPType,
                  .SetBCT     = SetBCT,
          },
          .MutateInput = AddCrazyConductivity,

  };
  RunMDOODZ("RiftingChenin.txt", &setup);
}