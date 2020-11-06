let { testPresure } = require("./test_presure");
const sampleCfg = require("./recv");


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

(async function test_sample() {
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
  
    let simpStart = async () => {
      for (let i of sampleCfg.pageSet) {
        if (flag) {
          break;
        }
  
        if (arrArgs.length > 0) {
          let meetingNum = arrArgs.indexOf(i.meetingID);
          if (meetingNum < 0) {
            continue;
          }
        }
        let oneInst = new testPresure(i);
        arr.push(oneInst);
        let ret = await oneInst.testStart();
        console.log("meetingId:%s nube:%s ----ret:%d ", ret.m, ret.n, ret.ret);
      }
    };
  
    let asyncStart = async () => {
      let oneStart = async (item) => {
        if (flag) {
          return;
        }
  
        if (arrArgs.length > 0) {
          let meetingNum = arrArgs.indexOf(i.meetingID);
          if (meetingNum < 0) {
            return;
          }
        }
        let oneInst = new testPresure(item);
        arr.push(oneInst);
        let ret = await oneInst.testStart();
        console.log("meetingId:%s nube:%s ----ret:%d ", ret.m, ret.n, ret.ret);
      };
  
      let startArr = [];
      for (let i of sampleCfg.pageSet) {
        startArr.push(oneStart(i));
      }
      await Promise.all(startArr);
    };
  
    await simpStart();
    console.log("----ok");
    let interval = setInterval(() => {
      for (let i of arr) {
        if (i != null) {
          i.getStat();
        }
      }
    }, 10000);
  })()
