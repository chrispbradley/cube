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


#ifndef __PLUS_EVALUATION_H
#define __PLUS_EVALUATION_H 0

#include "CubeBinaryEvaluation.h"

namespace cube
{
class PlusEvaluation : public BinaryEvaluation
{
public:
    PlusEvaluation();
    PlusEvaluation( GeneralEvaluation*,
                    GeneralEvaluation* );
    virtual
    ~PlusEvaluation();

    virtual
    double
    eval();


    virtual
    double eval( Cnode *, CalculationFlavour, Sysres *, CalculationFlavour   );


    virtual
    double eval( Cnode *, CalculationFlavour );

    virtual
    double*
    eval_row( Cnode*             _cnode,
              CalculationFlavour _cf );

    virtual
    void
    print()
    {
        arguments[ 0 ]->print();
        std::cout << "+";
        arguments[ 1 ]->print();
    };

    virtual
    double
    eval( double arg1,
          double arg2 );
};
};

#endif