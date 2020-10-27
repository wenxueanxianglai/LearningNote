const nUrl = require("url");
const path = require("path");

var config = require("./config");
const webdriver = require("selenium-webdriver");
const chrome = require("selenium-webdriver/chrome");

let vi_path = path.resolve("C://drive_path/testfile/video_test.y4m");
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
chromeOption.addArguments("--headless");
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
      tUrl.searchParams.append(i, element[i]);
    }
  }

  onClose() {
    this.driver.close();
  }

  async testStart() {
    await this.driver.get(this.url);
    await this.driver.sleep(4000);
  }

  async getStat() {
    let result = await mdriver.executeScript("return window.mettingStaus");
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

  report() {
      //TODO 添加上报数据
  }

  run() {

  }
}
