const webdriver = require('selenium-webdriver');

async function test_muti(account, pwd){
    let driver = await new webdriver.Builder()
    .forBrowser('chrome')
    .build();

    await driver.get('http://localhost:8080/index.html');


}


(async function example() {
    let driver = new webdriver.Builder()
    .forBrowser('chrome')
    .usingServer('http://localhost:4444/wd/hub')
    .build();

  //let driver = await new Builder().forBrowser('chrome').build();
  try {
    await driver.get('http://www.baidu.com');
  //  await driver.findElement(By.name('q'));.sendKeys('webdriver', Key.RETURN);
   // await driver.wait(until.titleIs('webdriver - Google Search'), 1000);
  } finally {
   // await driver.quit();
  }
})();