let { testPresure } = require('./test_presure');
const sampleCfg = require('./sample_json.json');
// 目标1 测试 分发




// let oneInst = new testPresure({
//     userName: "15500010107",
//     password: "123456",
//     getwayIP: "brtc.butel.com",
//     port: "3000",
//     meetingID: "90019168",
//     isSpeak: 1,
//   });

//   oneInst.testStart();
//   oneInst.run(20);

// 目标 1.1 同一个网关 下， 多个 会议 每个会议 9个用户
function test_sample() {
    let arr = [];
    sampleCfg.pageSet.forEach(async item => {
        let oneInst = new testPresure(item);
        await oneInst.testStart();
        oneInst.run(80);
        arr.push(oneInst);
    });

    setInterval(
        () => {
            await arr.forEach(item => {
                item.report();
            });


            

      }  ,1000
    );
}
test_sample();



// 目标 1.2 同一个网管