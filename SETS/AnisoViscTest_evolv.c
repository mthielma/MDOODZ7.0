#include "math.h"
#include "mdoodz.h"
#include "stdbool.h"
#include "stdlib.h"
#include "stdio.h"

int SetPhase(MdoodzInput *input, Coordinates coordinates) {
  const double radius = input->model.user1 / input->scaling.L;
  if (coordinates.x * coordinates.x + coordinates.z * coordinates.z < radius * radius) {
    return 1;
  } else {
    return 0;
  }
}

double SetDensity(MdoodzInput *input, Coordinates coordinates, int phase) {
  const double T_init = (zeroC) / input->scaling.T;
  if (1 == 0) {
    return input->materials.rho[phase] * (1 - input->materials.alp[phase] * (T_init - input->materials.T0[phase]));
  } else {
    return input->materials.rho[phase];
  }
}

Tensor2D SetDefGrad(MdoodzInput *input, Coordinates coordinates, int phase) {
  const double radius = input->model.user1 / input->scaling.L;
  if (coordinates.x * coordinates.x + coordinates.z * coordinates.z < radius * radius) {
    // nothing special in the inclusion
    return (Tensor2D) {.xx = 1., .xz = 0., .zx = 0., .zz = 1.,}; // initializes Fxx, Fxz, Fzx, Fzz 
  }
  else {
    // a bit more pure shear strain in the matrix
    return (Tensor2D) {.xx = 1.1, .xz = 0., .zx = 0., .zz = 0.9,}; // initializes Fxx, Fxz, Fzx, Fzz 
  }
}

double SetAnisoAngle(MdoodzInput *input, Coordinates coordinates, int phase, double predefined_angle) {
  const double radius = input->model.user1 / input->scaling.L;
  if (coordinates.x * coordinates.x + coordinates.z * coordinates.z < radius * radius) {
    // nothing special in the inclusion
    return 135.0;
  }
  else {
    // radial anisotropy in the matrix
    if (coordinates.x >= 0) {
      if (coordinates.z >= 0) {
        // x>0, y>0
        return atan(coordinates.z/coordinates.x) * 180.0 / M_PI;
        } else {
          // x>0, y<0
          return 270.0 + atan(coordinates.x/-coordinates.z) * 180.0 / M_PI;
        }
      }
      else {
            if (coordinates.z >= 0) {
              // x<0, y>0
              return 90.0 + atan(-coordinates.x/coordinates.z) * 180.0 / M_PI;
      } else {
        // x<0, y<0
        return 180.0 + atan(coordinates.z/coordinates.x) * 180.0 / M_PI;        
      }
    }
  }
}
  

int main(int nargs, char *args[]) {
  // Input file name
  char *input_file;
  if ( nargs < 2 ) {
    asprintf(&input_file, "AnisoViscTest_HomoRandomAngle.txt"); // Default
  }
  else {
    asprintf(&input_file, "%s", args[1]);     // Custom
  }
  printf("Running MDoodz7.0 using %s\n", input_file);
  MdoodzSetup setup = {
          .SetParticles  = &(SetParticles_ff){
                   .SetPhase              = SetPhase,
                   .SetDensity            = SetDensity,
                   .SetDefGrad            = SetDefGrad,
                   .SetAnisoAngle         = SetAnisoAngle,
          },
          .SetBCs = &(SetBCs_ff){
                  .SetBCVx = SetPureOrSimpleShearBCVx,
                  .SetBCVz = SetPureOrSimpleShearBCVz,
          },
  };
  RunMDOODZ(input_file, &setup);
  free(input_file);
}
