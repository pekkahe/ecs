#include <Precompiled.hpp>
#include <component/SparseIndex.hpp>

using namespace eng;

SparseIndex::Position SparseIndex::bitPos(uint32_t pos)
{
    size_t index = pos / k_bitsPerBlock;
    unsigned bit = pos - (index * k_bitsPerBlock);

    assert(bit >= 0 && bit < k_bitsPerBlock && "Bit index out of range");

    return { index, bit };
}

void SparseIndex::insert(EntityId id)
{
    auto pos = bitPos(id);

    while (pos.index >= m_bits.size())
    {
        allocateBlock();
    }

    m_bits[pos.index].set(pos.bit);
}

void SparseIndex::erase(EntityId id)
{
    auto pos = bitPos(id);

    if (pos.index >= m_bits.size())
    {
        return;
    }

    m_bits[pos.index].reset(pos.bit);
}

void SparseIndex::clear()
{
    m_bits.clear();
}

bool SparseIndex::check(EntityId id) const
{
    auto pos = bitPos(id);

    if (pos.index >= m_bits.size())
    {
        return false;
    }

    return m_bits[pos.index][pos.bit];
}

size_t SparseIndex::size() const
{
    size_t count = 0;

    for (auto& bitset : m_bits)
    {
        count += bitset.count();
    }

    return count;
}

bool SparseIndex::empty() const
{
    return size() == 0u;
}

SparseIndex& SparseIndex::operator|=(const SparseIndex& other)
{
    // Prepare by allocating empty bitsets if necessary
    size_t otherSize = other.m_bits.size();
    while (otherSize > m_bits.size())
    {
        allocateBlock();
    }

    size_t thisSize = m_bits.size();
    size_t maxSize = (std::max)(thisSize, otherSize);

    for (size_t i = 0; i < maxSize; ++i)
    {
        // Other has no more bits to OR
        if (i >= otherSize)
        {
            break;
        }

        m_bits[i] |= other.m_bits[i];
    }

    return *this;
}

SparseIndex& SparseIndex::operator&=(const SparseIndex& other)
{
    size_t thisSize = m_bits.size();
    size_t otherSize = other.m_bits.size();
    size_t maxSize = (std::max)(thisSize, otherSize);

    for (size_t i = 0; i < maxSize; ++i)
    {
        // We have no more bits, no need to continue ANDing
        if (i >= thisSize)
        {
            break;
        }

        // Other has no more bits, reset our leftover bits
        // to simulate ANDing
        if (i >= otherSize)
        {
            m_bits[i].reset();
        }
        else
        {
            m_bits[i] &= other.m_bits[i];
        }
    }

    return *this;
}

SparseIndex& SparseIndex::operator^=(const SparseIndex& other)
{
    // Prepare by allocating empty bitsets if necessary
    size_t otherSize = other.m_bits.size();
    while (otherSize > m_bits.size())
    {
        allocateBlock();
    }

    size_t thisSize = m_bits.size();
    size_t maxSize = (std::max)(thisSize, otherSize);

    bool otherHasNoMoreBits = false;

    for (size_t i = 0; i < maxSize; ++i)
    {
        if (i >= otherSize)
        {
            otherHasNoMoreBits = true;
        }

        if (otherHasNoMoreBits)
        {
            // If other has no more bits, we need to XOR
            // our remaining bits against an empty bitset
            m_bits[i] ^= DataBlock();
        }
        else
        {
            m_bits[i] ^= other.m_bits[i];
        }
    }

    return *this;
}

void SparseIndex::allocateBlock()
{
    m_bits.emplace_back(DataBlock());
}

SparseIndex::Iterator SparseIndex::begin()
{
    size_t size = m_bits.size() * k_bitsPerBlock;

    return Iterator(*this, size);
}

SparseIndex::Iterator SparseIndex::end()
{
    size_t size = m_bits.size() * k_bitsPerBlock;

    return Iterator(*this, size, size);
}

SparseIndex::Iterator& SparseIndex::Iterator::operator++()
{
    // Skip empty bits
    do
    {
        ++m_pos;

        if (m_pos >= m_size)
        {
            break;
        }
    } 
    while (!m_container.check(static_cast<EntityId>(m_pos)));

    return *this;
}

SparseIndex::Iterator SparseIndex::Iterator::operator++(int)
{
    Iterator it = *this;
    ++(*this);
    return it;
}

bool SparseIndex::Iterator::operator==(Iterator other) const
{
    return m_pos == other.m_pos;
}

bool SparseIndex::Iterator::operator!=(Iterator other) const
{
    return !(*this == other);
}

SparseIndex::Iterator::reference SparseIndex::Iterator::operator*() const
{
    return static_cast<EntityId>(m_pos);
}

eng::SparseIndex eng::operator|(const SparseIndex& lhs, const SparseIndex& rhs)
{
    SparseIndex out;
    size_t lhsSize = lhs.m_bits.size();
    size_t rhsSize = rhs.m_bits.size();
    size_t maxSize = (std::max)(lhsSize, rhsSize);

    for (size_t i = 0; i < maxSize; ++i)
    {
        out.allocateBlock();

        if (i >= lhsSize)
        {
            out.m_bits[i] = rhs.m_bits[i];
        }
        else if (i >= rhsSize)
        {
            out.m_bits[i] = lhs.m_bits[i];
        }
        else
        {
            out.m_bits[i] = lhs.m_bits[i] | rhs.m_bits[i];
        }
    }

    return out;
}

eng::SparseIndex eng::operator&(const SparseIndex& lhs, const SparseIndex& rhs)
{
    SparseIndex out;
    size_t lhsSize = lhs.m_bits.size();
    size_t rhsSize = rhs.m_bits.size();
    size_t maxSize = (std::max)(lhsSize, rhsSize);

    for (size_t i = 0; i < maxSize; ++i)
    {
        out.allocateBlock();

        if (i >= lhsSize)
        {
            break;
        }
        else if (i >= rhsSize)
        {
            break;
        }
        else
        {
            out.m_bits[i] = lhs.m_bits[i] & rhs.m_bits[i];
        }
    }

    return out;
}

eng::SparseIndex eng::operator^(const SparseIndex& lhs, const SparseIndex& rhs)
{
    constexpr auto emptyBits = SparseIndex::DataBlock();

    SparseIndex out;
    size_t lhsSize = lhs.m_bits.size();
    size_t rhsSize = rhs.m_bits.size();
    size_t maxSize = (std::max)(lhsSize, rhsSize);

    for (size_t i = 0; i < maxSize; ++i)
    {
        out.allocateBlock();

        if (i >= lhsSize)
        {
            out.m_bits[i] = emptyBits ^ rhs.m_bits[i];
        }
        else if (i >= rhsSize)
        {
            out.m_bits[i] = lhs.m_bits[i] ^ emptyBits;
        }
        else
        {
            out.m_bits[i] = lhs.m_bits[i] ^ rhs.m_bits[i];
        }
    }

    return out;
}