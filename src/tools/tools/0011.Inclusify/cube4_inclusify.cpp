/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2016                                                **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  Copyright (c) 2009-2015                                                **
**  German Research School for Simulation Sciences GmbH,                   **
**  Laboratory for Parallel Programming                                    **
**                                                                         **
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/


/**
 * \file cube4_inclusify.cpp
 * \brief Creates a cube with inclusive values in calltree dimenstion of input cube.
 *
 */
/******************************************

   Performance Algebra Operation: INCLUSIFY

 *******************************************/

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>
// #ifndef CUBE_COMPRESSED
// #  include <fstream>
// #else
// #  include "zfstream.h"
// #endif
#include <sstream>
#include <unistd.h>

#include "Cube.h"
#include "CubeServices.h"

#include "algebra4.h"

using namespace std;
using namespace cube;
using namespace services;
/**
 * Main program.
 * - Check calling arguments
 * - Read the .cube input file
 * - Calls cube_inclusify(...) to create an inclusified copy of the cube.
 * - Saves a new cube in the file "inclusify.cube|.gz"
 * - end.
 */
int
main( int argc, char* argv[] )
{
    // Handle arguments
    int  ch;
    bool subset   = false;
    bool collapse = false;

    vector <string> inputs;

    const string USAGE = "Usage: " + string( argv[ 0 ] ) + " [-h] [-c|-C]  <cube1> <cube2> ...\n"
                         "  -c     Reduce system dimension. \n"
                         "  -C     Collapse system dimension! Overrides option -c.\n"
                         "  -h     Help; Output a brief help message.\n"
    ;

    while ( ( ch = getopt( argc, argv, "cCh?" ) ) != EOF )
    {
        switch ( ch )
        {
            case 'c':
                subset = true;
                break;
            case 'C':
                collapse = true;
                break;
            case 'h':
            case '?':
                cerr << USAGE << endl;
                exit( 0 );
                break;
            default:
                cerr << USAGE << "\nError: Wrong arguments.\n";
                exit( 0 );
        }
    }


    if ( argc - optind > 0 )
    {
        string cur;
        for ( int i = optind; i < argc; i++ )
        {
            cur = argv[ i ];
            inputs.push_back( cur );
        }
    }
    else
    {
        cerr << USAGE << "Error: At least one file is required.\n\n";
        exit( 0 );
    }

    for ( unsigned i = 0; i < inputs.size(); i++ )
    {
        cout << "Reading " << inputs[ i ] << " ... " << flush;
        if ( check_file( inputs[ i ].c_str() ) != 0 )
        {
            continue;
        }


        Cube* in_cube  = new Cube();
        Cube* out_cube = new Cube();
        in_cube->openCubeReport( inputs[ i ].c_str() );


        cube4_inclusify( out_cube, in_cube, subset, collapse );

        out_cube->writeCubeReport( ( string( get_cube4_name( inputs[ i ] ) ) + "_incl" ).c_str() );
        delete in_cube;
        delete out_cube;
        cout << "done." << endl;
    }
}
