
var webdriver = require('selenium-webdriver');
var chrome = require('selenium-webdriver/chrome');
var path = require('chromedriver').path;

var service = new chrome.ServiceBuilder(path).build();
chrome.setDefaultService(service);



const By = webdriver.By;
const  until = webdriver.until;

var driver = new webdriver.Builder()
    .withCapabilities(webdriver.Capabilities.chrome())
    .build();

driver.get('https://www.baidu.com');
driver.findElement(By.id('kw')).sendKeys('webdriver');
driver.findElement(By.id('su')).click();
driver.wait(until.titleIs('webdriver_百度搜索'), 1000);
//driver.quit();