let client = require("prom-client");

class worker4Log {
  _ru_utime = new client.Gauge({
    name: "test_metric_name",
    help: "this value hahahahahaha",
    labelNames: ["test", "myname"],
  }); /* user CPU time used */

  _count = 0;

  constructor(worker) {
    this.worker = worker;
  }

  collect() {
    this._count++;
    console.log(this._count);
    this._ru_utime.labels(" testServer", "zxp").set(this._count);
  }
  // _ru_stime; /* system CPU time used */
  // _ru_maxrss; /* maximum resident set size */
  // _ru_ixrss; /* integral shared memory size (X) */
  // _ru_idrss; /* integral unshared data size (X) */
  // _ru_isrss; /* integral unshared stack size (X) */
  // _ru_minflt; /* page reclaims (soft page faults) (X) */
  // _ru_majflt; /* page faults (hard page faults) */
  // _ru_nswap; /* swaps (X) */
  // _ru_inblock; /* block input operations */
  // _ru_oublock; /* block output operations */
  // _ru_msgsnd; /* IPC messages sent (X) */
  // _ru_msgrcv; /* IPC messages received (X) */
  // _ru_nsignals; /* signals received (X) */
  // _ru_nvcsw; /* voluntary context switches (X) */
  // _ru_nivcsw; /* involuntary context switches (X) */
}

//let gateway = new client.Pushgateway('http://127.0.0.1:9091');

class log4 {
  _arrObj = [];
  _gateway = new client.Pushgateway("http://127.0.0.1:9091");

  createWorker(work) {
    let worker = new worker4Log(work);
    this._arrObj.push(worker);

    return worker;
  }

  run(timeout) {
    setInterval(async () => {
      await this._arrObj.forEach((item) => item.collect());
      this._gateway.push({ jobName: "test" }, function (
        err,
        resp,
        body
      ) {
          if (!err) {
              console.log('Succ!');
          }
        //console.log(resp);
      });
    }, timeout);
  }
}

let a = new log4();
exports.log4 = a;
