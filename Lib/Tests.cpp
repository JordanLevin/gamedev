#include "OctTree.hpp"

#include <vector>
#include <algorithm>
#include <cassert>

void testInsert(){
  OctTree<myVec3> data;
  std::vector<myVec3*> original;
  for(int i = 0; i < 150; i += 4){
    for(int j = 0; j < 150; j += 4){
      for(int k = 0; k < 150; k += 4){
        myVec3* v = new myVec3();
        original.push_back(v);
        v->x = i;
        v->y = j;
        v->z = k;
        data.insert(v);
      }
    }
  }

  std::vector<myVec3*> result = data.getChunkAsVector();
  //for(myVec3* v: result){
    //std::cout << v->x << ", " << v->y << ", " << v->z << "\n";
  //}

  for(myVec3* v: original){
    //std::cout << v->x << "- " << v->y << "- " << v->z << "\n";
    //if(std::count(result.begin(), result.end(), v) != 1){
      //std::cout << "BAD\n";
    //}
    assert(std::count(result.begin(), result.end(), v) == 1);
  }
  std::cout << "TEST_INSERT PASSED" << std::endl;
}

int main(){
  testInsert();
}
