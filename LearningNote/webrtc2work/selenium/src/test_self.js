const webdriver = require("selenium-webdriver");
const fs = require("fs");

(async function example() {
  let driver = new webdriver.Builder()
    .forBrowser("chrome")
    .usingServer("http://192.168.1.119:4444/wd/hub")
    .build();

  try {
    await driver.get("http://www.baidu.com/");

    var str = "";
    await fs.readFile("./get_ip.js", function (error, data) {
      if (error) {
        console.log("read File failed");
      } else {
        str += data.toString();
        console.log(str, str.length);
      }
    });

    await driver.executeScript('alert("aaa");');
    //    await (await driver).executeScript();
    await (await driver).sleep(4000);

    // let sess = (await driver).getWindowHandle();
    // console.log(sess);

    // let ur = (await driver).getCurrentUrl();
    //console.log(ur);
    //  await driver.findElement(By.name('q')).sendKeys('webdriver', Key.RETURN);
    ///   await driver.wait(until.titleIs('webdriver - Google Search'), 1000);
  } finally {
    await driver.quit();
  }
})();
