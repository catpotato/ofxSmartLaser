ofxSmartLaser 
=====================================

Introduction
------------
This code builds on ofxIlda, which took care of a lot of the headaces of sending points to the laser, but draws in an simple way that makes messy drawings.

ofxSmartLaser draws in a smart way to make clean drawings in a few ways. Packaged in ofxSmartLaser are:
- the ability to draw bezier curves
- smart resampling at corners (i.e. more points sampled at sharp turns)
- color bleed adjustment (in case the laser overshoots its color)
- connecting polygons together with blank points, also intelligently resampled
- a laser dispatch for managing the etherdream and gui controls
- and more!

License
-------
The code in this repository is available under the MIT License.
Copyright (c) 2017 Clark Addis

Installation
------------
Drag this folder into the `openFrameworks/addons/` folder.

Dependencies
------------
- ofxEtherdream
- ofxIlda (temporarily)
- ofxGui

Compatibility
------------
Currently tested on ofx_v0.9.8




