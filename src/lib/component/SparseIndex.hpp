#pragma once

#include <component/EntityId.hpp>

#include <vector>
#include <bitset>
#include <limits>

namespace eng
{
    class SparseIndex
    {
    public:
        void insert(EntityId id);
        void erase(EntityId id);
        void clear();

        bool check(EntityId id) const;

        size_t size() const;
        bool empty() const;

        SparseIndex& operator|=(const SparseIndex& other);
        SparseIndex& operator&=(const SparseIndex& other);
        SparseIndex& operator^=(const SparseIndex& other);

        inline friend SparseIndex operator|(const SparseIndex& lhs, const SparseIndex& rhs);
        inline friend SparseIndex operator&(const SparseIndex& lhs, const SparseIndex& rhs);
        inline friend SparseIndex operator^(const SparseIndex& lhs, const SparseIndex& rhs);

    public:
        class Iterator : public std::iterator<
            std::input_iterator_tag,
            EntityId,
            uint32_t,
            const EntityId*,
            EntityId>
        {
        public:
            explicit Iterator(
                SparseIndex& container,
                size_t size,
                size_t pos = 0) :
                m_container(container),
                m_size(size),
                m_pos(pos)
            {}

            Iterator& operator++();
            Iterator operator++(int);

            bool operator==(Iterator other) const;
            bool operator!=(Iterator other) const;
            
            reference operator*() const;

        private:
            SparseIndex& m_container;
            // Total number of bits in iterated container.
            size_t m_size;
            // Current bit position of iterator.
            size_t m_pos;
        };

    public:
        Iterator begin();
        Iterator end();

    private:
        struct Position
        {
            // Index to vector entry where the bit of the entity is stored
            size_t index;
            // Bit within the indexed entry which marks whether the entity exists or not
            unsigned bit;
        };

        static Position bitPos(uint32_t pos);

    private:
        void allocateBlock();

    private:
        static constexpr unsigned k_bitsPerBlock = 64;

        using DataBlock = std::bitset<k_bitsPerBlock>;

        std::vector<DataBlock> m_bits;
    };

    SparseIndex operator|(const SparseIndex& lhs, const SparseIndex& rhs);
    SparseIndex operator&(const SparseIndex& lhs, const SparseIndex& rhs);
    SparseIndex operator^(const SparseIndex& lhs, const SparseIndex& rhs);
}
