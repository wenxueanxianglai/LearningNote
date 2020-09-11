const puppeteer = require('puppeteer');
const timer = require('timers');
const { join } = require('path');

(async () => {
    // 1. launch 创建一个浏览器对象
    const browser = await puppeteer.launch({
        args: [//'--ignore-certificate-errors',   // 解决证书错误
       // `--use-fake-device-for-media-stream`, // 使用虚拟设备代替真实设备
       // `--use-fake-ui-for-media-stream`,     // 配合上面的
        `--no-sandbox`
        ],
        ignoreHTTPSErrors: true,
        headless: false
        // defaultViewport:{
        //     width: 1000,
        //     height: 800
        // }
    }); 

    // const browser = await puppeteer.launch({
    //     executablePath: 'C:\\Program\ Files\\Google\\Chrome\\Application\\chrome.exe',
    //     handless: false,
    //     defaultViewport: {
    //         width: 1000,
    //         height: 800
    //     }
    // });

    console.log('browser create succ!')  
    // 2. 通过 browser对象 创建一个页面
    const page = await browser.newPage();
    
    // 3. page 跳转到 https://192.168.1.119:3000/
     

      page.on('dialog', async dialog => {
        console.log(dialog.message);
        await dialog.accept();
    });
    await page.tracing.start({path: './trace.json'});
    //await page.goto('https://192.168.1.119:3000/');
    await page.goto('https://www.baidu.com/');
    console.log('page open succ!')  
    await page.tracing.stop();
    //let video = page.$eval('video');
    //console.log(video);

    // setTimeout(() => {
    //     browser.close();
    // }, 5000);

 

    // 4. 对页面截图
    await page.screenshot({path: 'example.png'});
   // page.on('dialog', async()=>)
    //let met = page.getMetrics();
    console.log(met);

    // 5. 关闭浏览器
   // browser.close();
})();