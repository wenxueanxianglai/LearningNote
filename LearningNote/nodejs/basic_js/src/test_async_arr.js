var items = [1, 2, 3, 4, 5, 6];
var results = [];

async function WaitMs(timeoutMs) {
  return new Promise(function (resolve) {
    setTimeout(() => {
      resolve(true);
      console.log("timeout:", timeoutMs);
    }, timeoutMs * 1000);
  });
}

async function test_for() {
    return new Promise(async (resolve, reject) => {
        WaitMs(7 - item).then(resolve => {
            console.log(item);
            resolve(1);
            return true;
        })

    });
    
    // await items.forEach((item) => {
    //     return new Promise(async (resolve, reject) => {
    //         await WaitMs(7 - item);
    //         console.log(item);
    //         resolve(1);
    //         return true;
    //     });
    // });
}

async function test_sample() {

    await test_for();

  console.log("OK-----");
}

test_sample();
