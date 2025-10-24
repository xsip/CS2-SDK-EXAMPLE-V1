#pragma once
#include <span>
#include <vector>
#include <PCH/Internal.h>



namespace Source2 {
    template <typename T >
    class CUtlVector
    {
    public:
        auto begin() const { return m_pData; }
        auto end() const { return m_pData + m_nSize; }

        auto At(int i) const { return m_pData[i]; }
        auto AtPtr(int i) const { return m_pData + i; }

        bool Exists(T val) const
        {
            for (const auto& it : *this)
                if (it == val) return true;
            return false;
        }
        bool Empty() const { return m_nSize == 0; }

        std::span<T> it() { return std::span(m_pData, m_nSize); }

        std::vector<T> CopyToVector(bool log = false) const {
            std::vector<T> vec;
            vec.reserve(m_nSize);
            int i = 0;
            for (const auto& elem : *this) {
                if(log)
                    printf("Element %i: 0x%p\n", i, &elem);
                vec.push_back(elem);  // always copy the element as-is
                i++;
            }

            return vec;
        }

        int m_nSize;
        S2_PAD(0x4);
        T* m_pData;
        S2_PAD(0x8);
    };
    static_assert(sizeof(CUtlVector<void*>) == 0x18);
}