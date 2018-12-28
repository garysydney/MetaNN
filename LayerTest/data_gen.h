#pragma once
#include <MetaNN/meta_nn2.h>

template <typename TElem>
inline auto GenMatrix(std::size_t r, std::size_t c, TElem start = 0, TElem step = 1)
{
    using namespace MetaNN;
    Matrix<TElem, MetaNN::DeviceTags::CPU> res(r, c);
    
    TElem cur{};
    for (std::size_t i = 0; i < r; ++i)
    {
        for (std::size_t j = 0; j < c; ++j)
        {
            res.SetValue((TElem)(start + cur), i, j);
            cur += step;
        }
    }
    return res;
}

template <typename TElem>
inline auto GenThreeDArray(size_t p, size_t r, size_t c, TElem start = 0, TElem step = 1)
{
    using namespace MetaNN;
    ThreeDArray<TElem, MetaNN::DeviceTags::CPU> res(p, r, c);
    
    TElem cur{};
    for (size_t k = 0; k < p; ++k)
    {
        for (size_t i = 0; i < r; ++i)
        {
            for (size_t j = 0; j < c; ++j)
            {
                res.SetValue((TElem)(start + cur), k, i, j);
                cur += step;
            }
        }
    }
    return res;
}

template <typename TElem>
inline auto GenBatchScalar(size_t len, TElem start = 0, TElem step = 1)
{
    using namespace MetaNN;
    BatchScalar<TElem, MetaNN::DeviceTags::CPU> res(len);
    TElem cur{};
    for (size_t k = 0; k < len; ++k)
    {
        res.SetValue((TElem)(start + cur), k);
        cur += step;
    }
    return res;
}

template <typename TElem>
inline auto GenBatchMatrix(size_t p, size_t r, size_t c, TElem start = 0, TElem step = 1)
{
    using namespace MetaNN;
    BatchMatrix<TElem, MetaNN::DeviceTags::CPU> res(p, r, c);
    
    TElem cur{};
    for (size_t k = 0; k < p; ++k)
    {
        for (size_t i = 0; i < r; ++i)
        {
            for (size_t j = 0; j < c; ++j)
            {
                res.SetValue((TElem)(start + cur), k, i, j);
                cur += step;
            }
        }
    }
    return res;
}

template <typename TElem>
inline auto GenBatchThreeDArray(size_t b, size_t p, size_t r, size_t c, TElem start = 0, TElem step = 1)
{
    using namespace MetaNN;
    BatchThreeDArray<TElem, MetaNN::DeviceTags::CPU> res(b, p, r, c);
    TElem cur{};
    for (size_t l = 0; l < b; ++l)
    {
        for (size_t k = 0; k < p; ++k)
        {
            for (size_t i = 0; i < r; ++i)
            {
                for (size_t j = 0; j < c; ++j)
                {
                    res.SetValue((TElem)(start + cur), l, k, i, j);
                    cur += step;
                }
            }
        }
    }
    return res;
}

template <typename TElem>
inline auto GenScalarSequence(size_t len, TElem start = 0, TElem scale = 1)
{
    using namespace MetaNN;
    ScalarSequence<TElem, MetaNN::DeviceTags::CPU> res(len);
    for (size_t k = 0; k < len; ++k)
    {
        res.SetValue((TElem)(start * scale), k);
        start += 1.0f;
    }
    return res;
}

template <typename TElem>
inline auto GenMatrixSequence(size_t p, size_t r, size_t c, TElem start = 0, TElem scale = 1)
{
    using namespace MetaNN;
    MatrixSequence<TElem, MetaNN::DeviceTags::CPU> res(p, r, c);
    for (size_t k = 0; k < p; ++k)
    {
        for (size_t i = 0; i < r; ++i)
        {
            for (size_t j = 0; j < c; ++j)
            {
                res.SetValue((TElem)(start * scale), k, i, j);
                start += 1.0f;
            }
        }
    }
    return res;
}

template <typename TElem>
inline auto GenThreeDArraySequence(size_t b, size_t p, size_t r, size_t c, TElem start = 0, TElem scale = 1)
{
    using namespace MetaNN;
    ThreeDArraySequence<TElem, MetaNN::DeviceTags::CPU> res(b, p, r, c);
    for (size_t l = 0; l < b; ++l)
    {
        for (size_t k = 0; k < p; ++k)
        {
            for (size_t i = 0; i < r; ++i)
            {
                for (size_t j = 0; j < c; ++j)
                {
                    res.SetValue((TElem)(start * scale), l, k, i, j);
                    start += 1.0f;
                }
            }
        }
    }
    return res;
}

template <typename TElem, typename TLen>
inline auto GenBatchScalarSequence(const std::vector<TLen>& seqs, TElem start = 0, TElem scale = 1)
{
    using namespace MetaNN;
    BatchScalarSequence<TElem, MetaNN::DeviceTags::CPU> res(seqs);
    for (size_t i = 0; i < seqs.size(); ++i)
    {
        for (size_t k = 0; k < (size_t)seqs[i]; ++k)
        {
            res.SetValue((TElem)(start * scale), i, k);
            start += 1.0f;
        }
    }
    return res;
}

template <typename TElem, typename TLen>
inline auto GenBatchMatrixSequence(const std::vector<TLen>& seqs, size_t rowNum, size_t colNum, TElem start = 0, TElem scale = 1)
{
    using namespace MetaNN;
    BatchMatrixSequence<TElem, MetaNN::DeviceTags::CPU> res(seqs, rowNum, colNum);
    for (size_t i = 0; i < seqs.size(); ++i)
    {
        for (size_t k = 0; k < (size_t)seqs[i]; ++k)
        {
            for (size_t r = 0; r < rowNum; ++r)
            {
                for (size_t c = 0; c < colNum; ++c)
                {
                    res.SetValue((TElem)(start * scale), i, k, r, c);
                    start += 1.0f;                
                }
            }
        }
    }
    return res;
}

template <typename TElem, typename TLen>
inline auto GenBatchThreeDArraySequence(const std::vector<TLen>& seqs, size_t pageNum, size_t rowNum, size_t colNum, TElem start = 0, TElem scale = 1)
{
    using namespace MetaNN;
    BatchThreeDArraySequence<TElem, MetaNN::DeviceTags::CPU> res(seqs, pageNum, rowNum, colNum);
    for (size_t i = 0; i < seqs.size(); ++i)
    {
        for (size_t k = 0; k < (size_t)seqs[i]; ++k)
        {
            for (size_t p = 0; p < pageNum; ++p)
            {
                for (size_t r = 0; r < rowNum; ++r)
                {
                    for (size_t c = 0; c < colNum; ++c)
                    {
                        res.SetValue((TElem)(start * scale), i, k, p, r, c);
                        start += 1.0f;
                    }
                }
            }
        }
    }
    return res;
}