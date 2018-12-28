#include <data/batch/test_dynamic_batch.h>
#include <MetaNN/meta_nn2.h>
#include <calculate_tags.h>
#include <iostream>
using namespace std;
using namespace MetaNN;

namespace
{
    void test_dynamic_batch_scalar_case1()
    {
        cout << "Test dynamic batch scalar case 1...\t";
        using TCardinal = Scalar<CheckElement, CheckDevice>;
        
        static_assert(IsBatchScalar<DynamicBatch<TCardinal>>, "Test Error");
        static_assert(IsBatchScalar<DynamicBatch<TCardinal> &>, "Test Error");
        static_assert(IsBatchScalar<DynamicBatch<TCardinal> &&>, "Test Error");
        static_assert(IsBatchScalar<const DynamicBatch<TCardinal> &>, "Test Error");
        static_assert(IsBatchScalar<const DynamicBatch<TCardinal> &&>, "Test Error");

        auto rm1 = DynamicBatch<TCardinal>();
        assert(rm1.Shape().BatchNum() == 0);
        assert(rm1.IsEmpty());

        rm1.PushBack(3);
        rm1.PushBack(8);
        rm1.PushBack(2);
        assert(rm1.Shape().BatchNum() == 3);
        assert(!rm1.IsEmpty());

        auto evalHandle = rm1.EvalRegister();
        EvalPlan<DeviceTags::CPU>::Eval();
        auto rm2 = evalHandle.Data();
    
        assert(rm2[0] == 3);
        assert(rm2[1] == 8);
        assert(rm2[2] == 2);
        cout << "done" << endl;
    }
    
    void test_dynamic_batch_matrix_case1()
    {
        cout << "Test dynamic batch matrix case 1...\t";
        using TCardinal = Matrix<CheckElement, CheckDevice>;
        
        static_assert(IsBatchMatrix<DynamicBatch<TCardinal>>);
        static_assert(IsBatchMatrix<DynamicBatch<TCardinal> &>);
        static_assert(IsBatchMatrix<DynamicBatch<TCardinal> &&>);
        static_assert(IsBatchMatrix<const DynamicBatch<TCardinal> &>);
        static_assert(IsBatchMatrix<const DynamicBatch<TCardinal> &&>);

        DynamicBatch<TCardinal> rm1(10, 20);
        assert(rm1.Shape().BatchNum() == 0);
        assert(rm1.IsEmpty());

        int c = 0;
        Matrix<CheckElement, CheckDevice> me1(10, 20);
        Matrix<CheckElement, CheckDevice> me2(10, 20);
        Matrix<CheckElement, CheckDevice> me3(10, 20);
        for (size_t i = 0; i < 10; ++i)
        {
            for (size_t j = 0; j < 20; ++j)
            {
                me1.SetValue((CheckElement)(c++), i, j);
                me2.SetValue((CheckElement)(c++), i, j);
                me3.SetValue((CheckElement)(c++), i, j);
            }
        }
        rm1.PushBack(me1);
        rm1.PushBack(me2);
        rm1.PushBack(me3);
        assert(rm1.Shape().BatchNum() == 3);
        assert(!rm1.IsEmpty());

        auto evalHandle = rm1.EvalRegister();
        EvalPlan<DeviceTags::CPU>::Eval();
        auto rm2 = evalHandle.Data();

        for (size_t i = 0; i < 10; ++i)
        {
            for (size_t j = 0; j < 20; ++j)
            {
                assert(rm1[0](i, j) == me1(i, j));
                assert(rm1[1](i, j) == me2(i, j));
                assert(rm1[2](i, j) == me3(i, j));
            }
        }
        cout << "done" << endl;
    }
    
    void test_dynamic_batch_3d_array_case1()
    {
        cout << "Test dynamic batch 3d array case 1...\t";
        using TCardinal = ThreeDArray<CheckElement, CheckDevice>;
        
        static_assert(IsBatchThreeDArray<DynamicBatch<TCardinal>>);
        static_assert(IsBatchThreeDArray<DynamicBatch<TCardinal> &>);
        static_assert(IsBatchThreeDArray<DynamicBatch<TCardinal> &&>);
        static_assert(IsBatchThreeDArray<const DynamicBatch<TCardinal> &>);
        static_assert(IsBatchThreeDArray<const DynamicBatch<TCardinal> &&>);

        DynamicBatch<TCardinal> rm1(7, 10, 20);
        assert(rm1.Shape().BatchNum() == 0);
        assert(rm1.IsEmpty());

        int c = 0;
        TCardinal me1(7, 10, 20);
        TCardinal me2(7, 10, 20);
        TCardinal me3(7, 10, 20);
        
        for (size_t p = 0; p < 7; ++p)
        {
            for (size_t i = 0; i < 10; ++i)
            {
                for (size_t j = 0; j < 20; ++j)
                {
                    me1.SetValue((CheckElement)(c++), p, i, j);
                    me2.SetValue((CheckElement)(c++), p, i, j);
                    me3.SetValue((CheckElement)(c++), p, i, j);
                }
            }
        }
        rm1.PushBack(me1);
        rm1.PushBack(me2);
        rm1.PushBack(me3);
        assert(rm1.Shape().BatchNum() == 3);
        assert(!rm1.IsEmpty());

        auto evalHandle = rm1.EvalRegister();
        EvalPlan<DeviceTags::CPU>::Eval();
        auto rm2 = evalHandle.Data();

        for (size_t p = 0; p < 7; ++p)
        {
            for (size_t i = 0; i < 10; ++i)
            {
                for (size_t j = 0; j < 20; ++j)
                {
                    assert(rm1[0](p, i, j) == me1(p, i, j));
                    assert(rm1[1](p, i, j) == me2(p, i, j));
                    assert(rm1[2](p, i, j) == me3(p, i, j));
                }
            }
        }
        cout << "done" << endl;
    }
}

namespace Test::Data::Batch
{
    void test_dynamic_batch()
    {
        test_dynamic_batch_scalar_case1();
        test_dynamic_batch_matrix_case1();
        test_dynamic_batch_3d_array_case1();
    }
}