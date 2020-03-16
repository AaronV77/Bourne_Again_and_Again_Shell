#include "exec_utility.h"

int eu_debugger_flag = 0;

void exec_utility_debugger() {
    eu_debugger_flag = 1;
    return;
}