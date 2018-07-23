# Penguin Slide - 3D graphics project

This project is distributed under a Creative Commons Attribution Share Alike 
license. See the LICENSE file for more information.

Original framework:
    © 2017 P.L. Manteaux, T. Delame and M. Chabanas
Project penguin slide:
    © 2017 T. Laviron, R. Clément and S. Vançon

==================
Build instructions
==================
Make sure the external libs are built:
    $ cd extlib/ && make && cd ..

Create a build directory (in the root folder, for example)
    $ mkdir build && cd build

Generate the makefile, then build the project
    $ cmake ..
    $ make


===================
Running the program
===================

Launch the generated executable:
    $ ./main

Once launched, you should see the penguing on the starting line. Click and
drag with the right mouse button to turn the camera around.
When you are ready, press Enter to launch the penguin down the slope.
Use the arrow keys to steer and avoid the obstacles to reach the penguin's dad

