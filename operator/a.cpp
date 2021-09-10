#include <iostream>
#include <algorithm>
#include <numeric>

class rationalNum{
	// this data is hidden form user.
	private:
		int nmr, dmr; // numenator & denominator
	public:
		// these functionality are aviable for user, not implimentation.
		rationalNum():nmr(0),dmr(1){}
		rationalNum(int nmr, int dmr):nmr(nmr),dmr(dmr){}
		rationalNum operator+(rationalNum); // binary 
		rationalNum operator-(rationalNum); // binary
		rationalNum operator*(rationalNum); // binary
		rationalNum operator/(rationalNum); // binary
		bool operator==(rationalNum); // binary
		bool operator!=(rationalNum); // binary
		// functioality with user desidered implimentation is aviable.
		friend void foo(rationalNum);
};

rationalNum rationalNum::operator+(rationalNum other){
	rationalNum c;
	c.nmr = this->nmr * other.dmr + other.nmr * this->dmr;
	c.dmr = this->dmr * other.dmr;
	if( c.nmr == 0 || c.dmr == 0 ){
		c.nmr = 0;
		c.dmr = 1;
		return c;
	}
	int g = std::gcd(c.nmr,c.dmr);
	if( g != 1){
		c.nmr /= g;
		c.dmr /= g;
	}
	return c;
}

rationalNum rationalNum::operator-(rationalNum other){
	rationalNum c;
	c.nmr = this->nmr * other.dmr - other.nmr * this->dmr;
	c.dmr = this->dmr * other.dmr;
	if( c.nmr == 0 || c.dmr == 0 ){
		c.nmr = 0;
		c.dmr = 1;
		return c;
	}
	int g = std::gcd(c.nmr,c.dmr);
	if( g != 1){
		c.nmr /= g;
		c.dmr /= g;
	}
	return c;
}

rationalNum rationalNum::operator*(rationalNum other){
	rationalNum c;
	c.nmr = this->nmr * other.nmr;
	c.dmr = this->dmr * other.dmr;
	if( c.nmr == 0 || c.dmr == 0 ){
		c.nmr = 0;
		c.dmr = 1;
		return c;
	}
	int g = std::gcd(c.nmr,c.dmr);
	if( g != 1){
		c.nmr /= g;
		c.dmr /= g;
	}
	return c;
}

rationalNum rationalNum::operator/(rationalNum other){
	rationalNum c;
	c.nmr = this->nmr * other.dmr;
	c.dmr = this->dmr * other.nmr;
	if( c.nmr == 0 || c.dmr == 0 ){
		c.nmr = 0;
		c.dmr = 1;
		return c;
	}
	int g = std::gcd(c.nmr,c.dmr);
	if( g != 1){
		c.nmr /= g;
		c.dmr /= g;
	}
	return c;
}

bool rationalNum::operator==(rationalNum other){
	return ( this->nmr == other.nmr ) && ( this->dmr == other.dmr );
}

bool rationalNum::operator!=(rationalNum other){
	return ( this->nmr != other.nmr ) || ( this->dmr != other.dmr );
}

// TODO: non member friend function should be implimented by the user.
void foo(rationalNum a){
	std::cout << "Rational Number : " << a.nmr << "/" << a.dmr <<  std::endl;
}


int main(){
	rationalNum a{1,2};
	rationalNum b{1,3};

	rationalNum c;

	c = a + b;
	foo(c);

	c = a - b;
	foo(c);

	c = a * b;
	foo(c);

	c = a / b;
	foo(c);


	
	return 0;
}



