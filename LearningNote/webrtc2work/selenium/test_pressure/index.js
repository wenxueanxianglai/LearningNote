let { testPresure } = require("./test_presure");
const sampleCfg = require("./sample_json");

// 目标1 测试 分发
async function WaitMs(timeoutMs) {
  return new Promise(function (resolve) {
    setTimeout(() => {
      resolve(true);
      log.warn("timeout:", timeoutMs);
    }, timeoutMs * 1000);
  });
}

let arr = [];
let flag = 0;
let arrArgs = process.argv.splice(2);
// 目标 1.1 同一个网关 下， 多个 会议 每个会议 9个用户
async function test_sample() {
  process.on("SIGINT", async function () {
    if (flag) {
      console.log("already exit");
      return;
    }
    console.log("Exit now!");
    flag = 1;
    let task = [];
    for (let i of arr) {
      task.push(i?.close());
    }

    await Promise.all(task);
    process.exit();
  });

  await sampleCfg.pageSet.forEach(async element => {
    return new Promise((resolve, reject) => {
      if (flag) {
        return resolve(-701);
      }
      if (arrArgs.length > 0) {
        let meetingNum = arrArgs.indexOf(element.meetingID);
        if (meetingNum < 0) {
          return resolve(-702);
        }
      }
      let oneInst = new testPresure(element);
      arr.push(oneInst);
      let ret = oneInst.testStart();
      console.log("meetingId:%s nube:%s ----ret:%d ", ret.m, ret.n, ret.ret);
      resolve(1);
    });
  });

  // for (let i of sampleCfg.pageSet) {
  //   if (flag) {
  //     break;
  //   }

  //   if (arrArgs.length > 0) {
  //     let meetingNum = arrArgs.indexOf(i.meetingID);
  //     if (meetingNum < 0) {
  //       continue;
  //     }
  //   }
  //   let oneInst = new testPresure(i);
  //   arr.push(oneInst);
  //   let ret = await oneInst.testStart();
  //   console.log("meetingId:%s nube:%s ----ret:%d ", ret.m, ret.n, ret.ret);
  // }

  console.log("----ok");
  let interval = setInterval(() => {
    for (let i of arr) {
      if (i != null) {
        i.getStat();
      }
    }
  }, 10000);

//  await WaitMs(10000);
  //oneInst.run(300000);
  //await arr[0].close();
}

test_sample();

// 目标 1.2 同一个网管

// let oneInst = new testPresure({
//     userName: "15500010107",
//     password: "123456",
//     getwayIP: "brtc.butel.com",
//     port: "3000",
//     meetingID: "90019168",
//     isSpeak: 1,
//   });

// oneInst.testStart();
// oneInst.run(20);
// oneInst.run(20);
