const {log4} = require('./testlog4')


let work = {
    name: "zxp",
    age: 1
};

log4.createWorker(work);
log4.run(10000);