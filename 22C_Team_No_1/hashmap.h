//
//  hashmap.h
//  hash
//
//  Created by Tommy on 12/3/18.
//  Copyright © 2018 Tommy. All rights reserved.
//

#ifndef hashmap_h
#define hashmap_h
#include "School.h"
#include "hashnode.h"
#include <iostream>
#include <string>

using namespace std;

int TABLE_SIZE = 27;

class DeletedNode:public HashNode
{
private:
    static DeletedNode *entry;
    DeletedNode():HashNode(-1,-1)
    {}
    
public:
    static DeletedNode *getNode()
    {
        if (entry == NULL)
        {
            entry = new DeletedNode();
        }
        
        return entry;
    }
    
};

DeletedNode *DeletedNode::entry = NULL;

class HashMap
{
private:
    HashNode **htable;
    
public:
    
    HashMap() // constructs table and set to null
    {
        htable = new HashNode* [TABLE_SIZE];
        for (int i = 0; i< TABLE_SIZE; i++)
        {
            htable[i] = NULL;
        }
    }
    
    ~HashMap() // deletes hash table
    {
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            if (htable[i] != NULL)
            {
                delete htable[i];
            }
        }
    }
    
	// Hash Function
    int HashFunc(int key) // hash function key % table size
    {
        return key % TABLE_SIZE;
        
    }
    
	// Inserting
    void insert(int key, int value)
    {
        int hash_value = HashFunc(key);
        int initial = -1;
        int deleteIndex = -1;
        
        while (hash_value != initial  && htable[hash_value] == DeletedNode::getNode() || htable[hash_value] != NULL && htable[hash_value]->key != key)
        {
            if (initial == -1)
            {
                initial = hash_value;
            }
            
            if (htable[hash_value] == DeletedNode::getNode())
            {
                deleteIndex = hash_value;
            }
            
            hash_value = HashFunc(hash_value + 1);
            
        }
        
        if (htable[hash_value] == NULL || hash_value == initial)
        {
            if (deleteIndex != -1)
            {
                htable[deleteIndex] = new HashNode(key,value);
                
            }
            else
            {
                htable[hash_value] = new HashNode(key, value);
                
            }
            
        }
        
        if (initial != hash_value)
        {
            
            if (htable[hash_value] != DeletedNode::getNode())
            {
                
                if (htable[hash_value] != NULL)
                {
                    
                    if (htable[hash_value]->key == key)
                    {
                        
                        htable[hash_value]->value = value;
                    }
                }
            }
            else
            {
                htable[hash_value] = new HashNode(key,value);
            }
        }
    }
    
	// Searching
    int search (int key) // search is just the initial partof insert but we return the hash value
    {
        int hash_value = HashFunc(key);
        int initial = -1;
        
        while (hash_value != initial  && htable[hash_value] == DeletedNode::getNode() || htable[hash_value] != NULL && htable[hash_value]->key != key)
            
        {
            
            if (initial == -1)
            {
                initial = hash_value;
                
            }
            hash_value = HashFunc(hash_value + 1);
            
        }
        
        if (htable[hash_value] == NULL || hash_value == initial)
        {
            return -1;
        }
        
        else
        {
            return htable[hash_value]->value;
        }
        
    }
    
	// Removing
    void remove(int key) // remove is similar to search except we delete instead of returning
    {
        int hash_value = HashFunc(key);
        int initial = -1;
        
        while (hash_value != initial  && htable[hash_value] == DeletedNode::getNode() || htable[hash_value] != NULL && htable[hash_value]->key != key)
        {
            if (initial == -1)
            {
                initial = hash_value;
                
            }
            
            hash_value = HashFunc(hash_value + 1);
            
        }
        
        if ( hash_value != initial && htable[hash_value] != NULL)
        {
            delete htable[hash_value];
            htable[hash_value] = DeletedNode::getNode();
        }
    }
	void print()
	{
		for (int i = 0; i < TABLE_SIZE; i++) {

			if (htable[i] != NULL)
			{

				cout << " " << htable[i]->key << endl;

			}
		}
	}
};

#endif /* hashmap_h */
