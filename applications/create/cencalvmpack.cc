// ======================================================================
//
//                           Brad T. Aagaard
//                        U.S. Geological Survey
//
// ======================================================================
//
// Application driver to generate a packed etree database for the central CA
// velocity model for optimized queries.

#include "cencalvm/create/VMCreator.h" // USES VMCreator
#include "cencalvm/storage/ErrorHandler.h" // USES VMCreator

#include <stdlib.h> // USES exit()
#include <unistd.h> // USES getopt()
#include <stdio.h> // USES EOF

#include <iostream> // USES std::cerr
#include <stdexcept> // USES std::exception
#include <assert.h> // USES assert()

// ----------------------------------------------------------------------
void
usage(void)
{ // usage
  std::cerr
    << "usage: cencalvmpack [-h] -i inFile -o outFile\n"
    << "  -i inFile  Parameter file with list of grid input files\n"
    << "  -o outFile    Etree database file created.\n"
    << "  -h            Display usage and exit.\n"
    << "\n"
    << "Parameter file is list of grid input files, one per line.\n";
  exit(1);
} // usage

// ----------------------------------------------------------------------
void
parseArgs(std::string* pFilenameIn,
	  std::string* pFilenameOut,
	  int* pCacheSize,
	  int argc,
	  char** argv)
{ // parseArgs
  assert(0 != pFilenameIn);
  assert(0 != pFilenameOut);
  assert(0 != pCacheSize);

  extern char* optarg;

  int nparsed = 1;
  *pFilenameIn = "";
  *pFilenameOut = "";
  int c = EOF;
  while ( (c = getopt(argc, argv, "c:hi:o:") ) != EOF) {
    switch (c)
      { // switch
      case 'c': // process -c options
	*pCacheSize = atoi(optarg);
	nparsed += 2;
	break;
      case 'i' : // process -i option
	*pFilenameIn = optarg;
	nparsed += 2;
	break;
      case 'o' : // process -o option
	*pFilenameOut = optarg;
	nparsed += 2;
	break;
      case 'h' : // process -h option
	nparsed += 1;
	usage();
	exit(0);
	break;
      default :
	usage();
      } // switch
  } // while
  if (nparsed != argc || 
      0 == pFilenameIn->length() ||
      0 == pFilenameOut->length())
    usage();
} // parseArgs

// ----------------------------------------------------------------------
int
main(int argc,
     char* argv[])
{ // main
  std::string filenameIn = "";
  std::string filenameOut = "";
  int cacheSize = 64;
  
  parseArgs(&filenameIn, &filenameOut, &cacheSize, argc, argv);

  try {
    cencalvm::create::VMCreator creator;
    creator.packDB(filenameOut.c_str(), filenameIn.c_str(), cacheSize);
  } catch (const std::exception& err) {
    std::cerr << err.what();
    return 1;
  } catch (...) {
    return 1;
  } // catch


  return 0;
} // main

// version
// $Id$

// End of file 
