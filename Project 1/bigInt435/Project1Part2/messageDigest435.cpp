/***
   prepared for CS435 Project 1 part 2
**/

#include <string.h>
#include <iostream>
#include <fstream>
#include "sha256.h"
#include "BigIntegerLibrary.hh"


int main(int argc, char *argv[])
{
   //demonstrating how sha256 works
   std::string input = "testing";
   std::string output1 = sha256(input);
   std::cout << "sha256('"<< input << "'):" << output1 << "\n";

   //demo bigInt works here
   BigUnsigned a = stringToBigUnsigned("124338907642982722929222542626327282");
   BigUnsigned b = stringToBigUnsigned("124338907642977775546469426263278643");
   std::cout << "big a = " <<a<<"\n";
   std::cout << "big b = " <<b<<"\n";
   std::cout << "big a*b = " <<a*b<<"\n";

   //Second part of your project starts here

/*
   //sign a given file
   std::cout << "Enter file name: ";
   std::string inFile;
   std::cin >> inFile;


   inFileStream.close();
   BigUnsigned n,e,d;
   inFileStream.open("d_n.txt");
//   inFileStream >> d >> n;
   inFileStream.close();

   inFileStream.open("e_n.txt");
 //  inFileStream >> e;
   inFileStream.close();

   BigUnsigned hashedValue = stringToBigUnsigned(toBeHashed);
   BigUnsigned signature = modexp(hashedValue, d, n);


   std::ofstream outFileHashedStream;
   outFileHashedStream.open(inFile + ".signature");
   outFileHashedStream << signature;
   outFileHashedStream.close();


   // verify the signed file
   std::string verifytoBeHashed;
   std::cout << "Enter file name: ";
   std::cin >> inFile;
   inFileStream.open(inFile);
   inFileStream >> verifytoBeHashed;
   std::string verifyHashed = sha256(verifytoBeHashed);
   inFileStream.close();

//   std::string signature;
   inFileStream.open(inFile + ".signature");
//   inFileStream >> signature;
   inFileStream.close();

*/




   if (argc != 3 || (argv[1][0]!='s' && argv[1][0]!='v'))
      std::cout << "wrong format! should be \"a.exe s filename\"";
   else {
      std::string filename = argv[2];


      //read the file
      std::streampos begin,end;
      std::ifstream myfile (filename.c_str(), std::ios::binary);
      begin = myfile.tellg();
      myfile.seekg (0, std::ios::end);
      end = myfile.tellg();
      std::streampos size = end-begin;
      //std::cout << "size of the file: " << size << " bytes.\n"; //size of the file

      myfile.seekg (0, std::ios::beg);
      char * memblock = new char[size];
      myfile.read (memblock, size); //read file; it's saved in the char array memblock
      myfile.close();

      std::string copyOFfile = filename+".Copy";
      std::ofstream myfile2 (copyOFfile.c_str(), std::ios::binary);
      myfile2.write (memblock, size); //write to a file
      myfile2.close();

      //std::cout<<memblock;

      if (argv[1][0]=='s') {
         std::cout << "\n"<<"Need to sign the doc.\n";
         //.....
        std::ifstream inFileStream;
        inFileStream.open(filename);
        std::string toBeHashed;
        getline(inFileStream, toBeHashed, (char)inFileStream.eof()); // pass entire document into string
        std::string hashed = sha256(toBeHashed); // hash file
        BigUnsigned x =  BigUnsignedInABase(hashed,16); // base 16 Hash -> Base 10
        inFileStream.close();

        std::string dString, nString;
        inFileStream.open("d_n.txt");
        inFileStream >> dString >> nString; // get D and N
        inFileStream.close();
        BigUnsigned d = stringToBigUnsigned(dString); // store d and N
        BigUnsigned n = stringToBigUnsigned(nString);

        BigUnsigned signature = modexp(x, d, n); // X^D mod N
        std::ofstream outFileHashedStream;
        outFileHashedStream.open(filename + ".signature"); // set to signature
        outFileHashedStream << signature;
        outFileHashedStream.close();

        std::cout << "\n DOC IS SIGNED";
//

      }
      else {
         std::cout << "\n"<<"Need to verify the doc.\n";
         //.....
        std::ifstream inFileStream;
        inFileStream.open(filename);
        std::string toBeHashed;
        getline(inFileStream, toBeHashed, (char)inFileStream.eof()); // pass entire document into string
        std::string hashed = sha256(toBeHashed);
        BigUnsigned x =  BigUnsignedInABase(hashed,16);
        inFileStream.close();

        inFileStream.open(filename + ".signature");
        std::string signature;
        inFileStream >> signature;
        BigUnsigned y = stringToBigUnsigned(signature); // get Signature
        inFileStream.close();


        std::string eString, nString;
        inFileStream.open("e_n.txt");
        inFileStream >> eString >> nString; // get e N
        inFileStream.close();
        BigUnsigned e = stringToBigUnsigned(eString);
        BigUnsigned n = stringToBigUnsigned(nString);

        BigUnsigned encrypt = modexp(y, e, n); // X^e mod N

        if (x == encrypt)
            std::cout<< "Verification Passed, document authentic";
        else
            std::cout << "Verification Failed, document modified";

      }
      delete[] memblock;
    }
    return 0;
}
