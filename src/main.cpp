
#include <assert.h>
#include "person.hpp"


int main(int argc,char *argv[])
{
	Friend f1{"my best friend", Singer{"rocker", 18}};
	Friend f2{"new friend", string("little girl")};
	Friend f3{"third friend", (int)3};

	Person p2{"p2", 3, Address{"china", "shanghai", "putuo"}};
	Address addr1{"china", "beijing", "wangjing", {p2}};
	Person p1{"p1", 4, addr1, {f1, f2, f3}, string("the kind!")};

    
	json::ANY a;
	auto json = json::dump(p1);
	std::cout << json << std::endl;
	Person ps;
	if(!json::parse(ps ,json)){
        std::cout<<"json::parse failed!"<<std::endl;
    }
    assert(p1 == ps);
	return 0;

}
