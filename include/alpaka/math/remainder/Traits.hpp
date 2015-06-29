/**
* \file
* Copyright 2014-2015 Benjamin Worpitz
*
* This file is part of alpaka.
*
* alpaka is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* alpaka is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with alpaka.
* If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <alpaka/core/Common.hpp>   // ALPAKA_FCT_HOST_ACC

#include <type_traits>              // std::enable_if, std::is_base_of, std::is_same, std::decay

namespace alpaka
{
    namespace math
    {
        namespace traits
        {
            //#############################################################################
            //! The remainder trait.
            //#############################################################################
            template<
                typename T,
                typename Tx,
                typename Ty,
                typename TSfinae = void>
            struct Remainder;
        }

        //-----------------------------------------------------------------------------
        //! Computes the IEEE remainder of the floating point division operation x/y.
        //!
        //! \tparam T The type of the object specializing Remainder.
        //! \tparam Tx The type of the first argument.
        //! \tparam Ty The type of the second argument.
        //! \param max The object specializing Max.
        //! \param x The first argument.
        //! \param y The second argument.
        //-----------------------------------------------------------------------------
        template<
            typename T,
            typename Tx,
            typename Ty>
        ALPAKA_FCT_HOST_ACC auto remainder(
            T const & remainder,
            Tx const & x,
            Ty const & y)
        -> decltype(
            traits::Remainder<
                T,
                Tx,
                Ty>
            ::remainder(
                remainder,
                x,
                y))
        {
            return traits::Remainder<
                T,
                Tx,
                Ty>
            ::remainder(
                remainder,
                x,
                y);
        }

        namespace traits
        {
            //#############################################################################
            //! The Remainder specialization for classes with RemainderBase member type.
            //#############################################################################
            template<
                typename T,
                typename Tx,
                typename Ty>
            struct Remainder<
                T,
                Tx,
                Ty,
                typename std::enable_if<
                    std::is_base_of<typename T::RemainderBase, typename std::decay<T>::type>::value
                    && (!std::is_same<typename T::RemainderBase, typename std::decay<T>::type>::value)>::type>
            {
                //-----------------------------------------------------------------------------
                //
                //-----------------------------------------------------------------------------
                ALPAKA_FCT_HOST_ACC static auto remainder(
                    T const & remainder,
                    Tx const & x,
                    Ty const & y)
                -> decltype(
                    math::remainder(
                        static_cast<typename T::RemainderBase const &>(remainder),
                        x,
                        y))
                {
                    // Delegate the call to the base class.
                    return
                        math::remainder(
                            static_cast<typename T::RemainderBase const &>(remainder),
                            x,
                            y);
                }
            };
        }
    }
}