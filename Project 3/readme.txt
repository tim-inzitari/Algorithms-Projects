Tim Inzitari
4387347
tsi3@zips.uakron.edu

This project demonstrates my mastery of hte seam carving algorithm using dynamic programing.

To Run:
	Use the following format in command line to Run
		XXX.exe [# of Vertical Seams to Remove] [# of Horizontal Seams to Remove] [Input File]

Explanation:
	We implement the seam carving image using a class creation.
	
	The Class has 5 private variables, a 2D array that holds the image, itself. A 2 array that holds the pixel energy matrix (will be explained later) An integer for width, an integer for height. and a string for Max Grey Scale.
	
	3 Public Functions
		a constructor that takes  astring.
		the seam carve itself
		and an output function that takes a string
		
	8 Private Functions
		void CollectFromFile that takes a string
		Void GenPixEnerMatrix to generate the pixel matrix
		int calculate pixel energy, that takes in two integer variables, and is used ot calculate a pixel's energy
		void vCarve, for vertical Carving
		void hCarve for horizontal Carving
		void idVSeam to identify a vertical Seams
		void deleteVSeam to delete the seam
		void rotateImage to rotate the image by swapping x-Y and y-X which is used for horizontal seams
		

	Pixel Energy is defined as the difference between each pixel and its neighbors
	calculated using the formula given to us. 
	
	energy of pixel at location i,j is:
	e(i,j) = |v(i,j) 0 v(i-1,j)| + |v(i,j)-v(i+1,j)|+|v(i,j) - v(i,j-1)| + |v(i,j) - v(i,j+1)|
	
	these energies are stored in an energy pixel matrix that is WxH wide;
	
	We use these energies to find seams, to delete to make deletion the least noticble.
	We can do vertical and horizontal seams, however hte horizontal seams are done by swapping the x and y cordinates at every point in matrix to turn them into vertical seams. This allows us to only have to implement one way to do the seams.
	
	Seams start at hte bottom of the image, and can contain its UPper, UpperLeft, or Upper RIght neighbor, depending on which one is lowest energy. 
	The lowest vertical seam for any point i,j is given by equation
	M(i,j) = e(i,j) + Min{ M(i-1,j-1) , M(i,j-1) , M(i+1,J-1).
	
	We then go through the top row and find hte lowest seam. We then trace back set all member pixels of that seam to -1;
	
	We then delete every pixel with value of -1
	
	if Horizontal seam, we then rotate the image back.
	
	
	