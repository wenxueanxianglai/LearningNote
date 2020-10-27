var config = require('./config');


const webdriver = require("selenium-webdriver");
const chrome = require("selenium-webdriver/chrome");

const By = webdriver.By;
const until = webdriver.until;

function getElemNgModel(strName) {
    return By.css('*[ng-model="' + strName + '"]');
}

function getElemNgClick(strClick) {
    return By.css('*[ng-click="' + strClick + '\(\)"]');
}

const path = require('path');

let vi_path = path.resolve('./testfile/video_test.y4m');
console.log('video path: ' + vi_path);

let au_path = path.resolve('./testfile/audio_test.wav');
console.log('audio path: ' + au_path);



let chromeOption = new chrome.Options();
chromeOption.addArguments("--no-sandbox");
chromeOption.addArguments("--no-default-browser-check");
chromeOption.addArguments("--disable-popup-blocking"); //禁止弹出拦截
chromeOption.addArguments('--use-fake-device-for-media-stream');
chromeOption.addArguments('--use-fake-ui-for-media-stream');
chromeOption.addArguments('--use-file-for-fake-video-capture=' + vi_path);
chromeOption.addArguments('--use-file-for-fake-audio-capture=' + au_path);
// chromeOption.addArguments("--start-maximized");
// chromeOption.addArguments("--no-managed-user-acknowledgment-check");
// chromeOption.addArguments("--webview-disable-safebrowsing-support");
chromeOption.addArguments("--enable-automation");

//chromeOption.addArguments("--unsafely-treat-insecure-origin-as-secure"+ `="` + config.url+ '"');
//let arg = "--unsafely-treat-insecure-origin-as-secure=“http://host||ip:port” --user-data-dir=“F:\temp"

// 打开浏览器
// let driver = new webdriver.Builder()
//     .usingServer(config.server)
//     .forBrowser("chrome")
//   .setChromeOptions(chromeOption).build();

config.pageSet.forEach(async (item) => {
    let driver = new webdriver.Builder()
    .usingServer(config.server)
    .forBrowser("chrome")
  .setChromeOptions(chromeOption).build();
    
    await driver.get(config.url);
    
    await driver.wait(until.elementLocated(getElemNgModel("getwayIP")), 10);

    driver.findElement(getElemNgModel('userName')).sendKeys(item.userName);
    console.log(item.userName);
    driver.findElement(getElemNgModel('password')).sendKeys(item.password);
    console.log(item.password);
    await driver.sleep(1000);
    driver.findElement(getElemNgClick('init')).click();
    driver.findElement(getElemNgClick('init')).click();
    driver.findElement(getElemNgClick('init')).click();
    await driver.sleep(3000);

   // let serLog = await (await driver).manage().logs().getAvailableLogTypes();
    
   // console.log(arrn);
    let arrLog = await driver.manage().logs().get('browser');
    let arrserLog = await driver.manage().logs().get('server');

    for (let s of arrserLog) {
        console.log(s);
    }
})
// 打开网页
//driver.get('https://brtc.butel.com:31001/meetingconnect/');
// 填写表单

//driver.findElement(getElemNgModel('userName')).sendKeys('webdriver');


// 进入会议
