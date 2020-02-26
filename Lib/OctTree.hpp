#ifndef OCTTREE_HPP
#define OCTTREE_HPP

#include "../Rendering/Models/CubeCluster.hpp"

#include <vector>
#include <array>
#include <iostream>
#include <random>
#include <cmath>

#define eq(x,y) std::abs(x-y) < .00001

/** OctTree
  * This class is intended to store data in an OctTree structure which works
  * by seperating data into 8 octants once too many items are entered into the
  * current octree.
  *
  * Requirements for type T:
  * T should be stored in a 3d coordinate system
  * Every instance of T should have the same size
  * T must contain functions for getX, getY, getZ returning floats
  */

//temp test class
struct myVec3{
  float x, y, z;
  float getX(){return x;}
  float getY(){return y;}
  float getZ(){return z;}

  bool operator==(const myVec3& other){
    return eq(x, other.x) && eq(y, other.y) && eq(z, other.z);
  }
};

struct Bound {
  glm::vec3 a;
  glm::vec3 b;
};

//TODO fix parent usage
template <typename T>
class OctTree{
  private:
    int max_chunk_size = 256;
    int size_ = 0;
    bool leaf = true;
    Bound bound;
    //Point representing the the root of this tree if it isnt a leaf
    float x, y, z;

    OctTree* parent = nullptr;
    std::vector<T*> chunk;
    std::array<OctTree<T>*, 8> octants;


    void split(){
      float avg_x = 0, avg_y = 0, avg_z = 0;
      leaf = false;
      size_ = 0;
      //calculate the center point for this octtree
      //potential item to consider: what if a point is right on this center
      for(T* val: chunk){
        avg_x += val->getX()/max_chunk_size;
        avg_y += val->getY()/max_chunk_size;
        avg_z += val->getZ()/max_chunk_size;
      }
      x = avg_x;
      y = avg_y;
      z = avg_z;
      //allocate child octtrees
      for(int i = 0; i < 8; i++){
        octants[i] = new OctTree<T>(this);
      }
      //Redistribute all the values from this chunk
      for(T* val: chunk){
        this->insert(val);
      }
      chunk.clear();
    }


  public:
    OctTree() = default;
    OctTree(OctTree* p):parent{p}{}
    ~OctTree() = default; //this shouldnt be default TODO
    /**
      * Insert a new item into the OctTree
      */
    void insert(T* val){
      //std::cout  << chunk.size() << std::endl;
      if(leaf){
        chunk.push_back(val);
        size_++;
        if(chunk.size() >= max_chunk_size){
          split();
        }
      }
      else{
        if(val->getX() >=x && val->getY() >=y && val->getZ() >=z)
          octants[0]->insert(val);
        else if(val->getX() >=x && val->getY() >=y && val->getZ() <=z)
          octants[1]->insert(val);
        else if(val->getX() >=x && val->getY() <=y && val->getZ() >=z)
          octants[2]->insert(val);
        else if(val->getX() >=x && val->getY() <=y && val->getZ() <=z)
          octants[3]->insert(val);
        else if(val->getX() <=x && val->getY() >=y && val->getZ() >=z)
          octants[4]->insert(val);
        else if(val->getX() <=x && val->getY() >=y && val->getZ() <=z)
          octants[5]->insert(val);
        else if(val->getX() <=x && val->getY() <=y && val->getZ() >=z)
          octants[6]->insert(val);
        else if(val->getX() <=x && val->getY() <=y && val->getZ() <=z)
          octants[7]->insert(val);
      }
    }

    /**
      *  Remove a certain value from the OctTree
      */
    //void remove(const T& val); TODO
    /**
      * Remove the closest element to a certain point from the OctTree
      */
    void remove(float x, float y, float z);
    /**
      * Return size of current chunk
      */
    int size(){
      return size_;
    }
    /**
      * Return the maximum size of a chunk for this OctTree
      */
    int getMaxChunkSize(){
      return max_chunk_size;
    }
    /**
      * Set the maximum size of a chunk for this OctTree
      */
    void setMaxChunkSize(int max_chunk_size_){
      max_chunk_size = max_chunk_size_;
    }
    /**
      * If this chunk is a leaf then return all data in it.
      * If this chunk is not a leaf return an empty vector
      */
    std::vector<T*> getChunk(){
      return chunk;
    }
    /**
      * Return a vector containing N neighbors that are closest to a certain point
      * return all elements if the octree doesnt contain N neighbors
      */
    std::vector<T*> getNearestNeighbors(float x, float y, float z, int n){

      //this is gonna be the hard one TODO
    }

    std::vector<T*> getChunkAsVector(){
      std::vector<T*> ret;
      if(leaf){
        ret.insert(ret.end(), chunk.begin(), chunk.end());
        return ret;
      }
      else{
        for(OctTree<T>* ot: octants){
          auto clust = ot->getChunkAsVector();
          ret.insert(ret.end(), clust.begin(), clust.end());
        }
        return ret;
      }
    }

    std::vector<CubeCluster*> getChunkAsCubeCluster(){
      std::vector<CubeCluster*> ret;
      if(leaf){
        CubeCluster* cluster = new CubeCluster();
        //cluster->r = rand()/(float)RAND_MAX;
        //cluster->g = rand()/(float)RAND_MAX;
        //cluster->b = rand()/(float)RAND_MAX;
        for(T* val: chunk){
          cluster->add(val->getX(), val->getY(), val->getZ());
        }
        ret.push_back(cluster);
        return ret;
      }
      else{
        for(OctTree<T>* ot: octants){
          auto clust = ot->getChunkAsCubeCluster();
          ret.insert(ret.end(), clust.begin(), clust.end());
        }
        return ret;
      }
    }
};

#endif
