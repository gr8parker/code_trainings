
#include <cstddef>
#include <memory>

namespace nm {

    template<class T>
    class vector {
    public:
	typedef size_t size_type;
	typedef T value_type;

	explicit vector() :
	    _data(nullptr),
	    _size(0),
	    _capacity(0)
	{}

	explicit vector(size_type size) :
	    _data(new value_type[size]),
	    _size(0),
	    _capacity(size)
	{}    
	
    private:
	std::unique_ptr<value_type> _data;
	size_type _size;
	size_type _capacity;
    };


} // namespace nm
