const webdriver = require('selenium-webdriver');
const path = require('path');

let vi_path = path.resolve('./testfile/video_test.y4m');
console.log('video path: ' + vi_path);

let au_path = path.resolve('./testfile/audio_test.wav');
console.log('audio path: ' + au_path);

(async function example() {
    let capabilities = webdriver.Capabilities.chrome();
    capabilities.set('chromeOptions',{
        'args': [
            //'--headless',
           // '--disable-gpu',
            '--ignore-certificate-errors',
            '--allow-running-insecure-content',
            //'--incognito',
            //'--disable-infobars',
           '--use-fake-device-for-media-stream', // 使用虚拟设备代替真实设备
           '--use-fake-ui-for-media-stream',     // 配合上面的
           
           '--use-file-for-fake-video-capture=' + vi_path,
           '--use-file-for-fake-audio-capture=' + au_path,
           `--no-sandbox`
        ]
    })
  //  capabilities.set('pageLoadStrategy', 'none');
    let driver = new webdriver.Builder()
    .forBrowser('chrome')
        .usingServer('http://169.254.120.129:4444/wd/hub')
        .withCapabilities(capabilities)
    .build();

  //let driver = await new Builder().forBrowser('chrome').build();
  try {
    await driver.get('https://brtc.butel.com:31001/meetingconnect/');
  //  await driver.findElement(By.name('q'));.sendKeys('webdriver', Key.RETURN);
   // await driver.wait(until.titleIs('webdriver - Google Search'), 1000);
  } finally {
   // await driver.quit();
  }
})();