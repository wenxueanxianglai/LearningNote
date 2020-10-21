let client = require("prom-client");

/**
 * define some string
 */
const strMdediasoup = "mds_";
const strWorker = "mds_worker_";
const strRouter = "mds_router_";
const strwebrtcTransporter = "mds_transport_webrtc_";

// set default pushgateway
let strJob = "mediasoup";                               // gateway name
let strInstance = "127.0.0.1";                          // gateway id
let strPushgatewayAddress = "http://127.0.0.1:9091";    // pushgateway address  of Prometheus

// check number
function isNumber(v) {
  return typeof v === "number" && !isNaN(v);
}

const workercfg = {
  gatewayInfo: {
    name: "btg_gateway_info",
    help: "contains gatewayId and workId",
    labelNames: ["work_id", "gateway_id"],
  },
  info: {
    name: "mds_worker_info",
    help: "basic info",
    labelNames: ["work_id"],
  },
  utime: {
    name: "mds_worker_utime",
    help: "user CPU time used",
    labelNames: ["work_id"],
  },
  stime: {
    name: "mds_worker_stime",
    help: "system CPU time used",
    labelNames: ["work_id"],
  },
  maxrss: {
    name: "mds_worker_maxrss",
    help: "maximum resident set size",
    labelNames: ["work_id"],
  },
  ixrss: {
    name: "mds_worker_ixrss",
    help: "integral shared memory size (X)",
    labelNames: ["work_id"],
  },
  idrss: {
    name: "mds_worker_idrss",
    help: "integral unshared data size",
    labelNames: ["work_id"],
  },
  minflt: {
    name: "mds_worker_minflt",
    help: "page reclaims (soft page faults) (X)",
    labelNames: ["work_id"],
  },
  majflt: {
    name: "mds_worker_majflt",
    help: "page faults (hard page faults)",
    labelNames: ["work_id"],
  },
  nswap: {
    name: "mds_worker_nswap",
    help: "swaps (X)",
    labelNames: ["work_id"],
  },
  inblock: {
    name: "mds_worker_inblock",
    help: "block input operations",
    labelNames: ["work_id"],
  },
  oublock: {
    name: "mds_worker_oublock",
    help: " block output operations",
    labelNames: ["work_id"],
  },
  msgsnd: {
    name: "mds_worker_msgsnd",
    help: "IPC messages sent",
    labelNames: ["work_id"],
  },
  msgrcv: {
    name: "mds_worker_msgrcv",
    help: "IPC messages received",
    labelNames: ["work_id"],
  },
  nsignals: {
    name: "mds_worker_nsignals",
    help: "signals received",
    labelNames: ["work_id"],
  },
  nvcsw: {
    name: "mds_worker_nvcsw",
    help: "voluntary context switches",
    labelNames: ["work_id"],
  },
  nivcsw: {
    name: "mds_worker_nivcsw",
    help: "involuntary context switches",
    labelNames: ["work_id"],
  },
};

class workerModel {
  constructor() {
    this.gatewayInfo = new client.Gauge(workercfg.gatewayInfo);

    this.info = new client.Gauge(workercfg.info);
    this.utime = new client.Gauge(workercfg.utime);
    this.stime = new client.Gauge(workercfg.stime);
    this.maxrss = new client.Gauge(workercfg.maxrss);
    this.ixrss = new client.Gauge(workercfg.ixrss);
    this.idrss = new client.Gauge(workercfg.idrss);
    this.minflt = new client.Gauge(workercfg.minflt);
    this.majflt = new client.Gauge(workercfg.majflt);
    this.nswap = new client.Gauge(workercfg.nswap);
    this.inblock = new client.Gauge(workercfg.inblock);
    this.oublock = new client.Gauge(workercfg.oublock);
    this.msgsnd = new client.Gauge(workercfg.msgsnd);
    this.msgrcv = new client.Gauge(workercfg.msgrcv);
    this.nsignals = new client.Gauge(workercfg.nsignals);
    this.nvcsw = new client.Gauge(workercfg.nvcsw);
    this.nivcsw = new client.Gauge(workercfg.nivcsw);
  }

  static getInst() {
    if (!this.instance) {
      this.instance = new workerModel();
    }
    return this.instance;
  }
}

class worker4Log {
  constructor(worker) {
    this.id = worker.id;
    this._worker = worker;
    this._report = workerModel.getInst();
  }

  async collect() {
    let usge = await this._worker.getResourceUsage();

    this._report.gatewayInfo
      .labels(this._worker.pid, this._worker.appData.gateWayId)
      .set(1);
    this._report.info.labels(this._worker.pid).set(1);
    if (isNumber(usge.ru_utime))
      this._report.utime.labels(this._worker.pid).set(usge.ru_utime);
    if (isNumber(usge.ru_stime))
      this._report.stime.labels(this._worker.pid).set(usge.ru_stime);
    if (isNumber(usge.ru_maxrss))
      this._report.maxrss.labels(this._worker.pid).set(usge.ru_maxrss);
    if (isNumber(usge.ru_ixrss))
      this._report.ixrss.labels(this._worker.pid).set(usge.ru_ixrss);
    if (isNumber(usge.ru_idrss))
      this._report.idrss.labels(this._worker.pid).set(usge.ru_idrss);
    if (isNumber(usge.ru_minflt))
      this._report.minflt.labels(this._worker.pid).set(usge.ru_minflt);
    if (isNumber(usge.ru_majflt))
      this._report.majflt.labels(this._worker.pid).set(usge.ru_majflt);
    if (isNumber(usge.ru_nswap))
      this._report.nswap.labels(this._worker.pid).set(usge.ru_nswap);
    if (isNumber(usge.ru_inblock))
      this._report.inblock.labels(this._worker.pid).set(usge.ru_inblock);
    if (isNumber(usge.ru_oublock))
      this._report.oublock.labels(this._worker.pid).set(usge.ru_oublock);
    if (isNumber(usge.ru_msgsnd))
      this._report.msgsnd.labels(this._worker.pid).set(usge.ru_msgsnd);
    if (isNumber(usge.ru_msgrcv))
      this._report.msgrcv.labels(this._worker.pid).set(usge.ru_msgrcv);
    if (isNumber(usge.ru_utime))
      this._report.nsignals.labels(this._worker.pid).set(usge.ru_utime);
    if (isNumber(usge.ru_nvcsw))
      this._report.nvcsw.labels(this._worker.pid).set(usge.ru_nvcsw);
    if (isNumber(usge.ru_nivcsw))
      this._report.nivcsw.labels(this._worker.pid).set(usge.ru_nivcsw);
  }
}

// router
const routercfg = {
  meetingInfo: {
    name: "btg_gateway_meetinginfo",
    help: "contains gatewayId and workId",
    labelNames: ["work_id", "router_id", "gateway_id", "meeting_id"]
  }
};

class routerModel {
  static getInst() {
    if (!this.instance) {
      this.instance = new routerModel();
    }
    return this.instance;
  }

  constructor() {
    this.meetingInfo = new client.Gauge(routercfg.meetingInfo);
  }
}

class router4Log {
  constructor(router, workerId, gateWayId=undefined) {
    this.id = router.id;
    this._router = router;
    this._workerId = workerId;
    this._gateWayId = gateWayId;
    this._report = routerModel.getInst();
  }

  async collect() {
    console.log("router collect----");
    this._report.meetingInfo.labels(this._workerId, this.id, this._gateWayId, this._router.appData.meetingId).set(1);
  }
}

const webRtcTransportcfg = {
  userInfo: {
    name: "btg_gateway_userinfo",
    help: "contains gatewayId and workId",
    labelNames: [
      "work_id",
      "router_id",
      "transport_id",
      "gateway_id",
      "meeting_id",
      "user_id",
      "transport_type"
    ],
  },
  info: {
    name: "mds_transport_webrtc_info",
    help: "user CPU time used",
    labelNames: ["work_id", "router_id", "transport_id", "trans_type"],
  },
  bytesReceived: {
    name: "mds_transport_webrtc_bytesreceived",
    help: "user CPU time used",
    labelNames: ["work_id", "router_id", "transport_id", "trans_type"],
  },
  bytesSent: {
    name: "mds_transport_webrtc_bytessent",
    help: "user CPU time used",
    labelNames: ["work_id", "router_id", "transport_id", "trans_type"],
  },
  dtlsState: {
    name: "mds_transport_webrtc_dtlsstate",
    help: "user CPU time used",
    labelNames: ["work_id", "router_id", "transport_id", "trans_type"],
  },
  iceRole: {
    name: "mds_transport_webrtc_icerole",
    help: "user CPU time used",
    labelNames: ["work_id", "router_id", "transport_id", "trans_type"],
  },
  iceSelectedTuple: {
    name: "mds_transport_webrtc_iceselectedtuple",
    help: "user CPU time used",
    labelNames: ["work_id", "router_id", "transport_id", "trans_type"],
  },
  iceState: {
    name: "mds_transport_webrtc_icestate",
    help: "user CPU time used",
    labelNames: ["work_id", "router_id", "transport_id", "trans_type"],
  },
  probationBytesSent: {
    name: "mds_transport_webrtc_probationbytessent",
    help: "user CPU time used",
    labelNames: ["work_id", "router_id", "transport_id", "trans_type"],
  },
  probationSendBitrate: {
    name: "mds_transport_webrtc_probationsendbitrate",
    help: "user CPU time used",
    labelNames: ["work_id", "router_id", "transport_id", "trans_type"],
  },
  recvBitrate: {
    name: "mds_transport_webrtc_recvbitrate",
    help: "user CPU time used",
    labelNames: ["work_id", "router_id", "transport_id", "trans_type"],
  },
  rtpBytesReceived: {
    name: "mds_transport_webrtc_rtpbytesreceived",
    help: "user CPU time used",
    labelNames: ["work_id", "router_id", "transport_id", "trans_type"],
  },
  rtpBytesSent: {
    name: "mds_transport_webrtc_rtpbytessent",
    help: "user CPU time used",
    labelNames: ["work_id", "router_id", "transport_id", "trans_type"],
  },
  rtpRecvBitrate: {
    name: "mds_transport_webrtc_rtprecvbitrate",
    help: "user CPU time used",
    labelNames: ["work_id", "router_id", "transport_id", "trans_type"],
  },
  rtpSendBitrate: {
    name: "mds_transport_webrtc_rtpsendbitrate",
    help: "user CPU time used",
    labelNames: ["work_id", "router_id", "transport_id", "trans_type"],
  },
  rtxBytesReceived: {
    name: "mds_transport_webrtc_rtxbytesreceived",
    help: "user CPU time used",
    labelNames: ["work_id", "router_id", "transport_id", "trans_type"],
  },
  rtxBytesSent: {
    name: "mds_transport_webrtc_rtxbytessent",
    help: "user CPU time used",
    labelNames: ["work_id", "router_id", "transport_id", "trans_type"],
  },
  rtxRecvBitrate: {
    name: "mds_transport_webrtc_rtxrecvbitrate",
    help: "user CPU time used",
    labelNames: ["work_id", "router_id", "transport_id", "trans_type"],
  },
  rtxSendBitrate: {
    name: "mds_transport_webrtc_rtxsendbitrate",
    help: "user CPU time used",
    labelNames: ["work_id", "router_id", "transport_id", "trans_type"],
  },
  sctpState: {
    name: "mds_transport_webrtc_sctpstate",
    help: "user CPU time used",
    labelNames: ["work_id", "router_id", "transport_id", "trans_type"],
  },
  sendBitrate: {
    name: "mds_transport_webrtc_sendbitrate",
    help: "user CPU time used",
    labelNames: ["work_id", "router_id", "transport_id", "trans_type"],
  },
  timestamp: {
    name: "mds_transport_webrtc_timestamp",
    help: "user CPU time used",
    labelNames: ["work_id", "router_id", "transport_id", "trans_type"],
  },
};
class webRtcTransportModel {
  static getInst() {
    if (!this.instance) {
      this.instance = new webRtcTransportModel();
    }
    return this.instance;
  }

  constructor() {
    this.userInfo = new client.Gauge(webRtcTransportcfg.userInfo);
    this.info = new client.Gauge(webRtcTransportcfg.info);
    this.bytesReceived = new client.Gauge(webRtcTransportcfg.bytesReceived);
    this.bytesSent = new client.Gauge(webRtcTransportcfg.bytesSent);
    this.dtlsState = new client.Gauge(webRtcTransportcfg.dtlsState);
    this.iceRole = new client.Gauge(webRtcTransportcfg.iceRole);
    this.iceState = new client.Gauge(webRtcTransportcfg.iceState);
    this.probationBytesSent = new client.Gauge(
      webRtcTransportcfg.probationBytesSent
    );
    this.probationSendBitrate = new client.Gauge(
      webRtcTransportcfg.probationSendBitrate
    );
    this.recvBitrate = new client.Gauge(webRtcTransportcfg.recvBitrate);
    this.rtpBytesReceived = new client.Gauge(
      webRtcTransportcfg.rtpBytesReceived
    );
    this.rtpBytesSent = new client.Gauge(webRtcTransportcfg.rtpBytesSent);
    this.rtpRecvBitrate = new client.Gauge(webRtcTransportcfg.rtpRecvBitrate);
    this.rtpSendBitrate = new client.Gauge(webRtcTransportcfg.rtpSendBitrate);
    this.rtxBytesReceived = new client.Gauge(
      webRtcTransportcfg.rtxBytesReceived
    );
    this.rtxBytesSent = new client.Gauge(webRtcTransportcfg.rtxBytesSent);
    this.rtxRecvBitrate = new client.Gauge(webRtcTransportcfg.rtxRecvBitrate);
    this.rtxSendBitrate = new client.Gauge(webRtcTransportcfg.rtxSendBitrate);
    this.sctpState = new client.Gauge(webRtcTransportcfg.sctpState);
    this.sendBitrate = new client.Gauge(webRtcTransportcfg.sendBitrate);
    //this.timestamp = new client.Gauge(webRtcTransportcfg.timestamp);
  }

  collect(rtcData, workId, routerId, gateWayId, meetingId, userId, transType) {
    rtcData.forEach((item) => {
      this.userInfo
        .labels(workId, routerId, item.transportId, gateWayId, meetingId, userId, transType)
        .set(1);

      this.info.labels(workId, routerId, item.transportId, item.type).set(1);
      if (isNumber(item.bytesReceived))
        this.bytesReceived
          .labels(workId, routerId, item.transportId, item.type)
          .set(item.bytesReceived);
      if (isNumber(item.bytesSent))
        this.bytesSent
          .labels(workId, routerId, item.transportId, item.type)
          .set(item.bytesSent);
      //if( isNumber(item.dtlsState)) this.dtlsState.labels(workId, routerId, item.transportId, item.type).set(item.dtlsState);
      //if( isNumber(item.iceRole)) this.iceRole.labels(workId, routerId, item.transportId, item.type).set(item.iceRole);
      //if( isNumber(item.iceState)) this.iceState.labels(workId, routerId, item.transportId, item.type).set(item.iceState);
      if (isNumber(item.probationBytesSent))
        this.probationBytesSent
          .labels(workId, routerId, item.transportId, item.type)
          .set(item.probationBytesSent);
      if (isNumber(item.probationSendBitrate))
        this.probationSendBitrate
          .labels(workId, routerId, item.transportId, item.type)
          .set(item.probationSendBitrate);
      if (isNumber(item.recvBitrate))
        this.recvBitrate
          .labels(workId, routerId, item.transportId, item.type)
          .set(item.recvBitrate);
      if (isNumber(item.rtpBytesReceived))
        this.rtpBytesReceived
          .labels(workId, routerId, item.transportId, item.type)
          .set(item.rtpBytesReceived);
      if (isNumber(item.rtpBytesSent))
        this.rtpBytesSent
          .labels(workId, routerId, item.transportId, item.type)
          .set(item.rtpBytesSent);
      if (isNumber(item.rtpRecvBitrate))
        this.rtpRecvBitrate
          .labels(workId, routerId, item.transportId, item.type)
          .set(item.rtpRecvBitrate);
      if (isNumber(item.rtpSendBitrate))
        this.rtpSendBitrate
          .labels(workId, routerId, item.transportId, item.type)
          .set(item.rtpSendBitrate);
      if (isNumber(item.rtxBytesReceived))
        this.rtxBytesReceived
          .labels(workId, routerId, item.transportId, item.type)
          .set(item.rtxBytesReceived);
      if (isNumber(item.rtxBytesSent))
        this.rtxBytesSent
          .labels(workId, routerId, item.transportId, item.type)
          .set(item.rtxBytesSent);
      if (isNumber(item.rtxRecvBitrate))
        this.rtxRecvBitrate
          .labels(workId, routerId, item.transportId, item.type)
          .set(item.rtxRecvBitrate);
      if (isNumber(item.rtxSendBitrate))
        this.rtxSendBitrate
          .labels(workId, routerId, item.transportId, item.type)
          .set(item.rtxSendBitrate);
      //if( isNumber(item.sctpState)) this.sctpState.labels(workId, routerId, item.transportId, item.type).set(item.sctpState);
      if (isNumber(item.sendBitrate))
        this.sendBitrate
          .labels(workId, routerId, item.transportId, item.type)
          .set(item.sendBitrate);
      // if (isNumber(item.timestamp))
      //   this.timestamp
      //     .labels(workId, routerId, item.transportId, item.type)
      //     .set(item.timestamp);
    });
  }
}

// plain
const plainTransportcfg = {
  userInfo: {
    name: "btg_gateway_userinfo",
    help: "contains gatewayId and workId",
    labelNames: [
      "work_id",
      "router_id",
      "transport_id",
      "gateway_id",
      "meeting_id",
      "user_id",
      "transport_type"
    ],
  },
  info: {
    name: "mds_transport_plain_info",
    help: "user CPU time used",
    labelNames: ["work_id", "router_id", "transport_id"],
  },
  bytesReceived: {
    name: "mds_transport_plain_bytesreceived",
    help: "user CPU time used",
    labelNames: ["work_id", "router_id", "transport_id"],
  },
  bytesSent: {
    name: "mds_transport_plain_bytessent",
    help: "user CPU time used",
    labelNames: ["work_id", "router_id", "transport_id"],
  },
  comedia: {
    name: "mds_transport_plain_comedia",
    help: "user CPU time used",
    labelNames: ["work_id", "router_id", "transport_id"],
  },
  rtcpMux: {
    name: "mds_transport_plain_rtcpmux",
    help: "user CPU time used",
    labelNames: ["work_id", "router_id", "transport_id"],
  },
  probationBytesSent: {
    name: "mds_transport_plain_probationbytessent",
    help: "user CPU time used",
    labelNames: ["work_id", "router_id", "transport_id"],
  },
  probationSendBitrate: {
    name: "mds_transport_plain_probationsendbitrate",
    help: "user CPU time used",
    labelNames: ["work_id", "router_id", "transport_id"],
  },
  recvBitrate: {
    name: "mds_transport_plain_recvbitrate",
    help: "user CPU time used",
    labelNames: ["work_id", "router_id", "transport_id"],
  },
  rtpBytesReceived: {
    name: "mds_transport_plain_rtpbytesreceived",
    help: "user CPU time used",
    labelNames: ["work_id", "router_id", "transport_id"],
  },
  rtpBytesSent: {
    name: "mds_transport_plain_rtpbytessent",
    help: "user CPU time used",
    labelNames: ["work_id", "router_id", "transport_id"],
  },
  rtpRecvBitrate: {
    name: "mds_transport_plain_rtprecvbitrate",
    help: "user CPU time used",
    labelNames: ["work_id", "router_id", "transport_id"],
  },
  rtpSendBitrate: {
    name: "mds_transport_plain_rtpsendbitrate",
    help: "user CPU time used",
    labelNames: ["work_id", "router_id", "transport_id"],
  },
  rtxBytesReceived: {
    name: "mds_transport_plain_rtxbytesreceived",
    help: "user CPU time used",
    labelNames: ["work_id", "router_id", "transport_id"],
  },
  rtxBytesSent: {
    name: "mds_transport_plain_rtxbytessent",
    help: "user CPU time used",
    labelNames: ["work_id", "router_id", "transport_id"],
  },
  rtxRecvBitrate: {
    name: "mds_transport_plain_rtxrecvbitrate",
    help: "user CPU time used",
    labelNames: ["work_id", "router_id", "transport_id"],
  },
  rtxSendBitrate: {
    name: "mds_transport_plain_rtxsendbitrate",
    help: "user CPU time used",
    labelNames: ["work_id", "router_id", "transport_id"],
  },
  sendBitrate: {
    name: "mds_transport_plain_sendbitrate",
    help: "user CPU time used",
    labelNames: ["work_id", "router_id", "transport_id"],
  },
  timestamp: {
    name: "mds_transport_plain_timestamp",
    help: "user CPU time used",
    labelNames: ["work_id", "router_id", "transport_id"],
  },
  transportId: {
    name: "mds_transport_plain_transportid",
    help: "user CPU time used",
    labelNames: ["work_id", "router_id", "transport_id"],
  },
};
// plain
class plainTransportModel {
  static getInst() {
    if (!this.instance) {
      this.instance = new plainTransportModel();
    }
    return this.instance;
  }
  constructor() {
    this.info = new client.Gauge(plainTransportcfg.info);
    this.bytesReceived = new client.Gauge(plainTransportcfg.bytesReceived);
    this.bytesSent = new client.Gauge(plainTransportcfg.bytesSent);
    this.comedia = new client.Gauge(plainTransportcfg.comedia);
    this.rtcpMux = new client.Gauge(plainTransportcfg.rtcpMux);
    this.probationBytesSent = new client.Gauge(
      plainTransportcfg.probationBytesSent
    );
    this.probationSendBitrate = new client.Gauge(
      plainTransportcfg.probationSendBitrate
    );
    this.recvBitrate = new client.Gauge(plainTransportcfg.recvBitrate);
    this.rtpBytesReceived = new client.Gauge(
      plainTransportcfg.rtpBytesReceived
    );
    this.rtpBytesSent = new client.Gauge(plainTransportcfg.rtpBytesSent);
    this.rtpRecvBitrate = new client.Gauge(plainTransportcfg.rtpRecvBitrate);
    this.rtpSendBitrate = new client.Gauge(plainTransportcfg.rtpSendBitrate);
    this.rtxBytesReceived = new client.Gauge(
      plainTransportcfg.rtxBytesReceived
    );
    this.rtxBytesSent = new client.Gauge(plainTransportcfg.rtxBytesSent);
    this.rtxRecvBitrate = new client.Gauge(plainTransportcfg.rtxRecvBitrate);
    this.rtxSendBitrate = new client.Gauge(plainTransportcfg.rtxSendBitrate);
    this.sendBitrate = new client.Gauge(plainTransportcfg.sendBitrate);
    this.timestamp = new client.Gauge(plainTransportcfg.timestamp);
  }

  collect(plainData, workId, routerId) {
    plainData.forEach((item) => {
      this.info.labels(workId, routerId, item.transportId, item.type).set(1);
      if (isNumber(item.bytesReceived))
        this.bytesReceived
          .labels(workId, routerId, item.transportId, item.type)
          .set(item.bytesReceived);
      if (isNumber(item.bytesSent))
        this.bytesSent
          .labels(workId, routerId, item.transportId, item.type)
          .set(item.bytesSent);
      //if( isNumber(item.comedia)) this.comedia.labels(workId, routerId, item.transportId, item.type).set(item.comedia);
      //if( isNumber(item.rtcpMux)) this.rtcpMux.labels(workId, routerId, item.transportId, item.type).set(item.rtcpMux);
      if (isNumber(item.probationBytesSent))
        this.probationBytesSent
          .labels(workId, routerId, item.transportId, item.type)
          .set(item.probationBytesSent);
      if (isNumber(item.probationSendBitrate))
        this.probationSendBitrate
          .labels(workId, routerId, item.transportId, item.type)
          .set(item.probationSendBitrate);
      if (isNumber(item.recvBitrate))
        this.recvBitrate
          .labels(workId, routerId, item.transportId, item.type)
          .set(item.recvBitrate);
      if (isNumber(item.rtpBytesReceived))
        this.rtpBytesReceived
          .labels(workId, routerId, item.transportId, item.type)
          .set(item.rtpBytesReceived);
      if (isNumber(item.rtpBytesSent))
        this.rtpBytesSent
          .labels(workId, routerId, item.transportId, item.type)
          .set(item.rtpBytesSent);
      if (isNumber(item.rtpRecvBitrate))
        this.rtpRecvBitrate
          .labels(workId, routerId, item.transportId, item.type)
          .set(item.rtpRecvBitrate);
      if (isNumber(item.rtpSendBitrate))
        this.rtpSendBitrate
          .labels(workId, routerId, item.transportId, item.type)
          .set(item.rtpSendBitrate);
      if (isNumber(item.rtxBytesReceived))
        this.rtxBytesReceived
          .labels(workId, routerId, item.transportId, item.type)
          .set(item.rtxBytesReceived);
      if (isNumber(item.rtxBytesSent))
        this.rtxBytesSent
          .labels(workId, routerId, item.transportId, item.type)
          .set(item.rtxBytesSent);
      if (isNumber(item.rtxRecvBitrate))
        this.rtxRecvBitrate
          .labels(workId, routerId, item.transportId, item.type)
          .set(item.rtxRecvBitrate);
      if (isNumber(item.rtxSendBitrate))
        this.rtxSendBitrate
          .labels(workId, routerId, item.transportId, item.type)
          .set(item.rtxSendBitrate);
      if (isNumber(item.sendBitrate))
        this.sendBitrate
          .labels(workId, routerId, item.transportId, item.type)
          .set(item.sendBitrate);
    });
  }
}

// PipeTransport
class pipeTransportModel {
  constructor() {
    //utime = new client.Gauge(workercfg.utime);
  }

  static getInst() {
    if (!this.instance) {
      this.instance = new pipeTransportModel();
    }
    return this.instance;
  }
}

// DirectTransport
class directTransportModel {
  constructor() {
    //utime = new client.Gauge(workercfg.utime);
  }

  static getInst() {
    if (!this.instance) {
      this.instance = new directTransportModel();
    }
    return this.instance;
  }

  setData(statData) {}
}

class transport4Log {
  constructor(transport, workerId, routerId, gateWayId, meetingId) {
    this.id = transport.id;
    this._transport = transport;
    this._workerId = workerId;
    this._routerId = routerId;
    this._gateWayId = gateWayId;
    this._meetingId = meetingId;
    this._userId = transport.appData.userId;
    this._type = transport.appData.type;
    console.log(
      "[transport4Log] :",
      transport.constructor.name,
      transport.appData
    );
    this._report = (() => {
      switch (transport.constructor.name) {
        case "WebRtcTransport":
          return webRtcTransportModel.getInst();
        case "PlainTransport":
          return plainTransportModel.getInst();
        case "PipeTransport":
        // return PipeTransportModel.getInst();
        case "DirectTransport":
        // return directTransportModel.getInst();
        default:
          console.log("unknow transporter: ", transport.constructor.name);
      }
    })();
  }

  async collect() {
    let statData = await this._transport.getStats();
    await this._report.collect(statData, this._workerId, this._routerId,  this._gateWayId, this._meetingId, this._userId, this._type);
  }
}

// producer
const producercfg = {
  info: {
    name: "mds_producer_info",
    help: "can not",
    labelNames: [
      "work_id",
      "router_id",
      "transport_id",
      "producer_id",
      "producer_type",
      "ssrc",
      "mimetype", "transport_type"
    ],
  },
  bitrate: {
    name: "mds_producer_bitrate",
    help: "can not",
    labelNames: [
      "work_id",
      "router_id",
      "transport_id",
      "producer_id",
      "producer_type",
      "ssrc",
      "mimetype", "transport_type"
    ],
  },
  bitrateByLayer: {
    name: "mds_producer_bitratebylayer",
    help: "can not",
    labelNames: [
      "work_id",
      "router_id",
      "transport_id",
      "producer_id",
      "producer_type",
      "ssrc",
      "mimetype", "transport_type"
    ],
  },
  byteCount: {
    name: "mds_producer_bytecount",
    help: "can not",
    labelNames: [
      "work_id",
      "router_id",
      "transport_id",
      "producer_id",
      "producer_type",
      "ssrc",
      "mimetype", "transport_type"
    ],
  },
  firCount: {
    name: "mds_producer_fircount",
    help: "can not",
    labelNames: [
      "work_id",
      "router_id",
      "transport_id",
      "producer_id",
      "producer_type",
      "ssrc",
      "mimetype", "transport_type"
    ],
  },
  fractionLost: {
    name: "mds_producer_fractionlost",
    help: "can not",
    labelNames: [
      "work_id",
      "router_id",
      "transport_id",
      "producer_id",
      "producer_type",
      "ssrc",
      "mimetype", "transport_type"
    ],
  },
  jitter: {
    name: "mds_producer_jitter",
    help: "can not",
    labelNames: [
      "work_id",
      "router_id",
      "transport_id",
      "producer_id",
      "producer_type",
      "ssrc",
      "mimetype", "transport_type"
    ],
  },
  kind: {
    name: "mds_producer_kind",
    help: "can not",
    labelNames: [
      "work_id",
      "router_id",
      "transport_id",
      "producer_id",
      "producer_type",
      "ssrc",
      "mimetype", "transport_type"
    ],
  },
  mimeType: {
    name: "mds_producer_mimetype",
    help: "can not",
    labelNames: [
      "work_id",
      "router_id",
      "transport_id",
      "producer_id",
      "producer_type",
      "ssrc",
      "mimetype", "transport_type"
    ],
  },
  nackCount: {
    name: "mds_producer_nackcount",
    help: "can not",
    labelNames: [
      "work_id",
      "router_id",
      "transport_id",
      "producer_id",
      "producer_type",
      "ssrc",
      "mimetype", "transport_type"
    ],
  },
  nackPacketCount: {
    name: "mds_producer_nackpacketcount",
    help: "can not",
    labelNames: [
      "work_id",
      "router_id",
      "transport_id",
      "producer_id",
      "producer_type",
      "ssrc",
      "mimetype", "transport_type"
    ],
  },
  packetCount: {
    name: "mds_producer_packetcount",
    help: "can not",
    labelNames: [
      "work_id",
      "router_id",
      "transport_id",
      "producer_id",
      "producer_type",
      "ssrc",
      "mimetype", "transport_type"
    ],
  },
  packetsDiscarded: {
    name: "mds_producer_packetsdiscarded",
    help: "can not",
    labelNames: [
      "work_id",
      "router_id",
      "transport_id",
      "producer_id",
      "producer_type",
      "ssrc",
      "mimetype", "transport_type"
    ],
  },
  packetsLost: {
    name: "mds_producer_packetslost",
    help: "can not",
    labelNames: [
      "work_id",
      "router_id",
      "transport_id",
      "producer_id",
      "producer_type",
      "ssrc",
      "mimetype", "transport_type"
    ],
  },
  packetsRepaired: {
    name: "mds_producer_packetsrepaired",
    help: "can not",
    labelNames: [
      "work_id",
      "router_id",
      "transport_id",
      "producer_id",
      "producer_type",
      "ssrc",
      "mimetype", "transport_type"
    ],
  },
  packetsRetransmitted: {
    name: "mds_producer_packetsretransmitted",
    help: "can not",
    labelNames: [
      "work_id",
      "router_id",
      "transport_id",
      "producer_id",
      "producer_type",
      "ssrc",
      "mimetype", "transport_type"
    ],
  },
  pliCount: {
    name: "mds_producer_plicount",
    help: "can not",
    labelNames: [
      "work_id",
      "router_id",
      "transport_id",
      "producer_id",
      "producer_type",
      "ssrc",
      "mimetype", "transport_type"
    ],
  },
  roundTripTime: {
    name: "mds_producer_roundtriptime",
    help: "can not",
    labelNames: [
      "work_id",
      "router_id",
      "transport_id",
      "producer_id",
      "producer_type",
      "ssrc",
      "mimetype", "transport_type"
    ],
  },
  rtxSsrc: {
    name: "mds_producer_rtxssrc",
    help: "can not",
    labelNames: [
      "work_id",
      "router_id",
      "transport_id",
      "producer_id",
      "producer_type",
      "ssrc",
      "mimetype", "transport_type"
    ],
  },
  score: {
    name: "mds_producer_score",
    help: "can not",
    labelNames: [
      "work_id",
      "router_id",
      "transport_id",
      "producer_id",
      "producer_type",
      "ssrc",
      "mimetype", "transport_type"
    ],
  },
  ssrc: {
    name: "mds_producer_ssrc",
    help: "can not",
    labelNames: [
      "work_id",
      "router_id",
      "transport_id",
      "producer_id",
      "producer_type",
      "ssrc",
      "mimetype", "transport_type"
    ],
  },
  timestamp: {
    name: "mds_producer_timestamp",
    help: "can not",
    labelNames: [
      "work_id",
      "router_id",
      "transport_id",
      "producer_id",
      "producer_type",
      "ssrc",
      "mimetype", "transport_type"
    ],
  },
  type: {
    name: "mds_producer_type",
    help: "can not",
    labelNames: [
      "work_id",
      "router_id",
      "transport_id",
      "producer_id",
      "producer_type",
      "ssrc",
      "mimetype", "transport_type"
    ],
  },
};

class producerModel {
  static getInst() {
    if (!this.instance) {
      this.instance = new producerModel();
    }
    return this.instance;
  }

  constructor() {
    this.info = new client.Gauge(producercfg.info);
    this.bitrate = new client.Gauge(producercfg.bitrate);
    this.bitrateByLayer = new client.Gauge(producercfg.bitrateByLayer);
    this.byteCount = new client.Gauge(producercfg.byteCount);
    this.firCount = new client.Gauge(producercfg.firCount);
    this.fractionLost = new client.Gauge(producercfg.fractionLost);
    this.jitter = new client.Gauge(producercfg.jitter);
    this.kind = new client.Gauge(producercfg.kind);
    this.mimeType = new client.Gauge(producercfg.mimeType);
    this.nackCount = new client.Gauge(producercfg.nackCount);
    this.nackPacketCount = new client.Gauge(producercfg.nackPacketCount);
    this.packetCount = new client.Gauge(producercfg.packetCount);
    this.packetsDiscarded = new client.Gauge(producercfg.packetsDiscarded);
    this.packetsLost = new client.Gauge(producercfg.packetsLost);
    this.packetsRepaired = new client.Gauge(producercfg.packetsRepaired);
    this.packetsRetransmitted = new client.Gauge(
      producercfg.packetsRetransmitted
    );
    this.pliCount = new client.Gauge(producercfg.pliCount);
    this.roundTripTime = new client.Gauge(producercfg.roundTripTime);
    this.rtxSsrc = new client.Gauge(producercfg.rtxSsrc);
    this.score = new client.Gauge(producercfg.score);
    this.ssrc = new client.Gauge(producercfg.ssrc);
    this.timestamp = new client.Gauge(producercfg.timestamp);
    this.type = new client.Gauge(producercfg.type);
  }

  collect(produceData, workId, routerId, transportId, producerId, transportType) {
    produceData.forEach((item) => {
      this.info
        .labels(
          workId,
          routerId,
          transportId,
          producerId,
          item.type,
          item.ssrc,
          item.mimeType, transportType
        )
        .set(1);
      if (isNumber(item.bitrate))
        this.bitrate
          .labels(
            workId,
            routerId,
            transportId,
            producerId,
            item.type,
            item.ssrc,
            item.mimeType, transportType
          )
          .set(item.bitrate);
      //if( isNumber(item.bitrateByLayer)) this.bitrateByLayer.labels(workId, routerId, transportId,producerId,item.type).set(item.bitrateByLayer);
      if (isNumber(item.byteCount))
        this.byteCount
          .labels(
            workId,
            routerId,
            transportId,
            producerId,
            item.type,
            item.ssrc,
            item.mimeType, transportType
          )
          .set(item.byteCount);
      if (isNumber(item.firCount))
        this.firCount
          .labels(
            workId,
            routerId,
            transportId,
            producerId,
            item.type,
            item.ssrc,
            item.mimeType, transportType
          )
          .set(item.firCount);
      if (isNumber(item.fractionLost))
        this.fractionLost
          .labels(
            workId,
            routerId,
            transportId,
            producerId,
            item.type,
            item.ssrc,
            item.mimeType, transportType
          )
          .set(item.fractionLost);
      if (isNumber(item.jitter))
        this.jitter
          .labels(
            workId,
            routerId,
            transportId,
            producerId,
            item.type,
            item.ssrc,
            item.mimeType, transportType
          )
          .set(item.jitter);
      //if( isNumber(item.kind)) this.kind.labels(workId, routerId, transportId,producerId,item.type).set(item.kind);
      //if( isNumber(item.mimeType, transportType)) this.mimeType.labels(workId, routerId, transportId,producerId,item.type).set(item.mimeType, transportType);
      if (isNumber(item.nackCount))
        this.nackCount
          .labels(
            workId,
            routerId,
            transportId,
            producerId,
            item.type,
            item.ssrc,
            item.mimeType, transportType
          )
          .set(item.nackCount);
      if (isNumber(item.nackPacketCount))
        this.nackPacketCount
          .labels(
            workId,
            routerId,
            transportId,
            producerId,
            item.type,
            item.ssrc,
            item.mimeType, transportType
          )
          .set(item.nackPacketCount);
      if (isNumber(item.packetCount))
        this.packetCount
          .labels(
            workId,
            routerId,
            transportId,
            producerId,
            item.type,
            item.ssrc,
            item.mimeType, transportType
          )
          .set(item.packetCount);
      if (isNumber(item.packetsDiscarded))
        this.packetsDiscarded
          .labels(
            workId,
            routerId,
            transportId,
            producerId,
            item.type,
            item.ssrc,
            item.mimeType, transportType
          )
          .set(item.packetsDiscarded);
      if (isNumber(item.packetsLost))
        this.packetsLost
          .labels(
            workId,
            routerId,
            transportId,
            producerId,
            item.type,
            item.ssrc,
            item.mimeType, transportType
          )
          .set(item.packetsLost);
      if (isNumber(item.packetsRepaired))
        this.packetsRepaired
          .labels(
            workId,
            routerId,
            transportId,
            producerId,
            item.type,
            item.ssrc,
            item.mimeType, transportType
          )
          .set(item.packetsRepaired);
      if (isNumber(item.packetsRetransmitted))
        this.packetsRetransmitted
          .labels(
            workId,
            routerId,
            transportId,
            producerId,
            item.type,
            item.ssrc,
            item.mimeType, transportType
          )
          .set(item.packetsRetransmitted);
      if (isNumber(item.pliCount))
        this.pliCount
          .labels(
            workId,
            routerId,
            transportId,
            producerId,
            item.type,
            item.ssrc,
            item.mimeType, transportType
          )
          .set(item.pliCount);
      //  if( isNumber(item.roundTripTime)) this.roundTripTime.labels(transportId, producerId, item.type).set(item.roundTripTime);
      if (isNumber(item.rtxSsrc))
        this.rtxSsrc
          .labels(
            workId,
            routerId,
            transportId,
            producerId,
            item.type,
            item.ssrc,
            item.mimeType, transportType
          )
          .set(item.rtxSsrc);
      if (isNumber(item.score))
        this.score
          .labels(
            workId,
            routerId,
            transportId,
            producerId,
            item.type,
            item.ssrc,
            item.mimeType, transportType
          )
          .set(item.score);
      if (isNumber(item.ssrc))
        this.ssrc
          .labels(
            workId,
            routerId,
            transportId,
            producerId,
            item.type,
            item.ssrc,
            item.mimeType, transportType
          )
          .set(item.ssrc);
      if (isNumber(item.timestamp))
        this.timestamp
          .labels(
            workId,
            routerId,
            transportId,
            producerId,
            item.type,
            item.ssrc,
            item.mimeType, transportType
          )
          .set(item.timestamp);
    });
  }
}

class producer4Log {
  constructor(producer, workerId, routerId, tranportId, transportType) {
    this.id = producer.id;
    this._producer = producer;
    this._workerId = workerId;
    this._routerId = routerId;
    this._transportId = tranportId;
    this._report = producerModel.getInst();
    this._transportType = transportType;
  }

  async collect() {
    let statData;
    try {
      statData = await this._producer.getStats();
    } catch (error) {
      console.log(error, "Error produce");
      return;
    }

    this._report.collect(
      statData,
      this._workerId,
      this._routerId,
      this._transportId,
      this._producer.id,
      this._transportType
    );
  }
}

// consumer
const consumercfg = { 
  subscribeInfo: {
    name: "btg_gateway_subscribeinfo",
    help: "can not",
    labelNames: [
      "work_id",
      "router_id",
      "transport_id",
      "consumer_id",
      "user_id",
      "subcribe_id",
      "transport_type"
    ],
  },
  info: {
    name: "mds_consumer_info",
    help: "can not",
    labelNames: [
      "work_id",
      "router_id",
      "transport_id",
      "consumer_id",
      "consumer_type",
      "ssrc",
      "mimetype",
    ],
  },
  bitrate: {
    name: "mds_consumer_bitrate",
    help: "can not",
    labelNames: [
      "work_id",
      "router_id",
      "transport_id",
      "consumer_id",
      "consumer_type",
      "ssrc",
      "mimetype",
    ],
  },
  byteCount: {
    name: "mds_consumer_bytecount",
    help: "can not",
    labelNames: [
      "work_id",
      "router_id",
      "transport_id",
      "consumer_id",
      "consumer_type",
      "ssrc",
      "mimetype",
    ],
  },
  firCount: {
    name: "mds_consumer_fircount",
    help: "can not",
    labelNames: [
      "work_id",
      "router_id",
      "transport_id",
      "consumer_id",
      "consumer_type",
      "ssrc",
      "mimetype",
    ],
  },
  fractionLost: {
    name: "mds_consumer_fractionlost",
    help: "can not",
    labelNames: [
      "work_id",
      "router_id",
      "transport_id",
      "consumer_id",
      "consumer_type",
      "ssrc",
      "mimetype",
    ],
  },
  jitter: {
    name: "mds_consumer_jitter",
    help: "can not",
    labelNames: [
      "work_id",
      "router_id",
      "transport_id",
      "consumer_id",
      "consumer_type",
      "ssrc",
      "mimetype",
    ],
  },
  kind: {
    name: "mds_consumer_kind",
    help: "can not",
    labelNames: [
      "work_id",
      "router_id",
      "transport_id",
      "consumer_id",
      "consumer_type",
      "ssrc",
      "mimetype",
    ],
  },
  mimeType: {
    name: "mds_consumer_mimetype",
    help: "can not",
    labelNames: [
      "work_id",
      "router_id",
      "transport_id",
      "consumer_id",
      "consumer_type",
      "ssrc",
      "mimetype",
    ],
  },
  nackCount: {
    name: "mds_consumer_nackcount",
    help: "can not",
    labelNames: [
      "work_id",
      "router_id",
      "transport_id",
      "consumer_id",
      "consumer_type",
      "ssrc",
      "mimetype",
    ],
  },
  nackPacketCount: {
    name: "mds_consumer_nackpacketcount",
    help: "can not",
    labelNames: [
      "work_id",
      "router_id",
      "transport_id",
      "consumer_id",
      "consumer_type",
      "ssrc",
      "mimetype",
    ],
  },
  packetCount: {
    name: "mds_consumer_packetcount",
    help: "can not",
    labelNames: [
      "work_id",
      "router_id",
      "transport_id",
      "consumer_id",
      "consumer_type",
      "ssrc",
      "mimetype",
    ],
  },
  packetsDiscarded: {
    name: "mds_consumer_packetsdiscarded",
    help: "can not",
    labelNames: [
      "work_id",
      "router_id",
      "transport_id",
      "consumer_id",
      "consumer_type",
      "ssrc",
      "mimetype",
    ],
  },
  packetsLost: {
    name: "mds_consumer_packetslost",
    help: "can not",
    labelNames: [
      "work_id",
      "router_id",
      "transport_id",
      "consumer_id",
      "consumer_type",
      "ssrc",
      "mimetype",
    ],
  },
  packetsRepaired: {
    name: "mds_consumer_packetsrepaired",
    help: "can not",
    labelNames: [
      "work_id",
      "router_id",
      "transport_id",
      "consumer_id",
      "consumer_type",
      "ssrc",
      "mimetype",
    ],
  },
  packetsRetransmitted: {
    name: "mds_consumer_packetsretransmitted",
    help: "can not",
    labelNames: [
      "work_id",
      "router_id",
      "transport_id",
      "consumer_id",
      "consumer_type",
      "ssrc",
      "mimetype",
    ],
  },
  pliCount: {
    name: "mds_consumer_plicount",
    help: "can not",
    labelNames: [
      "work_id",
      "router_id",
      "transport_id",
      "consumer_id",
      "consumer_type",
      "ssrc",
      "mimetype",
    ],
  },
  rtxSsrc: {
    name: "mds_consumer_rtxssrc",
    help: "can not",
    labelNames: [
      "work_id",
      "router_id",
      "transport_id",
      "consumer_id",
      "consumer_type",
      "ssrc",
      "mimetype",
    ],
  },
  score: {
    name: "mds_consumer_score",
    help: "can not",
    labelNames: [
      "work_id",
      "router_id",
      "transport_id",
      "consumer_id",
      "consumer_type",
      "ssrc",
      "mimetype",
    ],
  },
  ssrc: {
    name: "mds_consumer_ssrc",
    help: "can not",
    labelNames: [
      "work_id",
      "router_id",
      "transport_id",
      "consumer_id",
      "consumer_type",
      "ssrc",
      "mimetype",
    ],
  },
  timestamp: {
    name: "mds_consumer_timestamp",
    help: "can not",
    labelNames: [
      "work_id",
      "router_id",
      "transport_id",
      "consumer_id",
      "consumer_type",
      "ssrc",
      "mimetype",
    ],
  },
  type: {
    name: "mds_consumer_type",
    help: "can not",
    labelNames: [
      "work_id",
      "router_id",
      "transport_id",
      "consumer_id",
      "consumer_type",
      "ssrc",
      "mimetype",
    ],
  },
};

class consumerModel {
  static getInst() {
    if (!this.instance) {
      this.instance = new consumerModel();
    }
    return this.instance;
  }

  constructor() {
    this.subscribeInfo = new client.Gauge(consumercfg.subscribeInfo);
    this.info = new client.Gauge(consumercfg.info);
    this.bitrate = new client.Gauge(consumercfg.bitrate);
    this.byteCount = new client.Gauge(consumercfg.byteCount);
    this.firCount = new client.Gauge(consumercfg.firCount);
    this.fractionLost = new client.Gauge(consumercfg.fractionLost);
    this.jitter = new client.Gauge(consumercfg.jitter);
    this.kind = new client.Gauge(consumercfg.kind);
    this.mimeType = new client.Gauge(consumercfg.mimeType);
    this.nackCount = new client.Gauge(consumercfg.nackCount);
    this.nackPacketCount = new client.Gauge(consumercfg.nackPacketCount);
    this.packetCount = new client.Gauge(consumercfg.packetCount);
    this.packetsDiscarded = new client.Gauge(consumercfg.packetsDiscarded);
    this.packetsLost = new client.Gauge(consumercfg.packetsLost);
    this.packetsRepaired = new client.Gauge(consumercfg.packetsRepaired);
    this.packetsRetransmitted = new client.Gauge(
      consumercfg.packetsRetransmitted
    );
    this.pliCount = new client.Gauge(consumercfg.pliCount);
    this.rtxSsrc = new client.Gauge(consumercfg.rtxSsrc);
    this.score = new client.Gauge(consumercfg.score);
   // this.ssrc = new client.Gauge(consumercfg.ssrc);
 //   this.timestamp = new client.Gauge(consumercfg.timestamp);
 //   this.type = new client.Gauge(consumercfg.type);
  }

  collect(consumerData, workId, routerId, transportId, consumerId, userId, 
    transportType, subscribeId) {
    consumerData.forEach((item) => {
      this.subscribeInfo.labels(workId, routerId, tranportId, consumerId, userId, subscribeId, transportType).set(1);
      this.info
        .labels(
          workId,
          routerId,
          transportId,
          consumerId,
          item.type,
          item.ssrc,
          item.mimeType
        )
        .set(1);
      if (isNumber(item.bitrate))
        this.bitrate
          .labels(
            workId,
            routerId,
            transportId,
            consumerId,
            item.type,
            item.ssrc,
            item.mimeType
          )
          .set(item.bitrate);
      if (isNumber(item.byteCount))
        this.byteCount
          .labels(
            workId,
            routerId,
            transportId,
            consumerId,
            item.type,
            item.ssrc,
            item.mimeType
          )
          .set(item.byteCount);
      if (isNumber(item.firCount))
        this.firCount
          .labels(
            workId,
            routerId,
            transportId,
            consumerId,
            item.type,
            item.ssrc,
            item.mimeType
          )
          .set(item.firCount);
      if (isNumber(item.fractionLost))
        this.fractionLost
          .labels(
            workId,
            routerId,
            transportId,
            consumerId,
            item.type,
            item.ssrc,
            item.mimeType
          )
          .set(item.fractionLost);
      if (isNumber(item.jitter))
        this.jitter
          .labels(
            workId,
            routerId,
            transportId,
            consumerId,
            item.type,
            item.ssrc,
            item.mimeType
          )
          .set(item.jitter);
      // if( isNumber(item.kind)) this.kind.labels(workId, routerId, transportId, consumerId, item.type, item.ssrc, item.mimeType).set(item.kind);
      // if( isNumber(item.mimeType)) this.mimeType.labels(workId, routerId, transportId, consumerId, item.type, item.ssrc, item.mimeType).set(item.mimeType);
      if (isNumber(item.nackCount))
        this.nackCount
          .labels(
            workId,
            routerId,
            transportId,
            consumerId,
            item.type,
            item.ssrc,
            item.mimeType
          )
          .set(item.nackCount);
      if (isNumber(item.nackPacketCount))
        this.nackPacketCount
          .labels(
            workId,
            routerId,
            transportId,
            consumerId,
            item.type,
            item.ssrc,
            item.mimeType
          )
          .set(item.nackPacketCount);
      if (isNumber(item.packetCount))
        this.packetCount
          .labels(
            workId,
            routerId,
            transportId,
            consumerId,
            item.type,
            item.ssrc,
            item.mimeType
          )
          .set(item.packetCount);
      if (isNumber(item.packetsDiscarded))
        this.packetsDiscarded
          .labels(
            workId,
            routerId,
            transportId,
            consumerId,
            item.type,
            item.ssrc,
            item.mimeType
          )
          .set(item.packetsDiscarded);
      if (isNumber(item.packetsLost))
        this.packetsLost
          .labels(
            workId,
            routerId,
            transportId,
            consumerId,
            item.type,
            item.ssrc,
            item.mimeType
          )
          .set(item.packetsLost);
      if (isNumber(item.packetsRepaired))
        this.packetsRepaired
          .labels(
            workId,
            routerId,
            transportId,
            consumerId,
            item.type,
            item.ssrc,
            item.mimeType
          )
          .set(item.packetsRepaired);
      if (isNumber(item.packetsRetransmitted))
        this.packetsRetransmitted
          .labels(
            workId,
            routerId,
            transportId,
            consumerId,
            item.type,
            item.ssrc,
            item.mimeType
          )
          .set(item.packetsRetransmitted);
      if (isNumber(item.pliCount))
        this.pliCount
          .labels(
            workId,
            routerId,
            transportId,
            consumerId,
            item.type,
            item.ssrc,
            item.mimeType
          )
          .set(item.pliCount);
      if (isNumber(item.rtxSsrc))
        this.rtxSsrc
          .labels(
            workId,
            routerId,
            transportId,
            consumerId,
            item.type,
            item.ssrc,
            item.mimeType
          )
          .set(item.rtxSsrc);
      if (isNumber(item.score))
        this.score
          .labels(
            workId,
            routerId,
            transportId,
            consumerId,
            item.type,
            item.ssrc,
            item.mimeType
          )
          .set(item.score);
      // if (isNumber(item.ssrc))
      //   this.ssrc
      //     .labels(workId, routerId, transportId, consumerId, item.type, item.ssrc, item.mimeType)
      //     .set(item.ssrc);
      if (isNumber(item.timestamp))
        this.timestamp
          .labels(
            workId,
            routerId,
            transportId,
            consumerId,
            item.type,
            item.ssrc,
            item.mimeType
          )
          .set(item.timestamp);
      // if( isNumber(item.type)) this.type.labels(workId, routerId, transportId, consumerId, item.type, item.ssrc, item.mimeType).set(item.type);
      // console.log("consumerid:", consumerId, "ssrc:", item.ssrc);
    });
  }
}

class consumer4Log {
  constructor(consumer, workerId, routerId, tranportId, userId, transportType) {
    this.id = consumer.id;
    this._consumer = consumer;
    this._workerId = workerId;
    this._routerId = routerId;
    this._transportId = tranportId;
    this._userId = userId;
    this._transportType = transportType;
    this._subscribeId = transportType === "PlainTransport" ? consumer.appData.subscribeId : null;
    
    this._report = consumerModel.getInst();
  }

  async collect() {
    let statData;
    try {
      statData = await this._consumer.getStats();
    } catch (error) {
      console.log(error, "Error consumer");
      return;
    }

    this._report.collect(
      statData,
      this._workerId,
      this._routerId,
      this._transportId,
      this._consumer.id,
      this._userId, 
      this._transportType,
      this._subscribeId
    );
  }
}

class Monitor {
  constructor(job, instance, gateway) {
    this.init(job, instance, gateway)

    this._arrObj = [];
  }

  init(job, instance, gateway) {
    this._curJob = job;
    this._curInstance = instance;
    this._gateway = new client.Pushgateway(gateway);
  }

  createWorkerLog(work) {
    let worker = new worker4Log(work);
    this._arrObj.push(worker);

    return worker;
  }

  closeWorkerLog(work) {
    this._arrObj.splice(
      this._arrObj.findIndex((elem) => {
        return elem.id == work.id;
      }),
      1
    );
  }

  createRouterLog(router, workId, gateWayId) {
    let router_ = new router4Log(router, workId, gateWayId);
    this._arrObj.push(router_);
    return router_;
  }

  closeRouterLog(router) {
    this._arrObj.splice(
      this._arrObj.findIndex((elem) => {
        return elem.id == router.id;
      }),
      1
    );
  }

  createTransportLog(transport, workerId, routerId, gateWayId, meetingId) {
    let transport_ = new transport4Log(transport, workerId, routerId, gateWayId, meetingId);
    this._arrObj.push(transport_);
    return transport_;
  }

  closeTransportLog(transport) {
    this._arrObj.splice(
      this._arrObj.findIndex((elem) => {
        return elem.id == transport.id;
      }),
      1
    );
  }

  createProducerLog(producer, workerId, routerId, transportId) {
    let producer_ = new producer4Log(producer, workerId, routerId, transportId);
    this._arrObj.push(producer_);
    return producer_;
  }

  closeProducerLog(producer) {
    this._arrObj.splice(
      this._arrObj.findIndex((elem) => {
        return elem.id == producer.id;
      }),
      1
    );
  }

  createConsumerLog(consumer, workerId, routerId, transportId, userId, transportType) {
    let consumer_ = new consumer4Log(consumer, workerId, routerId, transportId, userId, transportType);
    this._arrObj.push(consumer_);
    return consumer_;
  }

  closeConsumerLog(consumer) {
    this._arrObj.splice(
      this._arrObj.findIndex((elem) => {
        return elem.id == consumer.id;
      }),
      1
    );
  }

  listening(mediasoup) {
    this.run(5000);
    //this.run(5000);
    mediasoup.on("newworker", (worker) => {
      console.log("new newworker created");
      this.createWorkerLog(worker);
  
      worker.observer.on("close", () => {
        this.closeWorkerLog(worker);
        console.log("worker closed [worker.pid:%d]", worker.pid);
      });
  
      // listening by router
      worker.observer.on("newrouter", (router) => {
        console.log("new router created");
        this.createRouterLog(router, worker.pid, worker.appData.gateWayId);
  
        router.observer.on("close", () => {
          this.closeRouterLog(router);
        });
  
        // listening by transport
        router.observer.on("newtransport", (transport) => {
          this.createTransportLog(transport, worker.pid, router.id, worker.appData.gateWayId, router.appData.meetingId);
  
          transport.observer.on("close", () => {
            this.closeTransportLog(transport);
          });
  
          // listening by producer
          transport.observer.on("newproducer", (producer) => {
            this.createProducerLog(producer, worker.pid, router.id, transport.id, transport.constructor.name);
            console.log("new newproducer created");
            producer.observer.on("close", () => {
              this.closeProducerLog(producer);
              console.log("producer closed [producer.id:%s]", producer.id);
            });
          });
  
          transport.observer.on("newconsumer", (consumer) => {
            console.log("new newconsumer created");
            this.createConsumerLog(consumer, worker.pid, router.id, transport.id, transport.appData.userId,transport.constructor.name);
            consumer.observer.on("close", () => {
              this.closeConsumerLog(consumer);
              console.log("consumer closed [consumer.id:%s]", consumer.id);
            });
          });
        });
      });
    });
  }
  
  run(timeout) {
    setInterval(async () => {
      await this._arrObj.forEach((item, key) => {
        item.collect();
      });
      await this._gateway.push(
        { jobName: this._curJob, groupings: { instance: this._curInstance } },
        function (err, resp, body) {
          if (!err) {
            console.log("Succ!");
          } else {
            console.log("push Failed!");
          }
        }
      );
      await client.register.getMetricsAsArray().forEach((elem) => {
        elem.reset();
      });
    }, 1000);
  }
}

//let a = new Monitor(strJob, strInstance, strPushgatewayAddress);
exports.Monitor = new Monitor(strJob, strInstance, strPushgatewayAddress);