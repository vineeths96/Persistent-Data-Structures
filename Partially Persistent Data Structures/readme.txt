FILES INCLUDES WITH THIS PROJECT:
================================================================

	client.c	header.h	implement.c
	readme.txt	makefile	
	
	(in every folder)


PROGRAM
================================================================

INTRODUCTION
-------------

	A persistent data structure is a data structure that always preserves the previous version of itself when
it is modified. They are effectively immutable, in the sense that their operations do not (visibly) update the
structure in-place, but always produce a new updated version. A data structure is partially persistent
if all versions can be accessed but only the newest version can be modified. The data structure is fully persistent
if every version can be both accessed and modified. In this program, each node contains a modification box with a
timestamp to hold a single modification. If more than modification is applied to a node, the node is split to create
a new node with the latest values. Amortized O(1) time and space can be achieved for access and updates using this
method. This method was originally given by Sleator, Tarjan et al. Each node contains a modification box that can hold:
	   a. one modification to the node (the modification could be of one of the pointers, or to the node’s key or
	      to some other node-specific data)
	   b. the time instance (or version number) when the mod was applied
The timestamp is essential for tracing the path to the version of the node we care about.

OPERATING SYSTEM AND SOFTWARE REQUIRMENTS
------------------------------------------

	The entire program was developed in Ubuntu operating system using C language. It is highly recommeneded 
to use the Ubuntu system to execute the program. The program requires gcc compiler to compile, build and 
execute the program. The OS and compiler version used for developing the code are :
		Operating system 	: Ubuntu 18.04.1 
		gcc compiler verison	: gcc version 7.4.0

INSTRUCTIONS TO RUN
--------------------

	Open the terminal, make the program and run it. Enter the file name of the graph to be processed as requested 
during exectuion of the program.


CONTACT
========
Developed by
Name	 : Vineeth S
