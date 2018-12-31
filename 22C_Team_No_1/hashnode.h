//
//  hashnode.h
//  hash
//
//  Created by Tommy on 12/3/18.
//  Copyright © 2018 Tommy. All rights reserved.
//

#ifndef hashnode_h
#define hashnode_h

#include <iostream>
#include <string>

class HashNode // class for nodes
{
public:
    int key;
    int value;
    
    HashNode (int k, int v) // constructor using int key and string school name
    {
        key = k;
        value = v;
    }
    
};

#endif /* hashnode_h */
