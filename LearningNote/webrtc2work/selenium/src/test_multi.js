const webdriver = require("selenium-webdriver");

const { hubHost } = require("./selenium_cofig");

(async function test_multiples_nodes() {
  let arrDriver = [];

  for (let i = 0; i < 10; ++i) {
    arrDriver.push(
      await new webdriver.Builder()
        .forBrowser("chrome")
        .usingServer(hubHost)
        .build()
    );
  }

  function sendfunc(a) {
    alert(a);
  }

  console.log(sendfunc.toString());
  for (iter in arrDriver) {
    await arrDriver[iter].get("http://www.baidu.com/");
    await arrDriver[iter]
      .findElement(webdriver.By.id("kw"))
      .sendKeys("ndoe" + iter);

    // await arrDriver[iter].findElement(webdriver.By.id("su")).click();
    //   await arrDriver[iter].findElement()
    // arrDriver[iter].executeScript(
    //   sendfunc.toString() + "sendfunc(" + iter + ");"
    // );
  }

  await arrDriver[0].sleep(13000);
  for (iter in arrDriver) {
    await arrDriver[iter].quit();
  }
})();
