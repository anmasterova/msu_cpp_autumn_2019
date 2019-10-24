/*LinearAllocator*/

#include <iostream>

class LinearAllocator
{
public:

    LinearAllocator(size_t maxSize){
    	begin = new char[maxSize];
    	ptr = begin;
    	end = begin + maxSize;
    }

    char* alloc(size_t size){
    	if (ptr + size > end)
    		return nullptr;
    	char* cur = ptr;
    	ptr += size;
    	return cur;
    }

    void reset(){
    	ptr = begin;
    }
    
    ~LinearAllocator(){
    	delete[] begin;
    }

private:
	char* begin;
	char* ptr;
	char* end;
};

int main(){
	size_t wanted = 8;
	LinearAllocator test(wanted);

	if (test.alloc(wanted + 1) == nullptr)
		std::cout << "I can't help you\n";
	else
		std::cout << "Everything is OK\n";

	if (test.alloc(wanted - 1) == nullptr)
		std::cout << "I can't help you\n";
	else
		std::cout << "Everything is OK\n";

	if (test.alloc(3) == nullptr)
		std::cout << "I can't help you\n";
	else
		std::cout << "Everything is OK\n";
	test.reset();

	if (test.alloc(wanted) != nullptr)
		std::cout << "Everything is OK\n";
	
	return 0;
}