//
// Created by tvito on 9/16/2025.
//

#ifndef BUILDING_H
#define BUILDING_H

#include <vector>

#include "Resource.h"
#include "Structure.h"

class Building : Structure{

    public:
    Building();
    ~Building();

    std::vector<Resource> collectResources();

};



#endif //BUILDING_H
