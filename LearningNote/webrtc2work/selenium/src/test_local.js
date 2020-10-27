var config = require("./config");
const webdriver = require("selenium-webdriver");
const chrome = require("selenium-webdriver/chrome");
const nUrl = require("url");
const path = require("path");

let vi_path = path.resolve("C://drive_path/testfile/video_test.y4m");
let au_path = path.resolve("C://drive_path/testfile/audio_test.wav");

const By = webdriver.By;
const until = webdriver.until;

async function start() {
  var arr = [];

  let chromeOption = new chrome.Options();
  chromeOption.addArguments("--no-sandbox");
  chromeOption.addArguments("--allow-running-insecure-content");
  chromeOption.addArguments("--ignore-certificate-errors");
  chromeOption.addArguments("--no-default-browser-check");
  chromeOption.addArguments("--disable-popup-blocking"); //禁止弹出拦截
  chromeOption.addArguments("--use-fake-device-for-media-stream");
  chromeOption.addArguments("--use-fake-ui-for-media-stream");
  chromeOption.addArguments("--use-file-for-fake-video-capture=" + vi_path);
  chromeOption.addArguments("--use-file-for-fake-audio-capture=" + au_path);
  chromeOption.addArguments("--headless");
  chromeOption.addArguments("--enable-automation");
  await config.pageSet.forEach(async (element) => {
    let tUrl = new nUrl.URL(config.url);
    for (let i in element) {
      tUrl.searchParams.append(i, element[i]);
    }

    let mdriver = new webdriver.Builder()
      .usingServer(config.server)
      .forBrowser("chrome")
      .setChromeOptions(chromeOption)
      .build();

    await mdriver.get(tUrl);
    await (await mdriver).sleep(4000);
    let retsult = await mdriver.executeScript("return window.mettingStaus");
    console.log(element.userName, retsult);

    arr.push({
      driver: mdriver,
      url: tUrl,
      succ: retsult.initialState == 1 && retsult.joinState == 1,
      restart: 0,
    });
  });

  return arr;
}

async function restart(item) {
  await item.driver.get(item.url);
  item.restart++;
}

(async function run() {
  let arrDrvier = await start();

  setInterval(() => {
    arrDrvier.forEach(async (item) => {
      if (item.restart < 3) {
        let retsult = await item.driver.executeScript(
          "return window.mettingStaus"
        );

        console.log(retsult, item.restart);
        if (retsult.succ != true && item.restart < 3) {
          restart(item);
        }
      }
    });
  }, 5000);
})();

// config.pageSet.forEach(async (element) => {
//   let tUrl = new nUrl.URL(config.url);
//   for (let i in element) {
//     tUrl.searchParams.append(i, element[i]);
//   }

//   let driver = new webdriver.Builder()
//     .usingServer(config.server)
//     .forBrowser("chrome")
//     .setChromeOptions(chromeOption)
//     .build();

//   await driver.get(tUrl);
//   await (await driver).sleep(4000);

//   arr.push(driver);
//   let retsult = await driver.executeScript("return window.mettingStaus");
//   console.log(element.userName, retsult);
// });

// setInterval(() => {
//   arr.forEach((item) => {
//     let retsult = item.executeScript("return window.mettingStaus");
//     console.log(retsult);
//   });
// }, 1000);
