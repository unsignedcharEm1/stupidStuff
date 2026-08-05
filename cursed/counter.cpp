#include<iostream>
// Unary operator overloading, prefix postfix
class Clock {
	private:
		unsigned int count;
	public:
		Clock() : count(0) {}
		Clock(unsigned int c) : count(c) {}
		// Prefix
		Clock operator ++ () { return Clock(++count); }  // this returns an nameless temporary object
		// Postfix
		Clock operator ++ (int) { return Clock(count++); }
		unsigned int getCount() { return count; }
};
int main() {
	Clock c1, c2; // c1 = 0 so c2 = 0
	c2 = c1++; // c1 = 1 c2 = 0
	std::cout << c2.getCount() << std::endl;
	std::cout << c1.getCount() << std::endl;
	++c1;
	std::cout << c1.getCount() << std::endl; // c1 = 2
}
