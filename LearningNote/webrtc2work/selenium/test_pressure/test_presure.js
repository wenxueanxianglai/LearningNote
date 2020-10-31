const nUrl = require("url");
const path = require("path");

var config = require("./config");
const webdriver = require("selenium-webdriver");
const chrome = require("selenium-webdriver/chrome");

const { devReport, gateway } = require("./dev_report");

let vi_path = path.resolve("C://drive_path/testfile/222.y4m"); //video_test.y4m
let au_path = path.resolve("C://drive_path/testfile/audio_test.wav");

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
//chromeOption.addArguments("--headless");
chromeOption.addArguments("--enable-automation");

class testPresure {
  constructor(jsonElement) {
    this.driver = new webdriver.Builder()
      .usingServer(config.server)
      .forBrowser("chrome")
      .setChromeOptions(chromeOption)
      .build();

    this.url = new nUrl.URL(config.url);
    for (let i in jsonElement) {
      this.url.searchParams.append(i, jsonElement[i]);
    }

    this.info = jsonElement;
    this._devReport = new devReport();
  }

  async close() {
    await this.driver.close();
  }

  async testStart() {
    let i = 0;
    await this.driver.get(this.url);
    await new Promise((resolve) => {
      let id = setInterval(async () => {
        let state = await this.getStat();
        i++;
        console.log(this.info.userName, "setInterval state", state);
        if (state?.joinState === 1) {
          clearInterval(id);
          console.log(this.info.userName, "succ!");
          await this.driver.sleep(1000);
          resolve();
        } else if (state?.joinState === -1) {
          console.log(this.info.userName, "failed:-1!");
          resolve(-1);
        } else {
          if (i > 9) {
            console.log(this.info.userName, "failed!");
            resolve(-1);
          }
        }
      }, 500);
    });
  }

  async getStat() {
    let result = await this.driver.executeScript("return window.mettingStaus");
    return result;
  }

  traceInit(initState) {
    return 1 === initState;
  }

  traceJoin(joinState) {
    return 1 === joinState;
  }

  traceSpeak(speakState) {
    return 1 === speakState;
  }

  async report() {
    //TODO 添加上报数据
    // let ret = await this.getStat();
    // console.log(ret);

    let ret = await this.getStat();
    console.log(ret);
    //this._devReport.collect(ret);
  }

  async run(timeout) {
    let interval = setInterval(() => {
      if (this.driver != null) {
        this.report();
      }
    }, 3000);
    setTimeout(async () => {
      await clearInterval(interval);
      await this.close();
      this.driver = null;
    }, timeout * 1000);
  }
}

// export
exports.testPresure = testPresure;

// test
async function test_sample() {
  let oneInst = new testPresure({
    userName: "15500010107",
    password: "123456",
    getwayIP: "brtc.butel.com",
    port: "3000",
    meetingID: "90019168",
    isSpeak: 1,
  });

  await oneInst.testStart();
  oneInst.run(20);
}

//test_sample();
