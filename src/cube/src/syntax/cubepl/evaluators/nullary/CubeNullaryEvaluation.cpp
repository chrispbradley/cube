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


#ifndef __NULLARY_EVALUATION_CPP
#define __NULLARY_EVALUATION_CPP 0

#include "CubeNullaryEvaluation.h"
using namespace cube;

NullaryEvaluation::NullaryEvaluation() : GeneralEvaluation()
{
};

NullaryEvaluation::~NullaryEvaluation()
{
}

size_t
NullaryEvaluation::getNumOfArguments()
{
    return 0;
}


#endif
