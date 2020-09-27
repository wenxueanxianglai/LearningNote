#include <string>

using namespace std;

using Counter = unsigned int;
using Gauge = int;
using uint64_t = unsigned long long;
using uv_timeval_t = uint64_t;

// 采集 worker 日志
class worker;
class worker4Log{ 
    typedef struct {        // worker 能提供的数据  WorkerResourceUsage
    uv_timeval_t ru_utime; /* user CPU time used */
    uv_timeval_t ru_stime; /* system CPU time used */
    uint64_t ru_maxrss; /* maximum resident set size */
    uint64_t ru_ixrss; /* integral shared memory size (X) */
    uint64_t ru_idrss; /* integral unshared data size (X) */
    uint64_t ru_isrss; /* integral unshared stack size (X) */
    uint64_t ru_minflt; /* page reclaims (soft page faults) (X) */
    uint64_t ru_majflt; /* page faults (hard page faults) */
    uint64_t ru_nswap; /* swaps (X) */
    uint64_t ru_inblock; /* block input operations */
    uint64_t ru_oublock; /* block output operations */
    uint64_t ru_msgsnd; /* IPC messages sent (X) */
    uint64_t ru_msgrcv; /* IPC messages received (X) */
    uint64_t ru_nsignals; /* signals received (X) */
    uint64_t ru_nvcsw; /* voluntary context switches (X) */
    uint64_t ru_nivcsw; /* involuntary context switches (X) */
} uv_rusage_t;

    bool from(worker wk);
    bool to();          // 这里好像并不需要， 理由，如果仅仅是修改值的话，我们就不需要了
};

// router 日志
class Router;
class router4Log{
    // uri
    string producerId;

public:
    bool from(Router rt);
    bool to();
};


// transport 日志
class transport4Log{
    string type;
    
};

// producer 日志
class producer {
};

// consumer 日志
class consumer {
};

class log4
{
}; 