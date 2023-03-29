#include "BPExec.h"
#include <fcntl.h>
#include <unistd.h>

BPExecResult BPExec::Exec(std::string cmd, bool wait) {
    BPExecResult ret;
    std::string result_str = "";
    int buff_size = 1024*1024;
    char buffer[buff_size];

    FILE* pipe = popen(cmd.c_str(),"r");  
    if (wait) {
        int fd = fileno(pipe);
        int flags = fcntl(fd, F_GETFL);
        fcntl(fd, F_SETFL, flags & ~O_NONBLOCK);
    }
    if (!pipe) {
        ret.exit_code = 1;
        ret.err_str = "BPTools:BPExec:error - Failed to open execution pipe.";
    } else {
        while (!feof(pipe)) {
            if (fgets(buffer, buff_size, pipe) != NULL){
                result_str += buffer;
            }            
        }
        ret.exit_code = 0;
        ret.result = result_str;
    }            
    pclose(pipe); 
    return ret;
}