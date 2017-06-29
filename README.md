# social_analyser

Depends Eigen3 https://github.com/naokiring/ofxMatrixEigen
and OpenFrameworks (Optionnal) https://github.com/openframeworks/openFrameworks for visualisation.

The code can be use without openFrameworks (disable USE_OFX in config or remove draw function, and include Eigen3 lib)

Documentation available in doc/html/index.html or doc/latex/refman.pdf

This program represent a Population of Agents represented by their position X,Y and rotation Theta and compute the personnal social space of each agents and detect group formation and their respective o-space (the formation's social space) based on a Gaussian mixture representation (proposed by J. Gomez et al.). The result is then stored in a 2D grid map representing the social cost of the world.

New social space representation can be implemented by extending PersonnalSocialSpace and GroupSocialSpace class.
