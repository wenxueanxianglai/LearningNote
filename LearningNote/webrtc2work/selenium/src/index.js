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



let chromeOption = new chrome.Options();
chromeOption.addArguments("--no-default-browser-check");
chromeOption.addArguments("--disable-popup-blocking"); //禁止弹出拦截
chromeOption.addArguments("--start-maximized");
chromeOption.addArguments("--no-sandbox");

// 打开浏览器
let driver = new webdriver.Builder()
    .usingServer(config.server)
    .forBrowser("chrome")
  .setChromeOptions(chromeOption).build();

config.pageSet.forEach(async (item) => {
    let driver = new webdriver.Builder()
    .usingServer(config.server)
    .forBrowser("chrome")
  .setChromeOptions(chromeOption).build();
    
    await driver.get(item.url);
    
    await driver.wait(until.elementLocated(getElemNgModel("getwayIP")), 10);

    let ipEditor = driver.findElement(getElemNgModel('getwayIP'));
    ipEditor.clear();
    ipEditor.sendKeys(item.getwayIP);
    driver.findElement(getElemNgModel('userName')).sendKeys(item.userName);
    driver.findElement(getElemNgModel('password')).sendKeys(item.password);
    driver.findElement(getElemNgClick('init')).click();

})
// 打开网页
//driver.get('https://brtc.butel.com:31001/meetingconnect/');
// 填写表单

//driver.findElement(getElemNgModel('userName')).sendKeys('webdriver');


// 进入会议
