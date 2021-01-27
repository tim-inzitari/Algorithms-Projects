// You need to complete this program for a part of your first project.

// Standard libraries
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>


// 'BigIntegerLibrary.hh' includes all of the library headers.
#include "BigIntegerLibrary.hh"

bool isPrime(BigUnsigned toTest)
{

   // test with 3 numbers
   for (int i = 2; i < 4; i++)
   {

      if(modexp(i, toTest-1, toTest) != 1)
        return false;

   }

   return true;
}
BigUnsigned generateBig()
{

    BigUnsigned big1 = BigUnsigned(1);
    for (int i=0;i<155;i++) {
         big1 = big1*10 +rand();
      }
      //if(isPrime(big1))
        return big1;
}


int main(){
	/* The library throws 'const char *' error messages when things go
	 * wrong.  It's a good idea to catch them using a 'try' block like this
	 * one.  Your C++ compiler might need a command-line option to compile
	 * code that uses exceptions. */
	try {

	/*
      std::cout << "a couple of test cases for 3460:435/535 Algorithms!!!\n";
      BigUnsigned big1 = BigUnsigned(1);
      for (int i=0;i<400;i++) {
         big1 = big1*10 +rand();
      }
      std::cout << std::endl;
      std::cout << isPrime(big1) << std::endl;
      std::cout << "my big1 !!!\n";
      std::cout << big1;
      BigUnsigned big2 = BigUnsigned(1);
      for (int i=0;i<400;i++) {
         big2 = big2*10 +rand();
      }
      std::cout << "my big2 !!!\n";
      std::cout << big2;
      std::cout << "my big3 = big1*big2 !!!\n";
      BigUnsigned big3 = big1*big2;
      std::cout <<big3;
      std::cout << "my big3/big2 !!!\n";
      std::cout <<big3/big2;
      std::cout << std::endl;
      */
      bool notPrime = true;
      BigUnsigned p = BigUnsigned(1);
      p = generateBig();
      notPrime = !(isPrime(p));
      while (notPrime)
      {
          // cant be even or end in 5
        if (p % 2 == 0)
            p++;
        if (p % 5 == 0)
            p+=2;
        p += 2; // add one until prime
        notPrime = !(isPrime(p));
      }

      notPrime = true;
      BigUnsigned q = BigUnsigned(1);
      q = generateBig();
      notPrime = !(isPrime(q));
      while (notPrime)
      {
          // cant be even or end in 5
        if (q % 2 == 0)
            q++;
        if (q % 5 == 0)
            q +=2;
        q += 2; // add two until prime
        notPrime = !(isPrime(q));
      }

      std::ofstream pqFile;
      pqFile.open("p_q.txt");
      pqFile << p << '\n' << q;
      pqFile.close();

      //std::cout << std::endl << std::endl<< p;
      //std::cout << std::endl << isPrime(p);

      //std::cout << std::endl << std::endl<< q;
      //std::cout << std::endl << isPrime(q);
      BigUnsigned n = BigUnsigned(1);
      n = p * q;
      std::cout << n;

      BigUnsigned phi = (q-1) * (p-1);
      BigUnsigned e = BigUnsigned(1);
      BigUnsigned d = BigUnsigned(1);
      e = generateBig();
      while(gcd(phi, e) != 1)
      {
          e +=1; // add one until it works
      }
      std::cout << "\n\n" << gcd(phi,e);
      d = modinv(e,phi);

      std::cout << "\n\n\n" << d << '\n' << e;

      std::ofstream enFile;
      enFile.open("e_n.txt");
      enFile << e << '\n' << n;
      enFile.close();

      std::ofstream dnFile;
      dnFile.open("d_n.txt");
      dnFile << d << '\n' << n;
      dnFile.close();

	} catch(char const* err) {
		std::cout << "The library threw an exception:\n"
			<< err << std::endl;
	}




	return 0;
}
