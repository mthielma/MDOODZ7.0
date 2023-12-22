#include "math.h"
#include "mdoodz.h"
#include "stdbool.h"
#include "stdlib.h"
#include "stdio.h"

double Line(const double x, Vector2D p1, Vector2D p2) {
  const double a   = (p2.z - p1.z) / (p2.x - p1.x);
  const double b   = p2.z - a*p2.x;
  const double z  = a*x +b;
  return z;
}

double SetSurfaceZCoord(MdoodzInput *instance, double x) {
  double h = 0.0;
  const double Earth_radius = 6370e3/instance->scaling.L;
  if (instance->model.polar==0) {
    // Flat topo 
    h     = Earth_radius;
  } 
  if (instance->model.polar==1) {
    // Curved topography (see PolarCoordinatesStuff.py)
    h     =  sqrt((Earth_radius - x)*(Earth_radius + x));
  }                   
  return h;
}

int SetPhase(MdoodzInput *m, Coordinates coordinates) {
  int phase = 0; // Default: crust
  const double x = coordinates.x, z = coordinates.z;
  const double Earth_radius = 6370e3/m->scaling.L;
  const double zMoho = Earth_radius + m->model.user0/m->scaling.L;
  const double basin_width1 = 200e3/m->scaling.L;
  const double basin_width2 = 500e3/m->scaling.L;
  const double cont_width   = 250e3/m->scaling.L;
  const double x1 = -200e3/m->scaling.L; // OCT #1 
  const double x2 =  x1 + basin_width1;         // OCT #2 
  const double x3 =  x2 + cont_width;           // OCT #3 
  const double x4 =  x3 + basin_width2;         // OCT #4 
  // const double z_ocean_moho = Earth_radius - 7.5e3/m->scaling.L;
  const double Lm = 50.e3/m->scaling.L;                     //  margin length
  const double z_lab_eur  = Earth_radius - 180e3/m->scaling.L;
  const double z_lab_bas  = Earth_radius - 180e3/m->scaling.L;
  const double z_lab_adr  = Earth_radius - 180e3/m->scaling.L;//Earth_radius + m->model.user1/m->scaling.L;
  const double z_moho_eur = zMoho;
  const double z_moho_bas = Earth_radius - 7.5e3/m->scaling.L;
  const double z_moho_adr = zMoho;
  // ASTHENOSPHERE
  if  (z < z_lab_bas) phase = 2;
  // Add lithospheric mantle
  Vector2D p1, p2, p3, p4; // points to draw segments
  double z_lab, z_moho; // vertical position of interface (function of x)
  // EUROPE
  if ( z>z_lab_eur && z<z_moho_eur && x<x1 - Lm/2.0) phase = 1; // europe
  // MARGIN 1
  // OCT 1 --- LAB
  p1.x = x1 - Lm/2.0; p1.z = z_lab_eur;
  p2.x = x1 + Lm/2.0; p2.z = z_lab_bas;
  z_lab = Line(x, p1, p2);
  // OCT 1 --- Moho
  p3.x = x1 - Lm/2.0; p3.z = z_moho_eur;
  p4.x = x1 + Lm/2.0; p4.z = z_moho_bas;
  z_moho = Line(x, p3, p4);
  // Draw polygon
  if ( fabs(x-x1)<Lm/2.0 && z>z_lab && z<z_moho) phase = 1; // margin
  // BASIN
  if ( z>z_lab_bas && z<z_moho_bas && x<x2 - Lm/2.0 && x>x1 + Lm/2.0) phase = 1; // mantle
  if ( z>z_moho_bas && x<x2 - Lm/2.0 && x>x1 + Lm/2.0) phase = 3; // crust
  // MARGIN 2
  // OCT 1 --- LAB
  p1.x = x2 - Lm/2.0; p1.z = z_lab_bas;
  p2.x = x2 + Lm/2.0; p2.z = z_lab_eur;
  z_lab = Line(x, p1, p2);
  // OCT 1 --- Moho
  p3.x = x2 - Lm/2.0; p3.z = z_moho_bas;
  p4.x = x2 + Lm/2.0; p4.z = z_moho_eur;
  z_moho = Line(x, p3, p4);
  // Draw polygon
  if ( fabs(x-x2)<Lm/2.0 && z>z_lab && z<z_moho) phase = 1; // margin
  // MICROCONTINENT
  if ( z>z_lab_eur && z<z_moho_eur && x<x3 - Lm/2.0 && x>x2 + Lm/2.0) phase = 1; // mantle
  if ( x<x3 + Lm/2.0 && x>x2 - Lm/2.0 && phase == 0) phase = 6;
  // MARGIN 3
  // OCT 1 --- LAB
  p1.x = x3 - Lm/2.0; p1.z = z_lab_eur;
  p2.x = x3 + Lm/2.0; p2.z = z_lab_bas;
  z_lab = Line(x, p1, p2);
  // OCT 1 --- Moho
  p3.x = x3 - Lm/2.0; p3.z = z_moho_eur;
  p4.x = x3 + Lm/2.0; p4.z = z_moho_bas;
  z_moho = Line(x, p3, p4);
  // Draw polygon
  if ( fabs(x-x3)<Lm/2.0 && z>z_lab && z<z_moho) phase = 1; // margin
  // BASIN
  if ( z>z_lab_bas && z<z_moho_bas && x<x4 - Lm/2.0 && x>x3 + Lm/2.0) phase = 1; // mantle
  if ( z>z_moho_bas && x<x4 - Lm/2.0 && x>x3 + Lm/2.0) phase = 3; // crust
  // MARGIN 4
  // OCT 1 --- LAB
  p1.x = x4 - Lm/2.0; p1.z = z_lab_bas;
  p2.x = x4 + Lm/2.0; p2.z = z_lab_adr;
  z_lab = Line(x, p1, p2);
  // OCT 1 --- Moho
  p3.x = x4 - Lm/2.0; p3.z = z_moho_bas;
  p4.x = x4 + Lm/2.0; p4.z = z_moho_adr;
  z_moho = Line(x, p3, p4);
  // Draw polygon
  if ( fabs(x-x4)<Lm/2.0 && z>z_lab && z<z_moho) phase = 1; // margin
  // Adria
  if ( z>z_lab_adr && z<z_moho_adr && x>x4 + Lm/2.0) phase = 1; // mantle

  // ----------------- WEAK ZONES
  const double angle = -35.*M_PI/180;
  const double a_ell = 10.0*m->model.user5/m->scaling.L, b_ell = 0.6*m->model.user5/m->scaling.L;
  double x_ell, z_ell, X, Z;
  // Draw ellipse
  double smaller_fact = 1.0;
  Z = Earth_radius - 55e3/m->scaling.L;
  X = x2 - 0.05*smaller_fact*sqrt(a_ell*a_ell + b_ell*b_ell);
  x_ell = (x-X)*cos(angle) + (z-Z)*sin(angle);
  z_ell =-(x-X)*sin(angle) + (z-Z)*cos(angle);
  if (pow(x_ell/(smaller_fact*a_ell),2.0) + pow(z_ell/(smaller_fact*b_ell),2.0) < 1.0) phase = 5;

  // Draw ellipse
  Z = Earth_radius - 55e3/m->scaling.L;
  X = x4 + 0.05*sqrt(a_ell*a_ell + b_ell*b_ell);
  x_ell = (x-X)*cos(angle) + (z-Z)*sin(angle);
  z_ell =-(x-X)*sin(angle) + (z-Z)*cos(angle);
  if (pow(x_ell/a_ell,2.0) + pow(z_ell/b_ell,2.0) < 1.0) phase = 4;
  
  return phase;
}

double SetTemperature(MdoodzInput *instance, Coordinates coordinates) {
  const double x = coordinates.x, z = coordinates.z;
  const double Lz = (double) (instance->model.zmax - instance->model.zmin) ;
  const double Earth_radius = 6370e3/instance->scaling.L;
  const double Ttop  = 293.0/(instance->scaling.T);
  const double Tbot  = (instance->model.user3 + zeroC)/instance->scaling.T;
  double Tgrad = (Ttop-Tbot)/ (Lz - (instance->model.zmax-Earth_radius));
  return Ttop + Tgrad*(z - Earth_radius);
}

// double SetGrainSize(MdoodzInput *instance, Coordinates coordinates, int phase) {
//   const int asthenospherePhase = 3;
//   return instance->materials.gs_ref[asthenospherePhase];
// }

// double SetHorizontalVelocity(MdoodzInput *instance, Coordinates coordinates) {
//   return -coordinates.x * instance->model.bkg_strain_rate;
// }

// double SetVerticalVelocity(MdoodzInput *instance, Coordinates coordinates) {
//   return coordinates.z * instance->model.bkg_strain_rate;
// }

char SetBCPType(MdoodzInput *instance, POSITION position) {
  if (position == NE || position == NW) {
    return 0;
  } else {
    return -1;
  }
}

SetBC SetBCT(MdoodzInput *instance, POSITION position, double particleTemperature) {
  SetBC     bc;
  double surface_temperature =                   (20. + zeroC) / instance->scaling.T;
  double mantle_temperature  = (instance->model.user3 + zeroC) / instance->scaling.T;
  if (position == S) {
    bc.type  = constant_temperature;
    bc.value = mantle_temperature;
  }
  if (position == free_surface || position == N) {
    bc.type  = constant_temperature;
    bc.value = surface_temperature;
  } 
  if (position == W || position == E) {
    bc.type  = constant_heatflux;
    bc.value = 0.;
  }
  return bc;
}

void AddCrazyConductivity(MdoodzInput *input) {
  int               *asthenospherePhases = (int *) malloc(sizeof(int));
  CrazyConductivity *crazyConductivity   = (CrazyConductivity *) malloc(sizeof(CrazyConductivity));
  asthenospherePhases[0]                 = 2;
  crazyConductivity->phases              = asthenospherePhases;
  crazyConductivity->nPhases             = 1;
  crazyConductivity->multiplier          = 1000;
  input->crazyConductivity               = crazyConductivity;
}

double BoundaryVelocityProfile(double V, double z, double z_LAB, double dz_smooth) {
  return -0.5*V*erfc( (z-z_LAB)/dz_smooth ) + V;
}

double BoundaryVelocityProfilePrimitive(double V, double z, double z_LAB, double dz_smooth) {
  return V*(z - 0.5*(z-z_LAB) * erfc( (z-z_LAB)/dz_smooth ) );
}

SetBC SetBCVx(MdoodzInput *instance, POSITION position, Coordinates coordinates) {
  SetBC bc;
  const double Earth_radius = 6370e3/instance->scaling.L, dz_smooth = 10e3/instance->scaling.L;
  const double Lx = instance->model.xmax - instance->model.xmin;
  double V_tot    =  Lx * instance->model.bkg_strain_rate; // |VxW| + |VxE|
  double maxAngle = asin(Lx/2/Earth_radius);     // Aperture angle
  double tet_W, alp_W, tet_E, alp_E;
  double VxW, VxE;
  double z_LAB, z_top;
  const double x = coordinates.x, z = coordinates.z;

  // Compute surface height and LAB position
  if (instance->model.polar == 1) {
    z_top = sqrt((Earth_radius - x)*(Earth_radius + x));
    z_LAB = z_top + instance->model.user1/instance->scaling.L;
  }
  else {
    z_top = Earth_radius;
    z_LAB = z_top + instance->model.user1/instance->scaling.L;
  }

  // Evaluate velocity of W and E boundaries
  if (instance->model.polar == 1) {
        const double tet_W  = -maxAngle;
        const double alp_W  = M_PI/2.0 - tet_W;
        VxW = (0.5*V_tot) * sin(alp_W) ;

        const double tet_E  = maxAngle;
        const double alp_E  = M_PI/2.0 - tet_E;
        VxE =-(0.5*V_tot) * sin(alp_E);
  }
  else {
    VxW =  0.5*V_tot;
    VxE = -0.5*V_tot;
  }

  // Apply smooth transition with depth
  VxW = BoundaryVelocityProfile(VxW, z, z_LAB, dz_smooth);
  VxE = BoundaryVelocityProfile(VxE, z, z_LAB, dz_smooth);

  // Assign BC values
  if (position == N || position == S || position == NW || position == SW || position == NE || position == SE) {
    bc.value = 0;
    bc.type  = 13;
  } else if (position == W) {
    bc.value = VxW;
    bc.type  = 0;
  } else if (position == E) {
    bc.value = VxE;
    bc.type  = 0;
  } else {
    bc.value = 0.0;
    bc.type  = -1;
  }
  return bc;
}

SetBC SetBCVz(MdoodzInput *instance, POSITION position, Coordinates coordinates) {
  SetBC bc;
  const double Earth_radius = 6370e3/instance->scaling.L, dz_smooth = 10e3/instance->scaling.L;
  const double Lx = instance->model.xmax - instance->model.xmin;
  double V_tot    =  Lx * instance->model.bkg_strain_rate; // |VxW| + |VxE|
  double maxAngle = asin(Lx/2/Earth_radius);     // Aperture angle
  double tet_W, alp_W, tet_E, alp_E;
  double VxW, VxE, VzW, VzE, VzS=0.0;
  double z_LAB, z_top;
  const double x = coordinates.x, z = coordinates.z;  

  // Compute surface height and LAB position
  if (instance->model.polar == 1) {
    z_top = sqrt((Earth_radius - x)*(Earth_radius + x));
    z_LAB = z_top + instance->model.user1/instance->scaling.L;
  }
  else {
    z_top = Earth_radius;
    z_LAB = z_top + instance->model.user1/instance->scaling.L;
  }

  // Evaluate velocity of W and E boundaries
  if (instance->model.polar == 1) {
        const double tet_W  = -maxAngle;
        const double alp_W  = M_PI/2.0 - tet_W;
        VxW = (0.5*V_tot) * sin(alp_W) ;
        VzW = (0.5*V_tot) * cos(alp_W) ;

        const double tet_E  = maxAngle;
        const double alp_E  = M_PI/2.0 - tet_E;
        VxE =-(0.5*V_tot) * sin(alp_W) ;
        VzE =-(0.5*V_tot) * cos(alp_E);
  }
  else {
    VxW =  0.5*V_tot;
    VxE = -0.5*V_tot;
    VzW =  0.0;
    VzE = -0.0;
  }

  // // Compute compensating VzS value
  const double z_min       = instance->model.zmin; 
  const double prim_W_zmax = BoundaryVelocityProfilePrimitive(VxW, z_top, z_LAB, dz_smooth);
  const double prim_W_zmin = BoundaryVelocityProfilePrimitive(VxW, z_min, z_LAB, dz_smooth);
  const double prim_E_zmax = BoundaryVelocityProfilePrimitive(VxE, z_top, z_LAB, dz_smooth);
  const double prim_E_zmin = BoundaryVelocityProfilePrimitive(VxE, z_min, z_LAB, dz_smooth);
  const double intW = prim_W_zmax - prim_W_zmin;
  const double intE = prim_E_zmax - prim_E_zmin;
  VzS = - ( fabs(intW) + fabs(intE) ) / Lx;

  // Apply smooth transition with depth
  VzW = -BoundaryVelocityProfile(VzW, z, z_LAB, dz_smooth);
  VzE = -BoundaryVelocityProfile(VzE, z, z_LAB, dz_smooth);

  // printf("Vx %2.2e %2.2e %2.2e\n",   0*instance->scaling.V, VxW*instance->scaling.V, VxE*instance->scaling.V);
  // printf("Vz %2.2e %2.2e %2.2e\n", VzS*instance->scaling.V, VzW*instance->scaling.V, VzE*instance->scaling.V);

  if (position == W || position == SW || position == NW ) {
    bc.value = 0*VzW;
    bc.type  = 13;
  } else if ( position == E || position == SE || position == NE) {
    bc.value = 0*VzE;
    bc.type  = 13;
  } else if (position == S || position == N) {
    bc.value = VzS;
    bc.type  = 0;
  } else {
    bc.value = 0;
    bc.type  = -1;
  }
  return bc;
}


int main(int nargs, char *args[]) {
  // Input file name
  char *input_file;
  if ( nargs < 2 ) {
    asprintf(&input_file, "DoubleSubduction.txt"); // Default
  }
  else {
    asprintf(&input_file, "%s", args[1]);     // Custom
  }
  printf("Running MDoodz7.0 using %s\n", input_file);
  MdoodzSetup setup = {
          .BuildInitialTopography = &(BuildInitialTopography_ff){
                  .SetSurfaceZCoord = SetSurfaceZCoord,
          },
          .SetParticles = &(SetParticles_ff){
                  .SetPhase              = SetPhase,
                  .SetTemperature        = SetTemperature,
          },
          .SetBCs = &(SetBCs_ff){
                  .SetBCVx    = SetBCVx,
                  .SetBCVz    = SetBCVz,
                  .SetBCPType = SetBCPType,
                  .SetBCT     = SetBCT,
          },
          .MutateInput = AddCrazyConductivity,

  };
  RunMDOODZ(input_file, &setup);
  free(input_file);
}
