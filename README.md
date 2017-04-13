# social_analyser

Depends on https://github.com/openframeworks/openFrameworks
and Eigen3 https://github.com/naokiring/ofxMatrixEigen

The code can be use without openFrameworks (remove draw function, include Eigen3 lib)


This program represent a Population of Agents represented by their position X,Y and rotation Theta and compute the personnal social space of each agents and detect group formation and their respective o-space (the formation's social space) based on a Gaussian mixture representation (proposed by J. Gomez et al.). The result is then stored in a 2D grid map representing the social cost of the world.

New social space representation can be implemented by extending PersonnalSocialSpace and GroupSocialSpace class. 

ON WORK: The program aim to connect with ROS to send navigation command to a robot for social proactive engagement of groups.