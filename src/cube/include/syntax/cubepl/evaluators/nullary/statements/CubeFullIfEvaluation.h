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


#ifndef __FULL_IF_EVALUATION_H
#define __FULL_IF_EVALUATION_H 0

#include "CubeNullaryEvaluation.h"

namespace cube
{
class FullIfEvaluation : public NullaryEvaluation
{
protected:
    GeneralEvaluation* condition;
    unsigned           n_true;
    unsigned           n_false;
public:
    FullIfEvaluation( GeneralEvaluation* _condition,
                      unsigned           _n_true,
                      unsigned           _n_false ) : NullaryEvaluation(), condition( _condition ), n_true( _n_true ), n_false( _n_false )
    {
    };
    ~FullIfEvaluation();



    inline
    virtual
    void
    setRowSize( size_t size )
    {
        row_size = size;
        condition->setRowSize( size );
        for ( std::vector<GeneralEvaluation*>::iterator iter = arguments.begin(); iter != arguments.end(); ++iter )
        {
            GeneralEvaluation* arg = *iter;
            arg->setRowSize( size );
        }
    }
    
    inline
    virtual
    void
    set_verbose_execution( bool _v )
    {
	GeneralEvaluation::set_verbose_execution( _v );
	condition->set_verbose_execution( _v );
    }
    
    virtual
    double
    eval();

    virtual
    double
    eval( Cnode* cnode, CalculationFlavour cf, Sysres* sr, CalculationFlavour tf  )
    {
        double _tmp = condition->eval( cnode, cf, sr, tf );
        if ( _tmp != 0 )
        {
            for ( unsigned i = 0; i < n_true; ++i )
            {
                arguments[ i ]->eval( cnode, cf, sr, tf );
            }
        }
        else
        {
            for ( unsigned i = n_true; i < n_true + n_false; ++i )
            {
                arguments[ i ]->eval( cnode, cf, sr, tf  );
            }
        }
        return 0.;
    };


    virtual
    double
    eval( Cnode* cnode, CalculationFlavour cf )
    {
        double _tmp = condition->eval( cnode, cf );
        if ( _tmp != 0 )
        {
            for ( unsigned i = 0; i < n_true; ++i )
            {
                arguments[ i ]->eval( cnode, cf );
            }
        }
        else
        {
            for ( unsigned i = n_true; i < n_true + n_false; ++i )
            {
                arguments[ i ]->eval( cnode, cf );
            }
        }
        return 0.;
    };


    virtual
    double
    eval( double arg1, double arg2 )
    {
        double _tmp = condition->eval( arg1, arg2 );
        if ( _tmp != 0 )
        {
            for ( unsigned i = 0; i < n_true; ++i )
            {
                arguments[ i ]->eval( arg1, arg2 );
            }
        }
        else
        {
            for ( unsigned i = n_true; i < n_true + n_false; ++i )
            {
                arguments[ i ]->eval( arg1, arg2 );
            }
        }
        return 0.;
    };

    virtual
    double*
    eval_row( Cnode*             cnode,
              CalculationFlavour cf )
    {
        double _tmp = condition->eval( cnode, cf );
        if ( _tmp != 0 )
        {
            for ( unsigned i = 0; i < n_true; ++i )
            {
                delete[] arguments[ i ]->eval_row( cnode, cf );
            }
        }
        else
        {
            for ( unsigned i = n_true; i < n_true + n_false; ++i )
            {
                delete[] arguments[ i ]->eval_row( cnode, cf );
            }
        }
        return NULL;
    };


    virtual
    void
    print()
    {
        std::cout << "if (";
        condition->print();
        std::cout << ") " << std::endl << "{" << std::endl;
        for ( unsigned i = 0; i < n_true; ++i )
        {
            arguments[ i ]->print();
        }
        std::cout << "} " << std::endl << "else "  << std::endl << "{ " << std::endl;
        for ( unsigned i = n_true; i < n_true + n_false; ++i )
        {
            arguments[ i ]->print();
        }
        std::cout << "};" << std::endl;
    };
};
};

#endif
