let client = require("prom-client");

let strurl = "http://192.168.1.127:9091";

// check number
function isNumber(v) {
  return typeof v === "number" && !isNaN(v);
}

const devcfg = {
  initState: {
    name: "btg_dev_initstate:",
    help: "basic info",
    labelNames: ["username"],
  },
  nube: {
    name: "btg_dev_nube",
    help: "basic info",
    labelNames: ["username", "nube"],
  },
  joinState: {
    name: "btg_dev_joinstate:",
    help: "basic info",
    labelNames: ["username", "meetingid"],
  },
};

class devModel {
  constructor() {
    this.initState = new client.Gauge(devcfg.initState);
    this.nube = new client.Gauge(devcfg.nube);
    this.joinState = new client.Gauge(devcfg.joinState);
  }

  static getInst() {
    if (!this.instance) {
      this.instance = new devModel();
    }
    return this.instance;
  }
}

class dev4Log {
  constructor() {
    this._report = devModel.getInst();
  }

  collect(devState) {
    if (!!(typeof newGateway == "undefined")) {
      return;
    }
    if (isNumber(devState.initialState)) {
      this._report.initState
        .labels(devState.userName)
        .set(devState.initialState);
      if (devState.initState == 1) {
        this._report.nube.labels(devState.userName, devState.nube).set(1);
      }
    }
    if (isNumber(devState.joinState)) {
      this._report.initState
        .labels(devState.userName, devState.meetingID)
        .set(devState.joinState);
    }
  }
}

class gateway {
  constructor() {
    this._gateway = new client.Pushgateway(strurl);
  }

  static getInst() {
    if (!this.instance) {
      this.instance = new gateway();
    }
    return this.instance;
  }

  async run() {
    await this._gateway.push({ jobName: "dev" }, function (err, resp, body) {
      if (!err) {
        //  console.log("Succ!");
      } else {
        console.log("push Failed!");
      }
    });
    await client.register.getMetricsAsArray().forEach((elem) => {
      elem.reset();
    });
  }
}

exports.devReport = dev4Log;
exports.gateway = gateway.getInst();
