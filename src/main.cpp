//
//  main.cpp
//  NaiveSoftwareRenderer
//
//  Created by zhang on 2020/08/17.
//  Copyright © 2020 zhang. All rights reserved.
//

#include <iostream>
#include "window.h"


int main(int argc, char** argv) {
    Window window(argc, argv);
    window.initialize();
    window.run();
    window.close();
    
    return 0;
}

