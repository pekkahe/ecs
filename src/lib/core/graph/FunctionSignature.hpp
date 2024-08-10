#pragma once

#include <functional>
#include <tuple>
#include <typeindex>
#include <vector>
#include <array>

namespace ecs
{
    template <typename ...Params>
    class FunctionSignature
    {
        struct Parameter
        {
            std::type_index typeIndex;
            bool isConst;
        };

    public:
        FunctionSignature() : m_params({ makeInfo<Params>()... })
                         // : m_arguments(std::make_tuple<Args...>())
        {
        }

        constexpr const Parameter* parameter(size_t index) const
        {
            if (m_params.empty())
            {
                return nullptr;
            }
            return index < m_params.size() ? &m_params[index] : nullptr;
        }

    private:
        // template <size_t... I, typename Func>
        // static void forEach(std::index_sequence<I...>, Func&& func) 
        // {
        //     m_args = { makeInfo<I>()... };
        // }

        template <typename T>
        constexpr static Parameter makeInfo()
        {
            return {
                .typeIndex = typeid(T),
                .isConst = std::is_const<T>::value,
            };
        }

        using Indices = std::index_sequence_for<Params...>;

        void unpack()
        {
            // m_argumentInfo.clear();

            // forEach(Indices(), m_arguments, [&](const auto& arg) {
            //     m_argumentInfo.emplace_back({
            //         .typeInfo = typeid(decltype(arg)),
            //         .isConst = std::is_const<decltype(arg)>::value,
            //     });
            // });
        }

        template <size_t... I, typename Tuple, typename Func>
        static void forEach(std::index_sequence<I...>, Tuple&& tuple, Func&& func) 
        {
            // Unpack 'tuple' and execute 'func' for each value
            doInOrder([&] { func(std::get<I>(std::forward<Tuple>(tuple))); }...);
        }

        template <typename... Func>
        static void doInOrder(Func&&... func)
        {
            // Use comma operator to call each function in parameter pack
            [[maybe_unused]] int unused[] = { 0, ((void) std::forward<Func>(func)(), 0)... };
        }

    private:
        static constexpr auto N = std::index_sequence_for<Params...>().size();

        const std::array<Parameter, N> m_params;
        
        //std::tuple<Args...> m_arguments;
        //std::vector<ArgumentInfo> m_argumentInfo;
    };
}