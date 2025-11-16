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

I must simulate the flow of a landslide, being as it acts as a fluid due to earthquake-induced liquefaction, and precipitation floods that is retained by the talud which has a that capacity (characteristic of the piroclastic filled area). 

The first approach will be the finite element, discretizing the body of the unstable part of the talud as little pieces where each one moves following motion equations.

And important step is to map the site where the talud fails and above that, represent the motion of that fluid (failed talud). It could be done with simple maps from above.

Other complext aproach for modeling fluids will be considered.

### Gravity anomalies

An additional goal is to put in practice the forward method at modeling gravity anomalies. Then, iterative methods are considered for adjusting the model, like least-squares. For this reason Eigen library is used to make calculations with matrix.

Finding the Jacobian matrix is crucial since it is aware of the variations in gravity per unit of change in density between prisms and observation points. There is where the equation provided by Plouff (Blakely 187) enter the scene and relates defining the mentioned relation in terms of source's dimensions considering fixed density per subsource (being a prism in that case).


