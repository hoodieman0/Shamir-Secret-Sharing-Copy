<a name="page-top"></a>
# Shamir-Secret-Sharing-Copy
![License](https://img.shields.io/github/license/hoodieman0/Shamir-Secret-Sharing-Copy?style=plastic) 
![Issues](https://img.shields.io/github/issues/hoodieman0/Shamir-Secret-Sharing-Copy?style=plastic)
![Contributors](https://img.shields.io/github/contributors/hoodieman0/Shamir-Secret-Sharing-Copy?color=Red&style=plastic)
![LastCommit](https://img.shields.io/github/last-commit/hoodieman0/Shamir-Secret-Sharing-Copy?style=plastic)

A C++ recreation of the Shamir Secret Sharing algorithm. 

# Usage
The SSS.hpp and SSS.cpp files contains the ShamirSecret class implementation and requries MathNotation.hpp, Exceptions.hpp, and Exceptions.cpp. Only SSS.hpp needs to be included in the desired file.


MathNotation.hpp contains the representations used to simplify ShamirSecret functions. Exceptions.hpp generally is used in the UnitTests.hpp file, but does have uses in SSS.hpp/cpp.

# Future Plans
* Making the ShamirSecret class a template class
* Ensuring the ShamirSecret uses a finite field with primes (not sufficiently secure eitherwise)

# References
* [Purdue University Lecture Shamir Secret Sharing Intro Pt. 1](https://www.cs.purdue.edu/homes/hmaji/teaching/Fall%202020/lectures/08.pdf)
* [Purdue University Lecture Shamir Secret Sharing Intro Pt. 2](https://www.cs.purdue.edu/homes/hmaji/teaching/Fall%202020/lectures/09.pdf)
* [Wikipedia Shamir Secret Sharing](https://en.wikipedia.org/wiki/Shamir%27s_secret_sharing#Computationally_efficient_approach)

# Author
* [James Mok (Github)](https://github.com/hoodieman0)