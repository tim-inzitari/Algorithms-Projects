Tim Inzitari
4387347
tsi3@zips.uakron.edu

This project is used to compare different Convex Hull Algorithms and their run time. Specifically, Graham Scan, Jarvis March and Quick Hull. 

To Run:
	Use hte folloiwng format to Run:   XXX.exe {G,J,Q} [Input File]
		Where you select G for Graham Scan, J For Jarvis March, Q for Quickhull.
		
		
Explanation.

	Graham Scan:
		You send it with an array of points from the input file.
		You then select a Cardinal Extreme point (Highest or Lowest X/Y) 
		then you sort each other point by their polar angle from that point.
		
		You then the first 3 points on to a stack
		and using the vectors between points decide to pop or push points from the stack, if Vector of Considering Point is - you pop, if it is + you push.
		
		Then once complete you simply output hte stack
		
	Jarvis March. 
		
		Select a cardinal Extreme point.
		and check every point for hteir has the lowest external angle between the points
		that point is on the convex hull and continue to the next point
		
		then output hte hull
		
		
	Quick Hull.
	
	You first select a cardinal extreme and select a line at that extreme. You partition each side whether they are above or below and add to the hull based on max distance
	It is a divide an conquer algorithm.
	
	In the implementation it used a set, so in order to properly output hte data for the test, i had to convert this to a vector that can be manually ordered.