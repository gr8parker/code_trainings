
#pragma once

#include <stdexcept>
#include <memory>
#include <iterator>
#include <iostream>
#include <cstddef> //ptrdiff_t
#include <limits> // max_size

namespace nm {

    template<class Type, std::size_t N> 
    class array {
    public:
	typedef Type value_type;
	typedef std::size_t size_type;
	typedef std::ptrdiff_t difference_type;
	typedef Type& reference;
	typedef const Type& const_reference;
	typedef Type* pointer;
	typedef const Type* const_pointer;

		
	array() :
	    _size(N),
	    _data(new Type[N])
	{}
	/* size */
	size_type size() noexcept { return _size; }
	bool empty() noexcept { return !_size; }
	constexpr size_type max_size() { return  std::numeric_limits<size_type>::max(); }
	
	/* access to elemets */
	Type* data() { return _data.get(); }
	Type& at(size_type pos) {
	    if (pos >= _size )
		throw std::out_of_range("array<>::at() : index is out of range");
	    return _data[pos];
	}
	Type& operator[](size_type i) { return _data[i]; }
	Type& front() { return _data[0]; }
        Type& back() { return _data[_size-1];}
	// const 
	const Type& at(size_type pos) const {
	    if (pos >= _size )
		throw std::out_of_range("array<>::at() : index is out of range");
	    return _data[pos];
	}
	const Type& operator[](size_type i) const  { return _data[i]; }
	const Type& front() const { return _data[0]; }
	const Type& back() const { return _data[_size-1];}

	/* fill */
	void fill(const Type& value) {
	    for(int i = 0; i < _size; ++i) {
		_data[i] = value;
	    }
	}

	void swap(array& other) {
	    int tmp;
	    for(int i = 0; i < _size; ++i) {
		tmp = _data[i];
		_data[i] = other[i];
		other[i] = tmp;
	    }
	}

    private:
	std::unique_ptr<Type []> _data;
	size_type _size;	
    };
    
}
