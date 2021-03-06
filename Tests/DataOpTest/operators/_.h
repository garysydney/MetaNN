#pragma once
#include <operators/activation/_.h>
#include <operators/blas/_.h>
#include <operators/cate_trans/_.h>
#include <operators/elementwise/_.h>
#include <operators/loss/_.h>
#include <operators/mutating/_.h>

namespace Test::Operators
{
    void test()
    {
        Test::Operators::Activation::test();
        Test::Operators::Blas::test();
        Test::Operators::CateTrans::test();
        Test::Operators::Elwentwise::test();
        Test::Operators::Loss::test();
        Test::Operators::Mutating::test();
    }
}