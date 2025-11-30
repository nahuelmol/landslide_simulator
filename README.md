<div>
  <img src="https://img.shields.io/github/last-commit/nahuelmol/landslide_simulator"/>
  <img src="https://img.shields.io/github/languages/code-size/nahuelmol/landslide_simulator"/>
  <img src="https://img.shields.io/github/languages/top/nahuelmol/landslide_simulator"/>
  <img src="https://img.shields.io/github/languages/count/nahuelmol/landslide_simulator"/>
</div>

### Goals

The main obective are: 
* to practice gravity anomalies modeling 

### Gravity anomalies

The goal is to put in practice the forward method at modeling gravity anomalies. Then, iterative methods are considered for adjusting the model, like least-squares. For this reason Eigen library is used to make calculations with matrix.

Finding the Jacobian matrix (sensitivity matrix) is crucial since it involves the ratio of the variations in gravity per unit of change in density between source and observation points. There is where the equation provided by Plouff (Blakely 187) enter the scene and relates defining the mentioned relation in terms of source's dimensions considering fixed density per subsource (being a prism in that case).

#### Implementation of Talwani forward modeling

A polygon class and a Stack class are created. Each polygon will create its own G(z) value and eventually the \phi value asociated. The Stack to wich polygons are linked to will get polygon's phi values to construct the PHI matrix. This is the Jacobian matrix that relates gravity with density, needed for forward and adjustment by applying least-squares.

A first aproximation is the case of a single observation point located at the origin of the coordinate system. This simplifies the formulas that calculate the mentioned parameters. This points has an asociated Jacobian matrix, of a single column, indeed it's a vector with a size of the amount of polygons that compounds the Stack.

When multiple observation are considered, the Jacobian will get the shape of multidimensional matrix with more than one column depending on the amount of observations.

G(z) are obtained by the superposition of the effects that each side of the polygon has on the origin. Each attraction is combined to form a single one as if the effect is produced by the polygon's boundary. The integral is then defined as follows (Blakely, Cambridge University Press 1996):

<img width="827" height="119" alt="image" src="https://github.com/user-attachments/assets/a6617bc8-75cc-4e49-9f4c-090ae8eebad4" />

For simplicity, x prime is defined in function of the y'. This way, integration has to be done along one single axis, and are introduced two more constants per side, the slope of the segment and its bias.

<img width="177" height="43" alt="image" src="https://github.com/user-attachments/assets/ffa20ef3-9ccf-4496-a46c-e3f602cea606" />

where:

<img width="317" height="229" alt="image" src="https://github.com/user-attachments/assets/753f83e5-9924-4ad2-a881-15dc90cb34d6" />

The follwing is to replace these definitions into G(z') and to calculate the function's primitive.

