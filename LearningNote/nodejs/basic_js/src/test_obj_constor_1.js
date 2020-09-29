let client = require("prom-client");
const workercfg = {
    utime: {
      name: "mds_worker_utime",
      help: "user CPU time used",
      labelNames: ["adress"]
    },
    stime: {
      name: "mds_worker_stime",
      help: "system CPU time used",
      labelNames: ["adress"]
    },
    maxrss: {
      name: "mds_worker_maxrss",
      help: "maximum resident set size",
      labelNames: ["adress"]
    },
    ixrss: {
      name: "mds_worker_ixrss",
      help: "integral shared memory size (X)",
      labelNames: ["adress"]
    },
    idrss: {
      name: "mds_worker_idrss",
      help: "integral unshared data size",
      labelNames: ["adress"]
    },
    minflt: {
      name: "mds_worker_minflt",
      help: "page reclaims (soft page faults) (X)",
      labelNames: ["adress"]
    },
    majflt: {
      name: "mds_worker_majflt",
      help: "page faults (hard page faults)",
      labelNames: ["adress"]
    },
    nswap: {
      name: "mds_worker_nswap",
      help: "swaps (X)",
      labelNames: ["adress"]
    },
    inblock: {
      name: "mds_worker_inblock",
      help: "block input operations",
      labelNames: ["adress"]
    },
    oublock: {
      name: "mds_worker_oublock",
      help: " block output operations",
      labelNames: ["adress"]
    },
    msgsnd: {
      name: "mds_worker_msgsnd",
      help: "IPC messages sent",
      labelNames: ["adress"]
    },
    msgrcv: {
      name: "mds_worker_msgrcv",
      help: "IPC messages received",
      labelNames: ["adress"]
    },
    nsignals: {
      name: "mds_worker_nsignals",
      help: "signals received",
      labelNames: ["adress"]
    },
    nvcsw: {
      name: "mds_worker_nvcsw",
      help: "voluntary context switches",
      labelNames: ["adress"]
    },
    nivcsw: {
      name: "mds_worker_nivcsw",
      help: "involuntary context switches",
      labelNames: ["adress"]
    }
  };

class work4Report {
    utime = new client.Gauge(workercfg.utime);
    stime = new client.Gauge(workercfg.stime);
    maxrss = new client.Gauge(workercfg.maxrss);
    ixrss = new client.Gauge(workercfg.ixrss);
    idrss = new client.Gauge(workercfg.idrss);
    minflt = new client.Gauge(workercfg.minflt);
    majflt = new client.Gauge(workercfg.majflt);
    nswap = new client.Gauge(workercfg.nswap);
    inblock = new client.Gauge(workercfg.inblock);
    oublock = new client.Gauge(workercfg.oublock);
    msgsnd = new client.Gauge(workercfg.msgsnd);
    msgrcv = new client.Gauge(workercfg.msgrcv);
    nsignals = new client.Gauge(workercfg.nsignals);
    nvcsw = new client.Gauge(workercfg.nvcsw);
    nivcsw = new client.Gauge(workercfg.nivcsw);
}

//let wutime = new client.Gauge(workercfg.stime);
class worker4Log { 
    _work4Report = {
        utime : new client.Gauge(workercfg.utime),
        stime : new client.Gauge(workercfg.stime),
        maxrss : new client.Gauge(workercfg.maxrss),
        ixrss : new client.Gauge(workercfg.ixrss),
        idrss : new client.Gauge(workercfg.idrss),
        minflt : new client.Gauge(workercfg.minflt),
        majflt : new client.Gauge(workercfg.majflt),
        nswap : new client.Gauge(workercfg.nswap),
        inblock : new client.Gauge(workercfg.inblock),
        oublock : new client.Gauge(workercfg.oublock),
        msgsnd : new client.Gauge(workercfg.msgsnd),
        msgrcv : new client.Gauge(workercfg.msgrcv),
        nsignals : new client.Gauge(workercfg.nsignals),
        nvcsw : new client.Gauge(workercfg.nvcsw),
        nivcsw : new client.Gauge(workercfg.nivcsw)
    };
    constructor(worker) {
        this._worker = worker;
       // this._reporter = new work4Report(); 
    }

    myforeach() {
        for (let a in this._work4Report) {
            console.log(this._work4Report[a].name); 
        }
    }
}


let e4 = new worker4Log();
e4.myforeach();

console.log(e4);