//
// Created by dongdokee on 2015-11-20.
//

#include "Parameter.h"

Parameter::Parameter() {
    isLoad = false;
}

Parameter* Parameter::getInstance() {
    static Parameter parameter;
    return &parameter;
}
