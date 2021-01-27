// You need to complete this program for your second project.

// Standard libraries
#include <string>
#include <iostream>
#include <stdlib.h>
#include <stack>
#include <fstream>
#include <vector>
#include <set>

#define iPair std::pair<int, int>
struct Point
{
    int x, y;
};

// Stores the result (points of convex hull in quick hull)
std::set<iPair> hull;

//Global Point needed for Graham Scan
Point gp0;

// Graham Scan Functions
Point gNextToTop(std::stack<Point> &S);
int gSwap(Point &p1, Point &p2);
int gDistSq(Point p1, Point p2);
int Gorientation(Point p, Point q, Point r);
int Gcompare(const void *vp1, const void *vp2);
void GrahamScan(Point points[], int n, std::string outputFile);


// JARVIS MARCH Functions
int jorientation(Point p, Point q, Point r);
void JarvisMarch(Point points[], int n, std::string outputFile);

// quick hull functions
int QfindSide(iPair p1, iPair p2, iPair p);
int QlineDist(iPair p1, iPair p2, iPair p);
void quickHull(iPair a[], int n, iPair p1, iPair p2, int side);
void printQHull(iPair a[], int n,std::string outputFile);


int main(int argc, char *argv[])
{
   //Second project starts here
   if (argc < 3)
      std::cout << "wrong format! should be \"a.exe algType dataFile\"";
   else {
      std::string algType = argv[1];
      std::string dataFilename = argv[2];
      std::string outputFile = "";
      //read your data points from dataFile (see class example for the format)
      std::ifstream inFile;
      inFile.open(dataFilename);
      std::string unused;
      int numline=0;
      while (std::getline(inFile, unused))
        {
             ++numline;
        }
      inFile.close();

      if (algType[0]=='G') {
         //call your Graham Scan algorithm to solve the problem
       inFile.open(dataFilename);
       int i = 0;
       Point points[numline];
       while (!inFile.eof())
         {
             inFile >> points[i].x >> points[i].y;
             ++i;
         }
       inFile.close();

       outputFile = "hull_G.txt";
       GrahamScan(points, numline, outputFile);
      }
      else if (algType[0]=='J') {
         //call your Javis March algorithm to solve the problem
        inFile.open(dataFilename);
        int i = 0;
        Point points[numline];
        while (!inFile.eof())
            {
             inFile >> points[i].x >> points[i].y;
             ++i;
            }
        inFile.close();
        outputFile = "hull_J.txt";
        JarvisMarch(points, numline, outputFile);
      }
      else { //default
         //call your Quickhull algorithm to solve the problem
         inFile.open(dataFilename);
         int x, y;
         int i = 0;
         iPair a[numline];
         while (!inFile.eof())
         {
             inFile >> x >> y;
             a[i] = {x, y};
             ++i;
         }
         outputFile = "hull_Q.txt";
         printQHull(a,numline,outputFile);
      }

      //write your convex hull to the outputFile (see class example for the format)
      //you should be able to visulize your convex hull using the "ConvexHull_GUI" program.

	return 0;
}
}

/*-------------------------------------------------------------------------
    Graham Scan   https://www.geeksforgeeks.org/convex-hull-set-2-graham-scan/
----------------------------------------------------------------------------*/
// A utility function to find next to top in a stack
Point gNextToTop(std::stack<Point> &S)
{
    Point p = S.top();
    S.pop();
    Point res = S.top();
    S.push(p);
    return res;
}

// A utility function to swap two points
int gSwap(Point &p1, Point &p2)
{
    Point temp = p1;
    p1 = p2;
    p2 = temp;
}

// A utility function to return square of distance
// between p1 and p2
int gDistSq(Point p1, Point p2)
{
    return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
}


// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int Gorientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;  // colinear
    return (val > 0)? 1: 2; // clock or counterclock wise
}

// A function used by library function qsort() to sort an array of
// points with respect to the first point
int Gcompare(const void *vp1, const void *vp2)
{
   Point *p1 = (Point *)vp1;
   Point *p2 = (Point *)vp2;

   // Find orientation
   int o = Gorientation(gp0, *p1, *p2);
   if (o == 0)
     return (gDistSq(gp0, *p2) >= gDistSq(gp0, *p1))? -1 : 1;

   return (o == 2)? -1: 1;
}

// Prints convex hull of a set of n points.
void GrahamScan(Point points[], int n, std::string outputFile)
{
   // Find the bottommost point
   int ymin = points[0].y, min = 0;
   for (int i = 1; i < n; i++)
   {
     int y = points[i].y;

     // Pick the bottom-most or chose the left
     // most point in case of tie
     if ((y < ymin) || (ymin == y &&
         points[i].x < points[min].x))
        ymin = points[i].y, min = i;
   }

   // Place the bottom-most point at first position
   gSwap(points[0], points[min]);

   // Sort n-1 points with respect to the first point.
   // A point p1 comes before p2 in sorted ouput if p2
   // has larger polar angle (in counterclockwise
   // direction) than p1
   gp0 = points[0];
   std::qsort(&points[1], n-1, sizeof(Point), Gcompare);

   // If two or more points make same angle with p0,
   // Remove all but the one that is farthest from p0
   // Remember that, in above sorting, our criteria was
   // to keep the farthest point at the end when more than
   // one points have same angle.
   int m = 1; // Initialize size of modified array
   for (int i=1; i<n; i++)
   {
       // Keep removing i while angle of i and i+1 is same
       // with respect to p0
       while (i < n-1 && Gorientation(gp0, points[i],
                                    points[i+1]) == 0)
          i++;


       points[m] = points[i];
       m++;  // Update size of modified array
   }

   // If modified array of points has less than 3 points,
   // convex hull is not possible
   if (m < 3) return;

   // Create an empty stack and push first three points
   // to it.
   std::stack<Point> S;
   S.push(points[0]);
   S.push(points[1]);
   S.push(points[2]);

   // Process remaining n-3 points
   for (int i = 3; i < m; i++)
   {
      // Keep removing top while the angle formed by
      // points next-to-top, top, and points[i] makes
      // a non-left turn
      while (Gorientation(gNextToTop(S), S.top(), points[i]) != 2)
         S.pop();
      S.push(points[i]);
   }

   // Now stack has the output points, print contents of stack
    std::ofstream outFile;
       outFile.open(outputFile);
   while (!S.empty())
   {
       Point p = S.top();

       outFile << p.x << "\t" << p.y << std::endl;
       S.pop();
   }
   outFile.close();
}

/* -----------------------------------------------------------------------------------
    END GRAHAM SCAN
    ----------------------------------------------------------------------------------
    */


/*
    -------------------------------------------------------------------------------------
    JARVIS MARCH  https://www.geeksforgeeks.org/convex-hull-set-1-jarviss-algorithm-or-wrapping/
    -------------------------------------------------------------------------------------
*/

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int jorientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;  // colinear
    return (val > 0)? 1: 2; // clock or counterclock wise
}

// Prints convex hull of a set of n points.
void JarvisMarch(Point points[], int n, std::string outputFile)
{
    // There must be at least 3 points
    if (n < 3) return;

    // Initialize Result
    std::vector<Point> hull;

    // Find the leftmost point
    int l = 0;
    for (int i = 1; i < n; i++)
        if (points[i].x < points[l].x)
            l = i;

    // Start from leftmost point, keep moving counterclockwise
    // until reach the start point again.  This loop runs O(h)
    // times where h is number of points in result or output.
    int p = l, q;
    do
    {
        // Add current point to result
        hull.push_back(points[p]);

        // Search for a point 'q' such that orientation(p, x,
        // q) is counterclockwise for all points 'x'. The idea
        // is to keep track of last visited most counterclock-
        // wise point in q. If any point 'i' is more counterclock-
        // wise than q, then update q.
        q = (p+1)%n;
        for (int i = 0; i < n; i++)
        {
           // If i is more counterclockwise than current q, then
           // update q
           if (jorientation(points[p], points[i], points[q]) == 2)
               q = i;
        }

        // Now q is the most counterclockwise with respect to p
        // Set p as q for next iteration, so that q is added to
        // result 'hull'
        p = q;

    } while (p != l);  // While we don't come to first point

    // Print Result
    std::ofstream outFile;
    outFile.open(outputFile);
    for (int i = 0; i < hull.size(); i++)
        outFile << hull[i].x << "\t" << hull[i].y << "\n";
    outFile.close();
}

/* -----------------------------------------------------------------------------------
    END Jarvis March
    ----------------------------------------------------------------------------------
    */



/* ---------------------------------------------------------------------------------------
    START QUICK HULL https://www.geeksforgeeks.org/quickhull-algorithm-convex-hull/
    --------------------------------------------------------------------------------------
*/

// Returns the side of point p with respect to line
// joining points p1 and p2.
int QfindSide(iPair p1, iPair p2, iPair p)
{
    int val = (p.second - p1.second) * (p2.first - p1.first) -
              (p2.second - p1.second) * (p.first - p1.first);

    if (val > 0)
        return 1;
    if (val < 0)
        return -1;
    return 0;
}

// returns a value proportional to the distance
// between the point p and the line joining the
// points p1 and p2
int QlineDist(iPair p1, iPair p2, iPair p)
{
    return abs ((p.second - p1.second) * (p2.first - p1.first) -
               (p2.second - p1.second) * (p.first - p1.first));
}

// End points of line L are p1 and p2.  side can have value
// 1 or -1 specifying each of the parts made by the line L
void quickHull(iPair a[], int n, iPair p1, iPair p2, int side)
{
    int ind = -1;
    int max_dist = 0;

    // finding the point with maximum distance
    // from L and also on the specified side of L.
    for (int i=0; i<n; i++)
    {
        int temp = QlineDist(p1, p2, a[i]);
        if (QfindSide(p1, p2, a[i]) == side && temp > max_dist)
        {
            ind = i;
            max_dist = temp;
        }
    }

    // If no point is found, add the end points
    // of L to the convex hull.
    if (ind == -1)
    {
        hull.insert(p1);
        hull.insert(p2);
        return;
    }

    // Recur for the two parts divided by a[ind]
    quickHull(a, n, a[ind], p1, -QfindSide(a[ind], p1, p2));
    quickHull(a, n, a[ind], p2, -QfindSide(a[ind], p2, p1));
}

void printQHull(iPair a[], int n,std::string outputFile)
{
    // a[i].second -> y-coordinate of the ith point
    if (n < 3)
    {
        std::cout << "Convex hull not possible\n";
        return;
    }

    // Finding the point with minimum and
    // maximum x-coordinate
    int min_x = 0, max_x = 0;
    for (int i=1; i<n; i++)
    {
        if (a[i].first < a[min_x].first)
            min_x = i;
        if (a[i].first > a[max_x].first)
            max_x = i;
    }

    // Recursively find convex hull points on
    // one side of line joining a[min_x] and
    // a[max_x]
    quickHull(a, n, a[min_x], a[max_x], 1);

    // Recursively find convex hull points on
    // other side of line joining a[min_x] and
    // a[max_x]
    quickHull(a, n, a[min_x], a[max_x], -1);


    // order is messed up so fixing that
    std::vector<iPair> hullVector;
    while (!hull.empty())
    {
        hullVector.push_back(*hull.begin());
        hull.erase(hull.begin());
    }

    std::vector<iPair> displayVector;
    displayVector.push_back(hullVector[0]);

    // Add all points Greater than start to correct ordered
    for (int i = 1; i < hullVector.size(); i++)
    {
        if (hullVector[i].second < displayVector[0].second)
        displayVector.push_back(hullVector[i]);
    }

     for (int i = hullVector.size(); i > 0; i--)
    {
        if (hullVector[i].second == displayVector[0].second)
        displayVector.push_back(hullVector[i]);
    }

    // add all less than to hull backwards

    for (int i = hullVector.size(); i > 0; i--)
    {
        if (hullVector[i].second >= displayVector[0].second)
        displayVector.push_back(hullVector[i]);
    }

    std::ofstream outFile;
    outFile.open(outputFile);
 /*   outFile << ( *hull.begin()).first << "\t"
             << (*hull.begin()).second;
        hull.erase(hull.begin());
    while (!hull.empty())
    {
        outFile << "\n";
        outFile << ( *hull.begin()).first << "\t"
             << (*hull.begin()).second;
        hull.erase(hull.begin());
    }
*/
    outFile << displayVector[0].first << "\t" << displayVector[0].second;
    for (int i = 1; i < displayVector.size(); i++)
    {
        outFile << "\n";
        outFile << displayVector[i].first << "\t" << displayVector[i].second;
    }
}
