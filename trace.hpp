#ifndef TRACE_HPP_INCLUDED
#define TRACE_HPP_INCLUDED

#include <sstream>
#include <string>

class cerr_at_end{
    private:
        std::string _msg;
    public:
        cerr_at_end(std::string msg){
            _msg=msg;
        }
        ~cerr_at_end(){
            std::cerr << _msg << std::endl;
        }
};

#define Q(x) #x
#define TRACE static int callid=0; callid++; std::cerr << __PRETTY_FUNCTION__ << ":" << callid << ": START" << std::endl;\
    std::stringstream _ss; _ss << __PRETTY_FUNCTION__ << ":" << callid <<": END"; \
    cerr_at_end _cae(_ss.str())
#define TEXP(x) std::cerr << __PRETTY_FUNCTION__ << ":" << callid << ":" << #x << ":" << x << std::endl
#define TCOM(x) std::cerr << __PRETTY_FUNCTION__ << ":" << callid << ":" << x << std::endl

#endif // TRACE_HPP_INCLUDED
