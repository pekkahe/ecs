#pragma once

#include <component/EntityId.hpp>

#include <vector>
#include <bitset>
#include <limits>

namespace eng
{
    class SparseSet
    {
    private:
        static constexpr unsigned k_size = 256;

    public:
        SparseSet()
        {
            m_sparse.resize(k_size, nullptr);
        }

        void insert(EntityId id)
        {
            m_dense.emplace_back(id);
            
            size_t k = static_cast<size_t>(id);

            if (m_sparse.size() <= k)
            {
                m_sparse.resize(k, nullptr);
            }

            m_sparse[k] = &m_dense.back();
        }

        void erase(EntityId id)
        {
            size_t k = static_cast<size_t>(id);

            if (m_sparse.size() <= k)
            {
                return;
            }

            // Swap last value to erased value
            *(m_sparse[k]) = m_dense.back();

            // Update sparse vector
            m_sparse[m_dense.back()] = m_sparse[k];
            m_sparse[k] = nullptr;

            // Remove last value
            m_dense.erase(m_dense.end() - 1);
        }
               
        void clear()
        {
            m_dense.clear();
            m_sparse.clear();
            m_sparse.resize(k_size, nullptr);
        }

        bool check(EntityId id) const
        {
            size_t k = static_cast<size_t>(id);

            if (m_sparse.size() <= k)
            {
                return m_sparse[k] != nullptr;
            }

            return false;
        }

        size_t size() const
        {
            return m_dense.size();
        }

        bool empty() const
        {
            return m_dense.empty();
        }

        //SparseSet& operator|=(const SparseSet& other)
        //{
        //    size_t localSize = m_bits.size();
        //    size_t otherSize = other.m_bits.size();
        //    size_t maxSize = (std::max)(localSize, otherSize);

        //    for (size_t i = 0; i < maxSize; ++i)
        //    {
        //        if (otherSize < i)
        //        {
        //            break;
        //        }

        //        if (localSize < i)
        //        {
        //            allocateOne();
        //            localSize++;
        //        }

        //        m_bits[i] |= other.m_bits[i];
        //    }

        //    return *this;
        //}

        //SparseSet& operator&=(const SparseSet& other)
        //{
        //    size_t localSize = m_bits.size();
        //    size_t otherSize = other.m_bits.size();
        //    size_t maxSize = (std::max)(localSize, otherSize);

        //    for (size_t i = 0; i < maxSize; ++i)
        //    {
        //        if (otherSize < i)
        //        {
        //            break;
        //        }

        //        if (localSize < i)
        //        {
        //            allocateOne();
        //            localSize++;
        //        }

        //        m_bits[i] &= other.m_bits[i];
        //    }

        //    return *this;
        //}

        //SparseSet& operator^=(const SparseSet& other)
        //{
        //    size_t localSize = m_bits.size();
        //    size_t otherSize = other.m_bits.size();
        //    size_t maxSize = (std::max)(localSize, otherSize);

        //    for (size_t i = 0; i < maxSize; ++i)
        //    {
        //        if (otherSize < i)
        //        {
        //            break;
        //        }

        //        if (localSize < i)
        //        {
        //            allocateOne();
        //            localSize++;
        //        }

        //        m_bits[i] ^= other.m_bits[i];
        //    }

        //    return *this;
        //}

        //inline friend SparseSet operator|(const SparseSet& lhs, const SparseSet& rhs);
        //inline friend SparseSet operator&(const SparseSet& lhs, const SparseSet& rhs);
        //inline friend SparseSet operator^(const SparseSet& lhs, const SparseSet& rhs);

    private:
        std::vector<EntityId>  m_dense;
        std::vector<EntityId*> m_sparse;
    };

    //inline SparseSet operator|(const SparseIndex& lhs, const SparseIndex& rhs)
    //{
    //    size_t lhsSize = lhs.m_bits.size();
    //    size_t rhsSize = rhs.m_bits.size();
    //    size_t maxSize = (std::max)(lhsSize, rhsSize);

    //    SparseIndex out;
    //    size_t outSize = out.m_bits.size();

    //    for (size_t i = 0; i < maxSize; ++i)
    //    {
    //        if (lhsSize < i)
    //        {
    //            break;
    //        }

    //        if (rhsSize < i)
    //        {
    //            break;
    //        }

    //        if (outSize < i)
    //        {
    //            out.allocateOne();
    //            outSize++;
    //        }

    //        out.m_bits[i] = lhs.m_bits[i] | rhs.m_bits[i];
    //    }

    //    return out;
    //}

    //inline SparseIndex operator&(const SparseIndex& lhs, const SparseIndex& rhs)
    //{
    //    size_t lhsSize = lhs.m_bits.size();
    //    size_t rhsSize = rhs.m_bits.size();
    //    size_t maxSize = (std::max)(lhsSize, rhsSize);

    //    SparseIndex out;
    //    size_t outSize = out.m_bits.size();

    //    for (size_t i = 0; i < maxSize; ++i)
    //    {
    //        if (lhsSize < i)
    //        {
    //            break;
    //        }

    //        if (rhsSize < i)
    //        {
    //            break;
    //        }

    //        if (outSize < i)
    //        {
    //            out.allocateOne();
    //            outSize++;
    //        }

    //        out.m_bits[i] = lhs.m_bits[i] & rhs.m_bits[i];
    //    }

    //    return out;
    //}

    //inline SparseIndex operator^(const SparseIndex& lhs, const SparseIndex& rhs)
    //{
    //    size_t lhsSize = lhs.m_bits.size();
    //    size_t rhsSize = rhs.m_bits.size();
    //    size_t maxSize = (std::max)(lhsSize, rhsSize);

    //    SparseIndex out;
    //    size_t outSize = out.m_bits.size();

    //    for (size_t i = 0; i < maxSize; ++i)
    //    {
    //        if (lhsSize < i)
    //        {
    //            break;
    //        }

    //        if (rhsSize < i)
    //        {
    //            break;
    //        }

    //        if (outSize < i)
    //        {
    //            out.allocateOne();
    //            outSize++;
    //        }

    //        out.m_bits[i] = lhs.m_bits[i] ^ rhs.m_bits[i];
    //    }

    //    return out;
    //}
}
