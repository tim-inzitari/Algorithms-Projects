Tim Inzitari
4387347
tsi3@zips.uakron.edu

This project is an implementation of RSA using C++

To Run:

	Part 1:
		Nothing required, simply run the program.
		
	Part 2:
		Required:
			Run the program using the following syntax
				
				If Signing a Document
					XXXX.exe s [FileName of Document to be signed, ex["file.txt"]
				
				If Verifying
					XXXX.exe v [FileName of Document to be signed, ex["file.txt"]
					

Explanation:

Part 1:
	
	To start we first generate 2 very large prime numbers using the BigUnsigned class and Fermat's Test that is (modular exponation of X using base^(x-1) mod x  and seeing if it equals one for two test cases) store these in p and q
	
	
	We save p and q in a file.
	
	We then generate N = pq
	set e as a number relatively prime to (p-1)(q-1)
	and d as modular inverse of e mod (p-1)(q-1)
	
	We store these in files
	
	
Part 2:
	
		Signing:
			
			Hash the content of a file in sha256
			Convert this base16 Hash into a big Unsigned X 
			
			Compute Signature Y = X^(d) mod N (from part 1)
			store Signature in a file.
			
		Verifying:
			Hash the content of a file in 256; Convert base16 hash to Big Unsigned X
			Obtain the signature of a file (filename+.signature) store as BigUnsigned Y
			Encrypt with Z = Y^e mod N
			
			Compare Z and X
			