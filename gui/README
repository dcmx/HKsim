

# Hegselmann-Krause Systems Visualization GUI

## How to compile and run:
 
 1. Check our repository.
 2. Install dependencies:
	- \# apt install libgl-dev
	- \# apt install libglu-dev
	- \# apt install freeglut3-dev
3. Compile:
	- $ mkdir build
	- $ cd build/
	- $ cmake ../src/
	- $ make
4. Run:
	- $ ./hk

## The following key bindings are implemented:

- case 'p':
	- change point size
- case 'l':
	- change line width
- case 's':
	- show selection
- case 'h':
	- show inactive edges between all pairs of nodes
- case 'H':
	- show inactive edges of social graph
- case 'P':
	- compute potential function
- case 'd':
	- switch between one and two dimensional HKS
- case ' ' (blank):
	- update a randomly selected node
- case 'G':
	- add edges between all pairs of nodes
- default:
	- set click mode to pressed key.

## The following click modes are implemented:

- case 'a':
	- add new node
- case 'e':
    - add edge
- case 'E':
    - add all edges for selected node
- case 'u':
	- update highlighted node
- case 'S':
	- select and move node
	
Click modes control what happens after a mouse click.

## Reading a network from standard input:

The simulation will read a geometric graph in "line" format from standard input. The file must 
- start with a list of (x,y) coordinates of nodes,
- followed by a blank line, and finally
- followed by a list of zero-indexed edges.

The following example file should give a square:

    0.0 0.0
    0.0 1.0
    1.0 0.0
    1.0 1.0
    
    0 1
    1 2
    2 3
    3 0

