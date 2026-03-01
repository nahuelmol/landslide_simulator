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

Finding the Jacobian matrix (sensitivity matrix) is crucial since it involves the ratio of variations in gravity per unit of density between source and observation points. There is where the equation provided by Plouff (Blakely 187) enters the scene, defining the mentioned relation in terms of source's dimensions considering fixed density per subsource (being a prism in that case).

#### Implementation of Talwani forward modeling

Polygon class and a Stack class are created. Each polygon will create its own G(z) value and eventually the \phi value asociated. The Stack to wich polygons are linked to will get polygon's phi values to construct the PHI matrix. This is the Jacobian matrix that relates gravity with density, needed for forward building and adjustment thorugh the least-square method.

A first aproximation is the case of a single observation point affected by the whole source.

<img width="482" height="76" alt="image" src="https://github.com/user-attachments/assets/48010189-ca3d-48f8-b3b5-ea304e14e56c" />

where:

<img width="353" height="45" alt="image" src="https://github.com/user-attachments/assets/30c2570e-5600-4a0f-abf1-43deef98eb5d" />

This can be rewritten leading to an asociated Jacobian matrix or sensitivity matrix that relates varitations in gravity with variations in density:

<img width="582" height="80" alt="image" src="https://github.com/user-attachments/assets/d95d60e7-5784-4352-8466-82708c3d907d" />


The Jacobian will get the shape of multidimensional matrix depending on the amount of observations and of number of polygons. However it's needed to work on the Green function first, and then expand it to the Jacobian. Redefining the same integral:

<img width="760" height="78" alt="image" src="https://github.com/user-attachments/assets/b8de6684-69a6-41a8-ba98-d1055439478a" />

where:

<img width="361" height="78" alt="image" src="https://github.com/user-attachments/assets/726f7de0-d133-4ec0-9733-3680607f91df" />

The Green function G(z') is obtained per polygon located at z'. And it's obtained by the superposition of the effect due to each side of that polygon. This way, all combined attraction compounds the effect produced by the polygon's boundary. The integral is then defined as follows (Blakely, Cambridge University Press 1996):

<img width="571" height="90" alt="image" src="https://github.com/user-attachments/assets/5cc46170-dab3-47e1-854e-d24d5d9cb34c" />

It's better to work over a linear integral, then the Green's theorem enter the scene. It makes sense to apply this since we are taking information from boundaries, which is what generates effects, following the Green's first identity.

<img width="530" height="92" alt="image" src="https://github.com/user-attachments/assets/f6f422c6-6f63-4617-b013-871c98d104ef" />



For simplicity, a parametrization is used where x' is defined as a function of the y'. This way, integration has to be done along one single axis.

<img width="288" height="87" alt="image" src="https://github.com/user-attachments/assets/4fee5c09-6cc8-4721-873f-329f689ff55f" />

where, both slope and bias are depends on corners, (m-esimo corner)

<img width="317" height="229" alt="image" src="https://github.com/user-attachments/assets/753f83e5-9924-4ad2-a881-15dc90cb34d6" />

Then, the integral is:

<img width="565" height="96" alt="image" src="https://github.com/user-attachments/assets/e192d184-8103-4109-8c71-1a2ea637e72b" />


This can be solved making some replacements as follows:

<img width="261" height="212" alt="image" src="https://github.com/user-attachments/assets/7f564c67-96d7-4c79-9fb9-45620ce49f94" />

Per side (m-side):

<img width="538" height="94" alt="image" src="https://github.com/user-attachments/assets/d4ba5391-72b6-4402-8fe8-4e61bc54d610" />

Then, the primitive is:

<img width="559" height="118" alt="image" src="https://github.com/user-attachments/assets/c5f3045e-6ea2-462e-9cb2-42d2c80d5caf" />

Finally, for the whole boundary, accumulating every side:

<img width="612" height="97" alt="image" src="https://github.com/user-attachments/assets/45df4962-7f58-4af7-860a-f5871b0e0206" />

This process must be repeated for each polygon. Finally, each observation will have n-polygons effects, n rows. Considering L observations, G will be a matrix of nxL dimensions. 

The last step is to build the Jacobian matrix from this G matrix, multiplying for \gamma and (z-z') and delta z'. The ideal case is to solve the integral going through the whole initial model. However, discrete polygons can be take into account.

#### Least Squares

The linear relation between observed data changes and parameters variation is represented as follows:

<img width="98" height="42" alt="image" src="https://github.com/user-attachments/assets/54e5a620-26d8-4a72-888b-d7b710f8d653" />

Where A has multiple meanings depending on the perspective. Phyisically, it's the sensitivity matrix. In calculis, it's the derivative of the observed data with repect to a source's parameter. In potential theory it is deeply related ot the Green's functions, thorughout U(x), the solution to the Poisson's differential equation.

This definition is used when the least square error algorithm is applied, defining the squared error first..

<img width="253" height="87" alt="image" src="https://github.com/user-attachments/assets/8eecb794-b8f0-4e9f-b12e-c5f8bb8747e1" />

and setting its derivative to zero.

<img width="450" height="135" alt="image" src="https://github.com/user-attachments/assets/ea3f2b37-303c-4ee8-b5a2-c95a87625c11" />

Considering c as a vector and B equal to the product of A with its transpose.

<img width="283" height="63" alt="image" src="https://github.com/user-attachments/assets/49dbbd83-5e8f-42a9-b8aa-a32258c1f412" />

B is simetric then..

<img width="161" height="42" alt="image" src="https://github.com/user-attachments/assets/82162811-5c46-4040-ae54-154aad23667f" />

Then the product is also simetric

<img width="297" height="140" alt="image" src="https://github.com/user-attachments/assets/1d345fbd-8516-48b3-8e2c-396cd457cb91" />

Finally,

<img width="410" height="96" alt="image" src="https://github.com/user-attachments/assets/b83f5754-036e-41ac-9c47-aa49dde71fe3" />

The product has invert and we get this

<img width="202" height="50" alt="image" src="https://github.com/user-attachments/assets/984ba314-bd00-41df-b1bc-b15e4c249d62" />

instead of using y and x, we can replace it with variations and control them to implement corrections per iteration.

<img width="238" height="62" alt="image" src="https://github.com/user-attachments/assets/66cc8439-2108-4442-b2d4-5915acd6b689" />

Corrections are aplied by adding displacments in x to the current set of x values.

<img width="184" height="44" alt="image" src="https://github.com/user-attachments/assets/f2dabd5f-5dfd-408c-93d1-c98177a25dcd" />

However, this application is not making any progress at all, because it is adding (or extracting if is negative) the same value to the set. I mean, it's the same displacement of the parameter corresponding to the same specific displacement in the observer data. Then it is just oscilating.

A weight must be used \alpha that controls the step (it could be consider a vector being that is represents direcction and magnitud of the correction), which will vary per iteration and allows an additional degree of freedom. Then,

<img width="209" height="59" alt="image" src="https://github.com/user-attachments/assets/5b207513-214a-4ef7-a6a2-a88bb3928241" />

This way the correction converges until it founds an step that produces an oscilation, that is the limit of the algorithm. Soon, regularizations will be implemented to control the stability of the process, conditioning A.

#### Adjustment

I have stated a 0.06 RMS_rel limit. Below that, the model starts oscilating. The following is a plot showing the output generated by each model along the adjustment process. As you can see, the produced by the model tends to be similar to the real data collected:

<img width="752" height="452" alt="image" src="https://github.com/user-attachments/assets/062473d7-10c3-4755-aa76-3282009fb376" />


#### Building

On windows, type the following command:

```
mingw32-make
```

It you have an older machine, run it using ansicon to activate ansi escapes code: 

```
ansicon dext
```

If you have any idea to help with this project or just want to contribute.. please let me know and let's start a conversation. Thanks for the reading!
