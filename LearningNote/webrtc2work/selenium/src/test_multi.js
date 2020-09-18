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
  // console.log(sendfunc.toString());
  console.log(sendfunc.toString());
  for (iter in arrDriver) {
    await arrDriver[iter].get("http://www.baidu.com/");
    arrDriver[iter].executeScript(
      sendfunc.toString() + "sendfunc(" + iter + ");"
    );
  }
})();
