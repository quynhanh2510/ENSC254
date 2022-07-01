// Copyright (c) Craig Scratchley 2020   wcs (AT) sfu (DOT) ca

#ifndef CARRIED_PRIMITIVE_HPP
#define CARRIED_PRIMITIVE_HPP

#include "primitive.hpp"

namespace primitives {
	
// We want a single carry flag for the whole program as we are simulating the processor's carry flag.
// This flag is not initialized, as a processor's carry flag may be unknown when a program starts
/* extern */ unsigned carry; // does this need to go in a separate file?

// carried_primitive allows arithmetic operations on unsigned ints to update a global carry variable... 
	// simulating a processor's carry flag.
	class carried_primitive : public primitive<unsigned> {

public:
	    template<typename U, typename = std::enable_if_t<
	         std::is_same<unsigned, U>::value || is_promotion<U, unsigned>::value
	    >>
	    constexpr carried_primitive(U const& value) noexcept : primitive<unsigned>(value) {}

		carried_primitive& operator++() noexcept {
			++primitive<unsigned>::m_value;
			carry = primitive<unsigned>::m_value == 0;
			return *this;
		}
		carried_primitive operator++(int) noexcept {
			auto result = carried_primitive(primitive<unsigned>::m_value++);
			carry = primitive<unsigned>::m_value == 0;  // is this correct?
			return result;
		}

//    template<typename U> // U could be another unsigned type, like unsigned char or unsigned short
    carried_primitive& operator+=(unsigned const& other) noexcept {
			// we should be able to deal with any allowable type for other
    	primitive<unsigned>::m_value += other;
//	   primitive<unsigned>::operator+=(other);
	   carry = primitive<unsigned>::m_value < other;
	   return *this;
    }
    carried_primitive& operator+=(carried_primitive const& other) noexcept {
    	primitive<unsigned>::m_value += other.get();
    	carry = primitive<unsigned>::m_value < other.get();
        return *this;
    }
		// borrowing hasn't been programmed yet
//    primitive& operator--() noexcept {
//        --m_value;
//        return *this;
//    }
//    primitive operator--(int) noexcept {
//        return primitive(m_value--);
//    }
//	and for -= operations
	};

//template<typename T> // T could be another unsigned type, like unsigned char or unsigned short
constexpr carried_primitive operator+(carried_primitive const& lhs, unsigned const& rhs) noexcept {
	auto result = carried_primitive(lhs.get() + rhs);
	carry = result < rhs;
	return result;
}
//template<typename T> // T could be another unsigned type, like unsigned char or unsigned short
constexpr carried_primitive operator+(unsigned const& lhs, carried_primitive const& rhs) noexcept {
	auto result = carried_primitive(lhs + rhs.get());
	carry = result < lhs;
	return result;
}
constexpr auto operator+(carried_primitive const& lhs, carried_primitive const& rhs) noexcept {
	auto result = carried_primitive(lhs.get() + rhs.get());
	carry = result < lhs.get();
	return result;
}

// add in more for subtraction operations

}  // namespace primitives

#endif