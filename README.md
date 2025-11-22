<div>
  <img src="https://img.shields.io/github/last-commit/nahuelmol/landslide_simulator"/>
  <img src="https://img.shields.io/github/languages/code-size/nahuelmol/landslide_simulator"/>
  <img src="https://img.shields.io/github/languages/top/nahuelmol/landslide_simulator"/>
  <img src="https://img.shields.io/github/languages/count/nahuelmol/landslide_simulator"/>
</div>

### Goals

The main obective are: 
* to develop fluid simulator as aproximation to landslide motion
* to practice gravity anomalies modeling 

### Landslides

I must simulate the flow of a landslide, being as it acts as a fluid due to earthquake-induced liquefaction, and precipitation floods that is retained by the talud which has that capacity (characteristic of the piroclastic filled area). 

There are different approaches for implementing the simulation, from two viewpoints specifically; the Eulerian and the Lagrangian. Both follow the Navier Stokes equation of motions but differ on the perspectives.

#### Eulerian viewpoint
This is a mesh-based method that assigns motion properties to the particles depending on their spatial location. The velocity field changes varies in time at an specific point.

#### Lagrangian viewpoint

This is the choseen approach. A mesh-free method which follows the behavior of each particle and consider how its properties varies along the way. Studying earquake produced landslides, there's a crucial properties that varies in time, the G module. At applying frequencies, the behavior of the soil changes from elastic to viscoelastic and finally, if the frequency is the fundamental, to plastic transforming into a fluid. The G comes to the limit, the resistance is broken and the soil faouls, particles are colapsed, porous pressure evolves along this evolution raching its peak.

The SPH (Smoothed Particle Hydrodinamics) is the method to be implemented.
Mohr-Coulomb constitutive model is also considered to represent deformation-stress relation and the rupture point.

Kernel functions will be explored for choosing the best option.
*  Cubic-Spline-Kernel is the first option.

### Gravity anomalies

An additional goal is to put in practice the forward method at modeling gravity anomalies. Then, iterative methods are considered for adjusting the model, like least-squares. For this reason Eigen library is used to make calculations with matrix.

Finding the Jacobian matrix is crucial since it is aware of the variations in gravity per unit of change in density between prisms and observation points. There is where the equation provided by Plouff (Blakely 187) enter the scene and relates defining the mentioned relation in terms of source's dimensions considering fixed density per subsource (being a prism in that case).

#### Implementation of Talwani forward modeling

A polygon class and a Stack class are created. Each polygon will create its own G(z) value and eventually the \phi value asociated. The Stack to wich polygons are linked to will get polygon's phi values to construct the PHI matrix. This is the Jacobian matrix that relates gravity with density, needed for forward and adjustment by applying least-squares.

A first aproximation is the case of a single observation point located at the origin of the coordinate system. This simplifies the formulas that calculate the mentioned parameters. This points has an asociated Jacobian matrix, of a single column, indeed it's a vector with a size of the amount of polygons that compounds the Stack.

When multiple observation are considered, the Jacobian will get the shape of multidimensional matrix with more than one column depending on the amount of observations.

G(z) are obtained by the superposition of the effects that each side has on the origin. Each attraction is comnined to form a single one as if the effect is produced by the polygon's boundary.




